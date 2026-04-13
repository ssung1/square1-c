## Why

CubeFace currently supports parsing from a string but does not support rotating block positions after construction. Rotation is core behavior for a Square-1 simulation, and adding it now enables move application without rebuilding faces from scratch.

## What Changes

- Add a CubeFace rotation function in `cube-face.c` to rotate all block positions counterclockwise by a caller-provided count.
- Define wrapping semantics on a 12-position ring so positions stay in the range `0..11`.
- Add unit tests that verify rotation by common counts and wraparound cases (for example: `12 -> 0`, `13 -> 1`).

## Capabilities

### New Capabilities
- `cube-face-rotation`: Rotate existing CubeFace blocks counterclockwise by a specified number of positions using modulo-12 wraparound.

### Modified Capabilities
- None.

## Impact

- Affected code: `cube-face.h`, `cube-face.c`, `unit-test.c`.
- API impact: new CubeFace rotation function exposed in the CubeFace interface.
- No new external dependencies.
