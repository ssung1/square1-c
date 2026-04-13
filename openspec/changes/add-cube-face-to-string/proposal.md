## Why

CubeFace currently has no string representation, making it difficult to inspect or compare face state during development and testing. Creating `cubeFaceToString` provides visibility into the full face configuration in a format that mirrors the input parsing.

## What Changes

- Add a `cubeFaceToString` function in `cube-face.c` that produces a space-delimited string representation of all blocks in a CubeFace, ordered by ascending position.
- Each block is represented using the existing `blockToString` function, which encodes face and side colors in 2-3 character format.
- Unit tests verify correct ordering, spacing, and handling of edge cases (empty faces, NULL input).

## Capabilities

### New Capabilities
- `cube-face-to-string`: Convert a CubeFace to a space-delimited string with blocks ordered by position, reusing blockToString formatting.

### Modified Capabilities
- None.

## Impact

- Affected code: `cube-face.h`, `cube-face.c`, `unit-test.c`.
- API impact: new public function `cubeFaceToString` in the CubeFace interface.
- No new external dependencies.
