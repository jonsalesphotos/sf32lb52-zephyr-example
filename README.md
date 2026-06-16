# SF32LB52 Zephyr Example

This repository contains a Zephyr demo application for SiFli SF32 series
devices, currently targeting the `sf32lb52_hspi` board.

The demo is based on Zephyr's workspace application layout and uses a west
manifest to pull the SiFli Zephyr downstream tree and required modules.

## Project Purpose

This project is intended as a small starting point for SF32LB52 development:

- `app/` contains the demo firmware application.
- `boards/sifli/sf32lb52_hspi/` contains the custom board definition.
- `west.yml` selects the OpenSiFli Zephyr downstream and required modules.

The current application prints the selected Zephyr board target once per
second.

## Target Board

- Board: `sf32lb52_hspi`
- Full name: HSPI-SF32LB52 (Huangshan Pi)
- SoC: `sf32lb525uc6`
- Vendor: SiFli

## Getting Started

Install the standard Zephyr development tools first, including Python, CMake,
Ninja, a supported ARM toolchain, and `west`.

```shell
pip install west
```

### Initialize a New Workspace

```shell
west init -m https://github.com/jonsalesphotos/sf32lb52-zephyr-example --mr main sf32lb52-zephyr-workspace
cd sf32lb52-zephyr-workspace
west update
```

After `west update`, the workspace will contain this application repository,
the OpenSiFli Zephyr downstream tree, and the modules allowed by `west.yml`.

### Build

From the west workspace root:

```shell
west build -b sf32lb52_hspi sf32lb52-zephyr-example/app
```

To rebuild from scratch:

```shell
west build -b sf32lb52_hspi sf32lb52-zephyr-example/app -p always
```

Windows example from this workspace:

```powershell
west build --build-dir e:/sf32lb52-zephyr-example/application/app/build e:/sf32lb52-zephyr-example/application/app --pristine --board sf32lb52_hspi/sf32lb525uc6 -- -DNCS_TOOLCHAIN_VERSION="NONE" -DDEBUG_THREAD_INFO=On -DCONFIG_DEBUG_OPTIMIZATIONS=y -DCONFIG_DEBUG_THREAD_INFO=y -DBOARD_ROOT=e:/sf32lb52-zephyr-example/application
```

### Flash

After a successful build, flash with:

```shell
west flash
```

Windows example using the generated build directory:

```powershell
west flash -d e:\sf32lb52-zephyr-example\application\app\build --port=COM7
```

Replace `COM7` with the serial port assigned to the board. To erase all flash
regions before programming, add `--erase`:

```powershell
west flash -d e:\sf32lb52-zephyr-example\application\app\build --port=COM7 --erase
```

The exact flashing behavior depends on the board runner and debug adapter
configuration available in the local Zephyr environment.

### VS Code Tasks

This repository keeps a Git-tracked VS Code task template at
`vscode/tasks.json`. The local `.vscode/tasks.json` file can use the same
tasks for `SF32: Build`, `SF32: Flash`, and `SF32: Erase and Flash`, while
`.vscode/` stays ignored for editor-local settings.

## Repository Notes

This repository intentionally does not include generated build output. Local
build directories such as `app/build` are ignored by Git.

The original template GitHub Actions workflows were removed because this demo
does not use the Nordic CI setup.
