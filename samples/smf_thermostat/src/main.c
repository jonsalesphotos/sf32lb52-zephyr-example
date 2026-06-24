/*
 * Copyright (c) 2026 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Zephyr SMF (State Machine Framework) demo - a hierarchical thermostat.
 *
 * State hierarchy (see state_machine.html for the rendered diagram):
 *
 *      ACTIVE  (superstate, parent of IDLE/HEATING/COOLING)
 *      |          - common handling for EVENT_FAULT / EVENT_SHUTDOWN
 *      +-- IDLE     (initial child)  heater + cooler OFF
 *      +-- HEATING                   heater ON
 *      +-- COOLING                   cooler ON
 *      FAULT   (top-level leaf, OUTSIDE of ACTIVE)
 *
 * Why this shape teaches SMF well:
 *   - Hierarchy + initial transition: entering ACTIVE auto-descends to IDLE.
 *   - Run propagation (new v0.2.0 API): a leaf state returns
 *     SMF_EVENT_PROPAGATE for events it does not handle, so the shared
 *     ACTIVE.run gets to deal with FAULT / SHUTDOWN once, for every child.
 *   - LCA / sibling optimization: IDLE<->HEATING<->COOLING hops do NOT
 *     re-run ACTIVE entry/exit, but leaving to FAULT (parent == NULL) does.
 *
 * The demo is self-driving: main() plays a scripted sequence of simulated
 * "sensor" events through a k_event object, while a dedicated thread runs
 * the state machine and reacts to them. This is the idiomatic Zephyr
 * event-driven SMF pattern (producer posts events, SM thread consumes).
 */

#include <zephyr/kernel.h>
#include <zephyr/smf.h>
#include <zephyr/sys/util.h>

/* ----------------------------------------------------------------------- */
/* Events posted to the state machine (k_event bitmask)                    */
/* ----------------------------------------------------------------------- */
#define EVENT_TEMP_LOW   BIT(0) /* temperature dropped below setpoint      */
#define EVENT_TEMP_HIGH  BIT(1) /* temperature rose above setpoint         */
#define EVENT_TEMP_OK    BIT(2) /* temperature back inside the dead-band   */
#define EVENT_FAULT      BIT(3) /* sensor / hardware fault                 */
#define EVENT_RESET      BIT(4) /* operator cleared the fault              */
#define EVENT_SHUTDOWN   BIT(5) /* power-down request                      */

#define EVENT_ALL                                                              \
	(EVENT_TEMP_LOW | EVENT_TEMP_HIGH | EVENT_TEMP_OK | EVENT_FAULT |       \
	 EVENT_RESET | EVENT_SHUTDOWN)

/*
 * smf_set_terminate() value MUST be non-zero: smf_run_state() returns this
 * value, and our loop treats "non-zero" as "stop". Using 0 here would spin.
 */
#define SM_TERMINATE_OK 1

/* ----------------------------------------------------------------------- */
/* State identifiers (also used as indexes into thermo_states[])           */
/* ----------------------------------------------------------------------- */
enum thermo_state_id {
	STATE_ACTIVE,  /* parent / superstate                  */
	STATE_IDLE,    /* child of ACTIVE, initial transition  */
	STATE_HEATING, /* child of ACTIVE                      */
	STATE_COOLING, /* child of ACTIVE                      */
	STATE_FAULT,   /* top-level leaf                       */
};

/* ----------------------------------------------------------------------- */
/* State machine context. The smf_ctx MUST be the first member.            */
/* ----------------------------------------------------------------------- */
struct thermo_ctx {
	struct smf_ctx ctx;    /* framework bookkeeping - keep first        */
	struct k_event events; /* event channel: producer -> SM thread      */
	uint32_t pending;      /* event bitmask handed to the run actions   */
};

/* Forward declaration so the state actions can reference the table. */
static const struct smf_state thermo_states[];

/* ======================================================================= */
/* ACTIVE - superstate (shared behaviour for IDLE / HEATING / COOLING)     */
/* ======================================================================= */
static void active_entry(void *o)
{
	ARG_UNUSED(o);
	printk("   (ACTIVE)   entry : controller armed\n");
}

static enum smf_state_result active_run(void *o)
{
	struct thermo_ctx *s = o;

	/*
	 * Reached only for events a child left unhandled (it returned
	 * SMF_EVENT_PROPAGATE). One place to handle faults/shutdown for all
	 * three operating sub-states.
	 */
	if (s->pending & EVENT_FAULT) {
		printk("   (ACTIVE)   run   : EVENT_FAULT -> FAULT\n");
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_FAULT]);
		return SMF_EVENT_HANDLED;
	}

	if (s->pending & EVENT_SHUTDOWN) {
		printk("   (ACTIVE)   run   : EVENT_SHUTDOWN -> terminate\n");
		smf_set_terminate(SMF_CTX(s), SM_TERMINATE_OK);
		return SMF_EVENT_HANDLED;
	}

	return SMF_EVENT_HANDLED; /* top of the tree: nothing above us */
}

static void active_exit(void *o)
{
	ARG_UNUSED(o);
	printk("   (ACTIVE)   exit  : controller disarmed\n");
}

/* ======================================================================= */
/* IDLE - initial child of ACTIVE (heater + cooler off)                    */
/* ======================================================================= */
static void idle_entry(void *o)
{
	ARG_UNUSED(o);
	printk("    [IDLE]    entry : heater OFF, cooler OFF\n");
}

static enum smf_state_result idle_run(void *o)
{
	struct thermo_ctx *s = o;

	if (s->pending & EVENT_TEMP_LOW) {
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_HEATING]);
		return SMF_EVENT_HANDLED;
	}
	if (s->pending & EVENT_TEMP_HIGH) {
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_COOLING]);
		return SMF_EVENT_HANDLED;
	}
	/* FAULT / SHUTDOWN are common -> let ACTIVE handle them. */
	return SMF_EVENT_PROPAGATE;
}
/* IDLE has no exit action (NULL in the table). */

/* ======================================================================= */
/* HEATING - heater on, raising temperature                                */
/* ======================================================================= */
static void heating_entry(void *o)
{
	ARG_UNUSED(o);
	printk("    [HEATING] entry : heater ON\n");
}

static enum smf_state_result heating_run(void *o)
{
	struct thermo_ctx *s = o;

	if (s->pending & EVENT_TEMP_OK) {
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_IDLE]);
		return SMF_EVENT_HANDLED;
	}
	if (s->pending & EVENT_TEMP_HIGH) {
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_COOLING]);
		return SMF_EVENT_HANDLED;
	}
	return SMF_EVENT_PROPAGATE;
}

static void heating_exit(void *o)
{
	ARG_UNUSED(o);
	printk("    [HEATING] exit  : heater OFF\n");
}

/* ======================================================================= */
/* COOLING - cooler on, lowering temperature                               */
/* ======================================================================= */
static void cooling_entry(void *o)
{
	ARG_UNUSED(o);
	printk("    [COOLING] entry : cooler ON\n");
}

static enum smf_state_result cooling_run(void *o)
{
	struct thermo_ctx *s = o;

	if (s->pending & EVENT_TEMP_OK) {
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_IDLE]);
		return SMF_EVENT_HANDLED;
	}
	if (s->pending & EVENT_TEMP_LOW) {
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_HEATING]);
		return SMF_EVENT_HANDLED;
	}
	return SMF_EVENT_PROPAGATE;
}

static void cooling_exit(void *o)
{
	ARG_UNUSED(o);
	printk("    [COOLING] exit  : cooler OFF\n");
}

/* ======================================================================= */
/* FAULT - top-level leaf (sits OUTSIDE of ACTIVE)                         */
/* ======================================================================= */
static void fault_entry(void *o)
{
	ARG_UNUSED(o);
	printk("   (FAULT)    entry : outputs SAFE, waiting for RESET\n");
}

static enum smf_state_result fault_run(void *o)
{
	struct thermo_ctx *s = o;

	if (s->pending & EVENT_RESET) {
		printk("   (FAULT)    run   : EVENT_RESET -> ACTIVE (initial: IDLE)\n");
		smf_set_state(SMF_CTX(s), &thermo_states[STATE_ACTIVE]);
		return SMF_EVENT_HANDLED;
	}
	if (s->pending & EVENT_SHUTDOWN) {
		printk("   (FAULT)    run   : EVENT_SHUTDOWN -> terminate\n");
		smf_set_terminate(SMF_CTX(s), SM_TERMINATE_OK);
		return SMF_EVENT_HANDLED;
	}
	return SMF_EVENT_HANDLED; /* leaf with no parent */
}

static void fault_exit(void *o)
{
	ARG_UNUSED(o);
	printk("   (FAULT)    exit  : fault cleared\n");
}

/* ----------------------------------------------------------------------- */
/* State table. Requires CONFIG_SMF_ANCESTOR_SUPPORT (parent) and          */
/* CONFIG_SMF_INITIAL_TRANSITION (initial).                                */
/* ----------------------------------------------------------------------- */
static const struct smf_state thermo_states[] = {
	[STATE_ACTIVE] = SMF_CREATE_STATE(active_entry, active_run, active_exit,
					  NULL, &thermo_states[STATE_IDLE]),
	[STATE_IDLE] = SMF_CREATE_STATE(idle_entry, idle_run, NULL,
					&thermo_states[STATE_ACTIVE], NULL),
	[STATE_HEATING] = SMF_CREATE_STATE(heating_entry, heating_run, heating_exit,
					   &thermo_states[STATE_ACTIVE], NULL),
	[STATE_COOLING] = SMF_CREATE_STATE(cooling_entry, cooling_run, cooling_exit,
					   &thermo_states[STATE_ACTIVE], NULL),
	[STATE_FAULT] = SMF_CREATE_STATE(fault_entry, fault_run, fault_exit,
					 NULL, NULL),
};

/* Shared state machine context instance. */
static struct thermo_ctx thermo;

/* Human-readable name for the current leaf state (for the trace banner). */
static const char *leaf_name(const struct smf_ctx *ctx)
{
	const struct smf_state *cur = smf_get_current_leaf_state(ctx);

	if (cur == &thermo_states[STATE_IDLE]) {
		return "IDLE";
	} else if (cur == &thermo_states[STATE_HEATING]) {
		return "HEATING";
	} else if (cur == &thermo_states[STATE_COOLING]) {
		return "COOLING";
	} else if (cur == &thermo_states[STATE_FAULT]) {
		return "FAULT";
	}
	return "ACTIVE";
}

/* ======================================================================= */
/* State-machine thread (consumer)                                         */
/* ======================================================================= */
static K_THREAD_STACK_DEFINE(thermo_stack, 2048);
static struct k_thread thermo_thread_data;

static void thermo_thread(void *a, void *b, void *c)
{
	ARG_UNUSED(a);
	ARG_UNUSED(b);
	ARG_UNUSED(c);

	/* Enters ACTIVE and, via the initial transition, descends to IDLE. */
	smf_set_initial(SMF_CTX(&thermo), &thermo_states[STATE_ACTIVE]);
	printk("    => current state: %s\n", leaf_name(SMF_CTX(&thermo)));

	while (1) {
		/* Block until at least one event is posted. */
		uint32_t evt = k_event_wait(&thermo.events, EVENT_ALL, false,
					    K_FOREVER);

		/* Consume the events we just observed. */
		k_event_clear(&thermo.events, evt);
		thermo.pending = evt;

		if (smf_run_state(SMF_CTX(&thermo)) != 0) {
			printk("    => state machine terminated\n");
			break;
		}

		printk("    => current state: %s\n", leaf_name(SMF_CTX(&thermo)));
	}
}

/* ======================================================================= */
/* Scripted "sensor" producer                                              */
/* ======================================================================= */
struct script_step {
	const char *label;
	uint32_t event;
};

static const struct script_step script[] = {
	{"temp drops below setpoint", EVENT_TEMP_LOW},   /* IDLE   -> HEATING */
	{"temp back inside dead-band", EVENT_TEMP_OK},   /* HEATING-> IDLE    */
	{"temp rises above setpoint", EVENT_TEMP_HIGH},  /* IDLE   -> COOLING */
	{"temp drops below setpoint", EVENT_TEMP_LOW},   /* COOLING-> HEATING (sibling hop) */
	{"sensor fault!", EVENT_FAULT},                  /* (propagates) -> FAULT */
	{"operator reset", EVENT_RESET},                 /* FAULT  -> ACTIVE -> IDLE */
	{"power down", EVENT_SHUTDOWN},                  /* -> terminate */
};

int main(void)
{
	printk("\n=== Zephyr SMF demo: hierarchical thermostat ===\n");

	/* Initialise the event object BEFORE the consumer can wait on it. */
	k_event_init(&thermo.events);

	k_thread_create(&thermo_thread_data, thermo_stack,
			K_THREAD_STACK_SIZEOF(thermo_stack), thermo_thread,
			NULL, NULL, NULL, 7, 0, K_NO_WAIT);
	k_thread_name_set(&thermo_thread_data, "thermo_sm");

	/* Let the SM thread print its initial-state banner first. */
	k_msleep(500);

	for (size_t i = 0; i < ARRAY_SIZE(script); i++) {
		k_msleep(1500);
		printk("\n-> EVENT: %s\n", script[i].label);
		k_event_post(&thermo.events, script[i].event);
	}

	return 0;
}
