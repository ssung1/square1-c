## Why

Defining a reusable Block structure enables the project to represent game blocks with properties including position, shape, and color information. This provides a foundation for building block-based game logic and ensures consistent data representation across the codebase.

## What Changes

- Add a new Block structure definition in dedicated source files (`block.h` and `block.c`).
- Define the structure with five properties: position (integer 0-11), shape (Shape enum), faceColor (BlockColor enum), sideColor1 (BlockColor enum), and sideColor2 (BlockColor enum).
- Ensure the structure declaration is available for inclusion by other compilation units.
- Keep this change scoped to structure definition only, without adding behavior or functions.

## Capabilities

### New Capabilities
- `block-struct-definition`: Introduces a canonical `Block` structure with position, shape, and color properties for consistent block representation across the codebase.

### Modified Capabilities
- None.

## Impact

- Affected code: adds new top-level source files `block.h` and `block.c`.
- Build/developer workflow: no additional dependencies; standard C toolchain remains sufficient.
- APIs/systems: integrates existing Shape and BlockColor enums into a composed data type.
