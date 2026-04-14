## Why

When displaying a `CubeFace` as a string, blocks are sorted by position and output in order starting from the lowest position. A face with the first block at position 0 and a face with the first block at position 1 can produce visually identical output strings, creating ambiguity. Adding a prefix marker allows callers to distinguish these cases and preserve positional context.

## What Changes

- Modify `cubeFaceToString` to return a string prefixed with `*` when the block with the lowest position is at position 1 (rather than position 0).
- The prefix is added only when the minimum position is 1; all other cases remain unchanged.

## Capabilities

### New Capabilities

### Modified Capabilities

- `cube-face-to-string`: Output format now includes optional `*` prefix when lowest block position is 1.

## Impact

- `cube.h` — no change (signature unchanged)
- `cube.c` — `cubeFaceToString` implementation updated
- `unit-test.c` — new tests for prefix behavior
