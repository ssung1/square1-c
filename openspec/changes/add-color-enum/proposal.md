## Why

Defining a shared BlockColor enum early provides a stable, typed vocabulary for future C code that needs to represent color states. Adding it now avoids duplicated constants and inconsistent naming as the project grows.

## What Changes

- Add a new Color enum in a dedicated source file (`block-color.h` or `block-color.c`, with preference for a header if shared usage is expected).
- Define an initial set of enum members for common colors.
- Ensure the enum declaration is available for inclusion by other compilation units.
- Keep this change scoped to enum definition only, without adding behavior.
- The members of the BlockColor enum shall include only these:
  - BLOCK_COLOR_WHITE
  - BLOCK_COLOR_GREEN
  - BLOCK_COLOR_YELLOW
  - BLOCK_COLOR_RED
  - BLOCK_COLOR_BLUE
  - BLOCK_COLOR_ORANGE

## Capabilities

### New Capabilities
- `color-enum-definition`: Introduces a canonical `BlockColor` enum in a dedicated file for consistent color representation across the codebase.

### Modified Capabilities
- None.

## Impact

- Affected code: adds a new top-level color enum file (`block-color.h` or `block-color.c`).
- Build/developer workflow: no additional dependencies; standard C toolchain remains sufficient.
- APIs/systems: creates a shared type contract that future modules can include.
