## ADDED Requirements

### Requirement: isFlippable predicate
`isFlippable(const Cube *cube)` SHALL return `1` (true) when both the top face and the bottom face of the cube are in a flippable state, and `0` (false) otherwise.

A `CubeFace` is flippable when position `0` and position `6` are NOT interior positions of any block. An interior position of a block is any position occupied by the block other than its counter-clockwise start position (i.e., `(block.position + offset) % 12` for `1 <= offset < block.shape.size`).

#### Scenario: Both faces flippable — triangles at 11, 0, 5, 6
- **WHEN** the top face has triangles at positions 11, 0, 5, 6 (and other blocks not spanning 0 or 6) and the bottom face similarly has no block interior crossing position 0 or 6
- **THEN** `isFlippable` SHALL return `1`

#### Scenario: Top face not flippable — kite at position 11 spans position 0
- **WHEN** the top face has a kite block at position 11 (occupying positions 11 and 0, making position 0 an interior position)
- **THEN** `isFlippable` SHALL return `0`

#### Scenario: Top face not flippable — block interior at position 6
- **WHEN** the top face has a kite block at position 5 (occupying positions 5 and 6, making position 6 an interior position)
- **THEN** `isFlippable` SHALL return `0`

#### Scenario: Bottom face not flippable
- **WHEN** the top face is flippable but the bottom face has a kite block at position 11 (spanning position 0)
- **THEN** `isFlippable` SHALL return `0`

#### Scenario: NULL cube input
- **WHEN** `isFlippable` is called with a NULL `cube` pointer
- **THEN** `isFlippable` SHALL return `0`
