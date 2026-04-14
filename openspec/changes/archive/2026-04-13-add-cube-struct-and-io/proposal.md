## Why

To simulate Square-1 state at the puzzle level, the project needs a first-class Cube type that holds both faces and move history. This enables higher-level operations and readable full-state output for debugging and tests.

## What Changes

- Add a new `Cube` data structure with `topFace`, `bottomFace`, and `history` fields.
- Add `cubeFromString(topFace, bottomFace)` to build a cube from two face definitions using `cubeFaceFromString`.
- Add `cubeToString(cube)` to serialize cube state as three lines: history, top face string, bottom face string.
- Reuse existing face/block string conversion logic, especially `cubeFaceToString`.

## Capabilities

### New Capabilities
- `cube-struct-and-io`: Define cube-level data and support parsing/serialization of full cube state.

### Modified Capabilities
- None.

## Impact

- New module files: `cube.h`, `cube.c`.
- Affected existing files: `unit-test.c`, `Makefile` (if needed for new source inclusion).
- New public APIs: `cubeFromString`, `cubeToString`.
- No external dependencies.
