## Why

The Square-1 puzzle has a "flip" operation that transfers blocks between the top and bottom faces. Before a flip can be performed, the simulation must be able to determine whether it is currently legal — i.e., whether the cut plane (positions 0 and 6) falls cleanly on block boundaries and not through the middle of a block. This capability is a prerequisite for any future flip implementation.

## What Changes

- Add `isFlippable(const Cube *cube)` in `cube.c` / `cube.h` that returns `1` (true) if both faces of the cube are in a state that allows flipping, and `0` (false) otherwise.
- A face is flippable when position `0` and position `6` each fall exactly on the counter-clockwise edge of some block (i.e., no block straddles either cut position).

## Capabilities

### New Capabilities

- `cube-is-flippable`: Predicate function on `Cube` that checks whether the flip operation is currently legal on both faces.

### Modified Capabilities

<!-- None -->

## Impact

- `cube.h` — new function declaration
- `cube.c` — new function implementation
- `unit-test.c` — new tests covering flippable and non-flippable face configurations
