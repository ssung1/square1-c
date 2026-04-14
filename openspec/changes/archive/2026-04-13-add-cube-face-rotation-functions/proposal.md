## Why

The Cube model currently stores top and bottom faces but does not provide cube-level operations to rotate either face directly. Adding explicit top/bottom rotation functions makes cube manipulation clearer and supports higher-level Square-1 move composition.

## What Changes

- Add a function to rotate the cube top face.
- Add a function to rotate the cube bottom face.
- Each function updates the corresponding face of a Cube using the existing face-rotation behavior.
- Extend unit tests to verify top/bottom rotation APIs and ensure only the target face is changed.

## Capabilities

### New Capabilities
- `cube-face-rotation-functions`: Provide Cube APIs to rotate top and bottom faces independently.

### Modified Capabilities
- None.

## Impact

- Affected code: `cube.h`, `cube.c`, `unit-test.c`.
- Reused dependency: existing face rotation function in `cube-face.c`.
- No external dependencies.
