## ADDED Requirements

### Requirement: Project SHALL provide CubeFace counterclockwise rotation
The project SHALL provide a CubeFace rotation function that updates each block position counterclockwise by a caller-provided count.

#### Scenario: Rotation function is available to callers
- **WHEN** a developer includes the CubeFace interface and links project sources
- **THEN** a CubeFace counterclockwise rotation function can be called on an existing CubeFace

### Requirement: Rotation SHALL wrap positions on a 12-slot ring
When rotating, each block position SHALL be transformed by adding the rotation count and normalizing with modulo-12 semantics so the resulting value remains in the range `0..11`.

#### Scenario: Position wraps at 12
- **WHEN** a block at position `11` is rotated by `1`
- **THEN** its resulting position is `0`

#### Scenario: Position wraps beyond 12
- **WHEN** a block at position `11` is rotated by `2`
- **THEN** its resulting position is `1`

### Requirement: Rotation SHALL preserve non-position block fields
Rotating a CubeFace SHALL NOT modify block shape or color fields.

#### Scenario: Shape and colors remain unchanged after rotation
- **WHEN** a CubeFace with initialized block shape and colors is rotated
- **THEN** each block retains the same shape, faceColor, sideColor1, and sideColor2 values while only position changes
