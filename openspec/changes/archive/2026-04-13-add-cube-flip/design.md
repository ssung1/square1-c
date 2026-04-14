## Context

The Square-1 puzzle's flip operation slices the puzzle along the plane through positions 0 and 6 and swaps the right half (positions 0–5) between the top and bottom faces. The simulation already has:
- `CubeFace` with `Block` arrays, positions 0–11, sizes 1 (triangle) or 2 (kite)
- `Cube` with `topFace`, `bottomFace`, `history`
- `isFlippable` to verify the cut positions are on block boundaries
- `cloneCube` (internal) for deep-copying a Cube
- `rotateClubFaceClockwise` for deep-copying a CubeFace

**Position model:** A block's `position` is the index of its counter-clockwise edge. A block at position `p` with size `s` occupies arc `[p, p+s)` (mod 12).

**Reflection formula:** Reflecting a block about the 3–9 axis maps arc `[p, p+s)` to `[6-p-s, 6-p)`, so the new counter-clockwise edge (new position) is `6 - p - s`. This is always non-negative for blocks where 0 ≤ p < 6 and size 1 or 2 (min result is 6-5-2=−1... except wait: a kite at position 5 has size 2 so 6-5-2=-1).

Wait — a kite at position 4 (size 2) occupies [4,6). That's right up against the cut. A kite at position 5 (size 2) would occupy [5,7), crossing position 6, which means the face is NOT flippable. So `isFlippable` guards against this. For all valid flippable configurations: blocks in the right half satisfy 0 ≤ p < 6 and p+s ≤ 6, so 6-p-s ≥ 0. The reflected position is always in [0, 6).

## Goals / Non-Goals

**Goals:**
- Produce a new `Cube *` where:
  - Right-half blocks (0 ≤ position < 6) of the old top face appear in the new bottom face, reflected
  - Right-half blocks of the old bottom face appear in the new top face, reflected
  - Left-half blocks (6 ≤ position ≤ 11) of each face remain on that same face, unchanged
- Return `NULL` for `NULL` input
- Never modify the input `Cube`

**Non-Goals:**
- Explicitly checking `isFlippable` inside `flip` — that is the caller's responsibility
- Updating `history`

## Decisions

### Build the new faces block-by-block

For each of the two new faces, collect:
1. The left-half blocks from the **same** face (unchanged position)
2. The right-half blocks from the **other** face (reflected position: `6 - p - size`)

Allocate new `CubeFace` structs with combined block count and populate them.

**Rationale:** Clean and direct. Avoids using `rotateClubFaceClockwise` as a clone step followed by mutation; instead constructs the faces from scratch with correct positions.

### Reflected position formula

For a block with `position = p` and `shape.size = s`:
```
reflected_position = 6 - p - s
```

**Derivation:** The block occupies arc `[p, p+s)`. Reflecting over the 3–9 axis maps each angular point `x` to `6 - x`. The reflected arc is `[6-(p+s), 6-p)`, so the new counter-clockwise edge is `6 - p - s`.

**Validity:** For a flippable face, all right-half blocks satisfy `p + s ≤ 6`, so `6 - p - s ≥ 0`.

### sideColor2 deep-copy

The `CubeFace` memory layout has `sideColor2` arrays stored contiguously after the blocks. When building the new faces, allocate with the same `blockBytes + sideColor2Bytes` pattern and copy `sideColor2` values explicitly, updating each block's `sideColor2` pointer to point into the new storage.

**Rationale:** Same pattern already used throughout `cube-face.c` and `cube.c`.

### history

Copy the existing history string unchanged (same as `cloneCube` does).

## Risks / Trade-offs

- [Risk] face not flippable but `flip` called anyway → positions outside [0,6) could produce negative or wrong reflected positions → Mitigation: document that `isFlippable` must be checked before calling; no in-function guard needed (consistent with immutable API contract).
- [Risk] NULL face pointers inside a non-NULL Cube → Mitigation: `isFaceFlippable` would have returned 0, so callers using `isFlippable` will never reach this state. No extra NULL check per face needed.
