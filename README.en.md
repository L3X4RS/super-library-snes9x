# SUPER LIBRARY

**SUPER LIBRARY** is an independent Windows frontend for **Snes9x**, designed to turn a local Super Nintendo ROM collection into a console-like visual library.

![SUPER LIBRARY interface](docs/images/super-library-interface.png)

## Highlights

- visual SNES-inspired game carousel;
- mouse, keyboard and SDL-compatible gamepad navigation;
- managed Snes9x + slang-shaders installation, or use an existing Snes9x;
- ROM folder selection, collection import and exact payload deduplication;
- PT-BR / USA / Europe / Japan / Auto import profiles;
- non-destructive organized copy creation;
- missing cover search and smart library maintenance;
- music, UI sounds and interactive LED;
- hold **R1/RB for about one second while playing** to close Snes9x and return to the frontend;
- no Python installation required for end users.

## First run

1. Install `SUPER_LIBRARY_Setup_v1.0.0.exe` from GitHub Releases.
2. Use **SELECT → Choose Folder** to select your own ROM library.
3. Use **Y → Download Snes9x and Shaders**, or choose an existing Snes9x installation.
4. Select a game and press **A / Cross**.

**Commercial ROMs are not included or provided.**

## Controller mapping

- D-Pad / left stick: navigate
- A / Cross: Play
- B / Circle: Back
- X / Square: Smart Refresh
- Y / Triangle: Snes9x Manager
- LB / L1: music on/off
- RB / R1: +5 games; hold while playing to exit Snes9x
- Start / Options: open Snes9x configuration
- View/Back / Share/Create: close frontend

Compatibility depends on Windows/SDL recognition. Xbox/XInput, DualShock/DualSense, 8BitDo and many generic USB/Bluetooth controllers are typical targets.

## Independent project

SUPER LIBRARY is not affiliated with or endorsed by Nintendo, Snes9x or libretro. Nintendo/SNES related trademarks and third-party software remain the property of their respective owners.

See the full Portuguese documentation in [README.md](README.md).
