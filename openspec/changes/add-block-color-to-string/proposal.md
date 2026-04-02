## Why

The project uses the `BlockColor` enum to represent block colors, but there is no way to convert a `BlockColor` value to a human-readable string. Adding a conversion function in a dedicated `block-color.c` enables display, debugging, and serialization of color values without duplicating logic across the codebase.

## What Changes

- Add a new source file `block-color.c` containing a `blockColorToString` function.
- Update `block-color.h` to declare the `blockColorToString` function.
- The function maps each `BlockColor` member to a single-character string:
  - `BLOCK_COLOR_WHITE` → `"w"`
  - `BLOCK_COLOR_GREEN` → `"g"`
  - `BLOCK_COLOR_YELLOW` → `"y"`
  - `BLOCK_COLOR_RED` → `"r"`
  - `BLOCK_COLOR_BLUE` → `"b"`
  - `BLOCK_COLOR_ORANGE` → `"o"`

## Capabilities

### New Capabilities
- `block-color-to-string`: Introduces a `blockColorToString` function that converts a `BlockColor` enum value to its single-character string representation.

### Modified Capabilities
- None.

## Impact

- Affected code: adds `block-color.c`; updates `block-color.h` with function declaration.
- Build/developer workflow: `Makefile` must include `block-color.c` in the build.
- APIs/systems: `blockColorToString` becomes available to any module that includes `block-color.h`.
