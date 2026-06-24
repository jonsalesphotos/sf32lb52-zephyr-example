.. zephyr:code-sample:: smf-thermostat
   :name: SMF Hierarchical Thermostat
   :relevant-api: smf

   Build a hierarchical state machine with the State Machine Framework (SMF).

Overview
********

This sample models a thermostat controller as a **hierarchical state machine**
(HSM) built on Zephyr's :ref:`State Machine Framework <smf>`. It is meant as a
teaching example: a single, self-driving firmware that exercises every major
SMF feature and prints a readable trace of every ``entry`` / ``run`` / ``exit``
action.

A rendered, interactive state diagram is provided next to this README:

   ``state_machine.html`` -- open it in any web browser (no internet needed).

State hierarchy
***************

::

   ACTIVE  (superstate)                  shared FAULT / SHUTDOWN handling
   |
   +-- IDLE      (initial child)         heater OFF, cooler OFF
   +-- HEATING                           heater ON
   +-- COOLING                           cooler ON

   FAULT   (top-level leaf, outside ACTIVE)

Events (delivered through a ``k_event``):

==================  ====================================================
Event               Meaning / effect
==================  ====================================================
``EVENT_TEMP_LOW``  below setpoint  -> go HEATING
``EVENT_TEMP_HIGH`` above setpoint  -> go COOLING
``EVENT_TEMP_OK``   back in range   -> go IDLE
``EVENT_FAULT``     handled by ACTIVE for any substate -> go FAULT
``EVENT_RESET``     in FAULT        -> go ACTIVE (descends to IDLE)
``EVENT_SHUTDOWN``  anywhere        -> terminate the state machine
==================  ====================================================

What it demonstrates
********************

Hierarchy + initial transition
   ``ACTIVE`` is the parent of ``IDLE`` / ``HEATING`` / ``COOLING`` and declares
   ``IDLE`` as its initial child. ``smf_set_initial(&ACTIVE)`` therefore runs
   ``ACTIVE.entry`` and then descends to run ``IDLE.entry``.

Run propagation (SMF v0.2.0 API)
   A leaf ``run`` action returns ``SMF_EVENT_PROPAGATE`` for events it does not
   handle. The framework then runs the parent ``ACTIVE.run``, which is where
   ``EVENT_FAULT`` and ``EVENT_SHUTDOWN`` are handled once, for all children.
   A leaf that *does* handle an event returns ``SMF_EVENT_HANDLED`` (or calls
   ``smf_set_state()``), which stops propagation.

LCA / sibling optimization
   Hops between siblings (``IDLE`` <-> ``HEATING`` <-> ``COOLING``) do **not**
   re-run ``ACTIVE``'s ``entry`` / ``exit`` because their Least Common Ancestor
   is ``ACTIVE`` itself. Leaving the hierarchy to ``FAULT`` (whose parent is
   ``NULL``) *does* run ``ACTIVE.exit``; ``EVENT_RESET`` back into ``ACTIVE``
   re-runs ``ACTIVE.entry`` and the initial transition to ``IDLE``.

Termination
   ``smf_set_terminate(ctx, 1)`` ends the machine. The value **must be
   non-zero** -- ``smf_run_state()`` returns it, and the run loop treats
   non-zero as "stop". Returning ``0`` would spin.

Event-driven structure
   ``main()`` plays a scripted list of simulated sensor events into a
   ``k_event``; a dedicated thread waits on that event, then calls
   ``smf_run_state()``. This is the production pattern: an ISR or another
   thread posts events, the state-machine thread consumes them.

Requirements
************

* A board with a serial console. The sample is set up for the
  ``sf32lb52_hspi`` board; ``boards/sf32lb52_hspi.overlay`` pins the console to
  ``usart1`` at 1,000,000 baud.

Building and Running
********************

From the west workspace root (adjust paths for your checkout):

.. code-block:: powershell

   west build --build-dir e:/sf32lb52-zephyr-example/application/samples/smf_thermostat/build ^
       e:/sf32lb52-zephyr-example/application/samples/smf_thermostat ^
       --pristine --board sf32lb52_hspi/sf32lb525uc6 ^
       -- -DBOARD_ROOT=e:/sf32lb52-zephyr-example/application

Flash and open the serial port at 1000000 baud:

.. code-block:: powershell

   west flash -d e:/sf32lb52-zephyr-example/application/samples/smf_thermostat/build --port=COM7

Sample Output
*************

.. code-block:: console

   === Zephyr SMF demo: hierarchical thermostat ===
      (ACTIVE)   entry : controller armed
       [IDLE]    entry : heater OFF, cooler OFF
       => current state: IDLE

   -> EVENT: temp drops below setpoint
       [HEATING] entry : heater ON
       => current state: HEATING

   -> EVENT: temp back inside dead-band
       [HEATING] exit  : heater OFF
       [IDLE]    entry : heater OFF, cooler OFF
       => current state: IDLE

   -> EVENT: temp rises above setpoint
       [COOLING] entry : cooler ON
       => current state: COOLING

   -> EVENT: temp drops below setpoint
       [COOLING] exit  : cooler OFF
       [HEATING] entry : heater ON
       => current state: HEATING

   -> EVENT: sensor fault!
      (ACTIVE)   run   : EVENT_FAULT -> FAULT
       [HEATING] exit  : heater OFF
      (ACTIVE)   exit  : controller disarmed
      (FAULT)    entry : outputs SAFE, waiting for RESET
       => current state: FAULT

   -> EVENT: operator reset
      (FAULT)    run   : EVENT_RESET -> ACTIVE (initial: IDLE)
      (FAULT)    exit  : fault cleared
      (ACTIVE)   entry : controller armed
       [IDLE]    entry : heater OFF, cooler OFF
       => current state: IDLE

   -> EVENT: power down
      (ACTIVE)   run   : EVENT_SHUTDOWN -> terminate
       => state machine terminated

Notice in the "sensor fault!" step that ``HEATING.run`` propagated the event up
to ``ACTIVE.run``; and that the "temp drops below setpoint" hop from ``COOLING``
to ``HEATING`` did not print any ``ACTIVE`` entry/exit (sibling optimization),
while the trip through ``FAULT`` did.

Files
*****

==========================  ============================================
File                        Purpose
==========================  ============================================
``src/main.c``              The state machine, states and event producer
``prj.conf``                Enables ``SMF`` + ancestor + initial + events
``state_machine.html``      Rendered state diagram and walkthrough
``boards/*.overlay``        Console pin-out for the board
==========================  ============================================
