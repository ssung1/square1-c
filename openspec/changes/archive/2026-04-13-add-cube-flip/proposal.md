## Why

The Square-1 simulation has `isFlippable` to detect when a flip is legal, but no way to actually perform it. The flip is the fundamental operation that mixes blocks between the top and bottom faces, and is required to model real puzzle moves.

## What Changes

- Add `flip(const Cube *cube)` in `cube.c` / `cube.h` that returns a new `Cube *` representing the state after a flip.
- Blocks in the right half (position 0 inclusive to position 6 non-inclusive) of the top face move to the bottom face (and vice versa), with each block's position reflected about the position 3–9 axis.
- The left half blocks (position 6 to 11) remain on their original face, unchanged.
- The function follows the immutable pattern: the input `Cube` is never modified.
- Calling `flip` on a non-flippable cube is undefined; callers must check `isFlippable` first. The function returns `NULL` for NULL input.

## Capabilities

### New Capabilities

- `cube-flip`: Immutable flip operation on a Cube that exchanges and reflects the right-half blocks between top and bottom faces.

### Modified Capabilities

## Impact

- `cube.h` — new function declaration: `Cube *flip(const Cube *cube)`
- `cube.c` — new function implementation
- `unit-test.c` — new tests for flip correctness, immutability, and NULL guard
