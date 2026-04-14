## MODIFIED Requirements

### Requirement: flip returns new Cube with right-half blocks exchanged and reflected
`flip(const Cube *cube)` SHALL return a new `Cube *` where the right-half blocks (those with `position` in [0, 6)) from the top face have moved to the bottom face with reflected positions, and the right-half blocks from the bottom face have moved to the top face with reflected positions. Left-half blocks (position >= 6) remain on their original face with unchanged positions.

The reflected position of a block with `position = p` and `shape.size = s` SHALL be `6 - p - s`.

`flip` SHALL return `NULL` when the input cube is not flippable (as defined by `isFlippable`).

#### Scenario: Right-half triangle moves from top to bottom, reflected
- **WHEN** the top face has a triangle at position 0 (size 1) and `flip` is called on a flippable cube
- **THEN** the new bottom face contains that block at reflected position `6 - 0 - 1 = 5`

#### Scenario: Right-half kite moves from top to bottom, reflected
- **WHEN** the top face has a kite at position 0 (size 2) and `flip` is called on a flippable cube
- **THEN** the new bottom face contains that block at reflected position `6 - 0 - 2 = 4`

#### Scenario: Right-half blocks from bottom face move to top face
- **WHEN** the bottom face has right-half blocks and `flip` is called on a flippable cube
- **THEN** those blocks appear on the new top face with their positions reflected

#### Scenario: Left-half blocks remain on their original face
- **WHEN** a face has blocks at positions >= 6 and `flip` is called on a flippable cube
- **THEN** those blocks remain on the same face with unchanged positions

#### Scenario: Non-flippable cube aborts flip
- **WHEN** `flip` is called with a cube where `isFlippable(cube)` is false
- **THEN** `flip` SHALL return `NULL`

### Requirement: flip does not modify the input Cube
`flip` SHALL NOT modify the input `Cube` or either of its faces. The original `Cube` SHALL remain identical after the call.

#### Scenario: Source Cube unchanged after successful flip
- **WHEN** `flip` is called on a flippable Cube
- **THEN** the source Cube's top and bottom faces are identical to before the call

### Requirement: flip returns NULL for NULL input
`flip(NULL)` SHALL return `NULL`.

#### Scenario: NULL input returns NULL
- **WHEN** `flip` is called with a `NULL` cube pointer
- **THEN** the return value is `NULL`
