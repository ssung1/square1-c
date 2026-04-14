## Context

The Square-1 puzzle can perform a "flip" that slices the puzzle along a vertical plane through positions 0 and 6 and swaps the right half (positions 0–6, non-inclusive) between the top and bottom faces. The simulation already has `CubeFace` (with `Block` positions and `Shape` sizes) and `Cube` (with `topFace` and `bottomFace`). Before implementing the flip itself, the simulation needs a predicate that answers: "Is the flip currently legal?"

A flip is legal only when no block straddles either cut position (0 or 6). A block with `position = p` and `shape.size = s` occupies positions `p` through `p + s - 1` (all modulo 12). The cut positions 0 and 6 must each coincide exactly with the counter-clockwise edge of some block — which means no block's interior spans position 0 or position 6.

## Goals / Non-Goals

**Goals:**
- Implement `isFlippable(const Cube *cube)` returning `1` if both faces pass the flippability check, `0` otherwise.
- A face is flippable when every block's occupied range does not span position 0 or position 6 as an interior position (i.e., 0 and 6 must each be the start position of some block, or unoccupied, but never the interior of a block).

**Non-Goals:**
- Implementing the actual flip operation (future change).
- Validating that the face's total block coverage equals 12 (assumed valid from `cubeFaceFromString`).
- Handling NULL safety beyond a simple NULL guard (NULL → 0).

## Decisions

### One helper per face, one top-level function for Cube

`isFaceFlippable(const CubeFace *face)` is a private helper in `cube.c` that checks a single face. `isFlippable(const Cube *cube)` calls the helper on both faces.

**Rationale:** Clean separation of concerns; future code may need to query a single face. Keeping the helper non-public avoids premature API exposure.

### Cut-position check algorithm

For each block in the face, compute whether the block's occupied range spans position 0 or position 6 as an interior (non-start) position:

```
for each block b:
    for offset = 1 to b.shape.size - 1:
        occupied = (b.position + offset) % 12
        if occupied == 0 or occupied == 6: return false  // not flippable
return true
```

Offset starts at 1 so the block's own start position is not tested (start positions are allowed at the cut).

**Rationale:** Simple O(n) scan, correct for wrap-around due to `% 12`, no sorting or sorting-based lookup needed.

**Alternative considered:** Build a 12-element occupancy array and check slots 0 and 6 for the "middle of a block" flag. More memory, same correctness; rejected as overengineered for ≤12 blocks.

## Risks / Trade-offs

- [Risk] Incorrect modular arithmetic for blocks near position 11 that wrap around to 0 → Mitigation: The `% 12` in the offset loop handles wrap-around correctly.
- [Risk] A Cube with a NULL topFace or bottomFace pointer → Mitigation: `isFaceFlippable` returns `0` on NULL input; `isFlippable` propagates via `&&`.

## Migration Plan

No migration required. New exported symbol `isFlippable` is purely additive.
