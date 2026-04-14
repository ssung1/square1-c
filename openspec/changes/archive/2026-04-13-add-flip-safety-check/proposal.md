## Why

`flip` currently assumes callers only invoke it when the cube is flippable. Adding an internal safety guard prevents invalid state transitions and makes `flip` safer to call directly.

## What Changes

- Update `flip` in `cube.c` to check `isFlippable(cube)` before performing the operation.
- If the cube is not flippable, `flip` aborts and returns `NULL`.
- Preserve existing `NULL` behavior and immutable semantics.

## Capabilities

### New Capabilities

### Modified Capabilities
- `cube-flip`: `flip` now enforces a precondition internally and returns `NULL` for non-flippable cube states.

## Impact

- `cube.c`: add precondition check in `flip`
- `unit-test.c`: add/adjust tests for non-flippable input behavior
