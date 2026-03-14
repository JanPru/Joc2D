# Joc2D

Joc2D is a C++ 2D game development workspace containing multiple OpenGL learning projects and two larger game projects built with Visual Studio.

## Overview

This repository includes:

- **OpenGL practice projects** in `OpenGL/` (window setup, primitives, uniforms, transforms, textures, text rendering).
- **2D game prototypes** in `2DGame/`:
  - `01-TBE`: tile-based engine foundation.
  - `02-Bubble`: a more complete game with player, enemies, bosses, power-ups, GUI, and effects.
- **Shared graphics and assets** (`.xcf`, `.tmx`, `.tsx`, maps, and sprite resources).
- **Third-party libraries** in `libs/` (GLFW, GLEW, GLM, FreeType, SOIL).

## Main Folder Structure

```text
Joc2D/
  2DGame/
    01-TBE/
    02-Bubble/
  OpenGL/
    01-window/
    02-primitives/
    03-uniforms/
    04-transforms/
    05-textures/
    06-text/
  libs/
  assets and map files
```

## Requirements

- Windows
- Visual Studio (with C++ workload)
- OpenGL-compatible GPU drivers

## How To Build

1. Open the `.sln` file for the project you want to run (for example, `2DGame/02-Bubble/02-Bubble.sln`).
2. Select build configuration (`Debug` or `Release`).
3. Build the solution.
4. Run the startup project from Visual Studio.

## Notes

- Make sure asset paths are correct relative to each executable project.
- If a project fails to link, verify include/library paths for dependencies under `libs/`.

## License

No explicit license file is currently included in this workspace.
Add a `LICENSE` file if you plan to distribute the project publicly.
