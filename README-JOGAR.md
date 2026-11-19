# EmberCloud: the game, ready to run

A working copy of EmberEngine with only the files the game reads (the user, 2026-11-18). No source videos, no cut frames, no old builds.

1. Clone this repository.
2. Double-click `JOGAR.bat`. The first time it puts the big packs back together (`JUNTAR.bat`, a few minutes: GitHub refuses a file over
   100 MiB, so `battle.pak`, the ground and mesh packs are stored as `name.part001`, `name.part002`, ...; the result is checked against
   `PARTES.json`). The joined files are ignored by git (`.gitignore`).
3. Windows, a Vulkan GPU.

`overworld-minimap.patch` and `apps/sandbox/OverworldMinimap.h` are an earlier update kept here untouched.
