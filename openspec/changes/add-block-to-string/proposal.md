## Why

The project can already convert a `BlockColor` to a string, but has no way to represent an entire `Block` as a string. Adding `blockToString` in `block.c` enables compact textual representation of blocks for debugging, display, and serialization. This change also makes `sideColor2` an optional (nullable) field to correctly model blocks that have only one side color.

## What Changes

- Add a `blockToString` function to `block.c` and declare it in `block.h`.
- The function concatenates the string representations of `faceColor`, `sideColor1`, and (if present) `sideColor2`, in that order.
- **BREAKING**: Change the `sideColor2` field in the `Block` struct from `BlockColor` (value) to `const BlockColor *` (pointer), making it nullable.
- Update `main.c` to adapt to the changed `sideColor2` field type.

## Capabilities

### New Capabilities
- `block-to-string`: Introduces a `blockToString` function that converts a `Block` to a short string by concatenating the string forms of its color fields.

### Modified Capabilities
- `block-struct-definition`: The `sideColor2` field changes from `BlockColor` to `const BlockColor *` to support optional (nullable) values.

## Impact

- Affected code: `block.h` (struct field type change, new function declaration), `block.c` (new function), `main.c` (struct literal must pass pointer for `sideColor2`).
- Build/developer workflow: no new dependencies; existing `Makefile` targets remain sufficient.
- APIs/systems: any caller that passes a `BlockColor` value for `sideColor2` must now pass a pointer (or `NULL`). This is a breaking change to the `Block` struct.
