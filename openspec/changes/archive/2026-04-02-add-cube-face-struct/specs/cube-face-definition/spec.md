## ADDED Requirements

### Requirement: Project SHALL define a CubeFace structure in cube-face.h
The project SHALL define a CubeFace structure in a dedicated header file named cube-face.h.

#### Scenario: CubeFace header exists
- **WHEN** a developer inspects the project files
- **THEN** cube-face.h exists and contains the CubeFace structure declaration

### Requirement: CubeFace SHALL contain an array of Block objects
The CubeFace structure SHALL contain an ordered array of Block objects representing the Blocks that belong to that face.

#### Scenario: CubeFace stores Block values
- **WHEN** the CubeFace structure declaration is reviewed
- **THEN** it includes storage for an array of Block objects rather than a scalar Block field

### Requirement: CubeFace SHALL preserve radial block arrangement semantics
The order of Blocks in CubeFace and the Block.position field values SHALL represent the radial arrangement of Blocks on the face.

#### Scenario: Block positions describe radial placement
- **WHEN** a CubeFace instance is interpreted by a developer or calling code
- **THEN** each contained Block.position value corresponds to that Block's radial placement within the face
