# SUPER LIBRARY

**SUPER LIBRARY** is an independent Windows frontend for **Snes9x**, designed to turn a local Super Nintendo collection into a console-like visual library.

![SUPER LIBRARY interface](docs/images/super-library-interface.png)

## Current release: v1.0.3

Version 1.0.3 consolidates the current stable line with:

- visual SNES-inspired game carousel;
- mouse, keyboard and SDL-compatible gamepad navigation;
- Favorites, Recently Played and instant search;
- managed Snes9x + slang-shaders installation, or use an existing Snes9x;
- ROM folder selection, collection import and exact-payload deduplication;
- Standard / PT-BR translation / MSU-1 managed library layout;
- in-game **Quick Menu**;
- manual **SAVE PROGRESS** and **LOAD PROGRESS**;
- **CONTINUE PLAYING?** only after the player explicitly creates a progress point;
- in-game video-filter/shader browsing and live preview when the Snes9x build can be safely validated;
- in-game Player 1 controller setup when the supported bridge can be safely matched;
- controller diagnostics, USB/Bluetooth hot-plug and reconnect handling;
- no Python installation required for end users.

**Commercial ROMs are not included, provided or downloaded by SUPER LIBRARY.**

## First run

1. Install the v1.0.3 Setup from GitHub Releases.
2. Use **SELECT → Choose Folder** to select your existing ROM library, or **Import Collection** to create a managed organized copy.
3. Use **Y → Download Snes9x and Shaders**, or choose an existing Snes9x installation.
4. Select a game and press **A / Cross**.

## In-game Quick Menu

### Modern controllers

Press **R3** while a game is running.

R2/RT is deliberately left untouched for the game itself.

### Classic controllers without R3

Press **START + SELECT** together to open the same Quick Menu.

The Quick Menu provides:

- **RESUME GAME**
- **SAVE PROGRESS**
- **LOAD PROGRESS**
- **VIDEO FILTERS**
- **CONTROLLER SETTINGS**
- **RETURN TO LIBRARY**

Returning to the library does **not** silently create a save. The next-launch **CONTINUE PLAYING?** prompt appears only when the player explicitly used SAVE PROGRESS.

## Launcher controller mapping

| Action | Xbox / XInput | PlayStation |
|---|---|---|
| Navigate | D-Pad / left stick | D-Pad / left stick |
| Play | A | Cross (×) |
| Back | B | Circle (○) |
| Smart Refresh | X | Square (□) |
| Snes9x Manager | Y | Triangle (△) |
| Music | LT | L2 |
| Previous page | LB | L1 |
| Next page | RB | R1 |
| Favorite | L3 | L3 |
| Library view | R3 | R3 |
| Snes9x configuration | Menu / Start | Options |
| Close frontend | View / Back | Share / Create |

During gameplay, **R3 opens the Quick Menu** and **R2/RT remains available to the game**.

Compatibility depends on Windows/SDL recognition. Xbox/XInput, DualShock/DualSense, 8BitDo and many generic USB/Bluetooth controllers are typical targets.

## Managed ROM layout

A managed import can organize the user's own collection as:

```text
Snes9x\Roms\
├── Standard\
│   ├── USA\
│   ├── Europe\
│   ├── Japan\
│   └── Other\
├── Translations\
│   └── PT-BR\
└── MSU-1\
```

Ordinary games are written as validated single-ROM ZIPs when appropriate. Native `.msu1` packages are handled separately so their `program.rom` and streamed assets are not flattened into an ordinary ROM ZIP.

## Snes9x and shaders

SUPER LIBRARY can download the current Windows Snes9x release from the official Snes9x GitHub repository and install slang-shaders from libretro, or it can use an existing Snes9x installation.

Managed repair/removal operations protect the user's ROM tree before changing emulator files.

## Security and distribution

This repository is a **binary release and documentation repository**. The proprietary SUPER LIBRARY application source code is not distributed under an open-source license.

Official releases use published SHA-256 information and GitHub Artifact Attestation as integrity layers. This does not replace Authenticode, so Windows may still show `Unknown publisher`/SmartScreen warnings for unsigned builds.

SUPER LIBRARY does not disable or bypass antivirus software.

See [SECURITY.md](SECURITY.md) and [LICENSE.md](LICENSE.md).

## Independent project

SUPER LIBRARY is not affiliated with or endorsed by Nintendo, Snes9x, libretro, LaunchBox or other third parties referenced by the project. Trademarks and third-party software remain the property of their respective owners.

See the full Portuguese documentation in [README.md](README.md).
