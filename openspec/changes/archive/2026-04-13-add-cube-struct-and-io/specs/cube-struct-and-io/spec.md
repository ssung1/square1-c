## ADDED Requirements

### Requirement: Project SHALL define a Cube structure
The project SHALL define a `Cube` structure in new cube module files with three fields: top face, bottom face, and history.

#### Scenario: Cube structure is available to callers
- **WHEN** a developer includes the Cube interface
- **THEN** the `Cube` type is available with top-face, bottom-face, and history state

### Requirement: Project SHALL provide cubeFromString
The project SHALL provide `cubeFromString` that builds a Cube from two input strings: one for top face and one for bottom face.

#### Scenario: cubeFromString builds both faces from inputs
- **WHEN** `cubeFromString(top, bottom)` is called with valid face-definition strings
- **THEN** top and bottom faces are created via CubeFace parsing and assigned to the new Cube

#### Scenario: cubeFromString initializes history
- **WHEN** a Cube is created from valid face strings
- **THEN** Cube history is initialized to an empty string

#### Scenario: cubeFromString fails on invalid face input
- **WHEN** either top or bottom face definition is invalid
- **THEN** `cubeFromString` returns `NULL`

### Requirement: Project SHALL provide cubeToString
The project SHALL provide `cubeToString` that returns a three-line string representation of cube state.

#### Scenario: cubeToString line order is history, top, bottom
- **WHEN** `cubeToString` is called on a valid Cube
- **THEN** the first line is history, second line is top-face string, and third line is bottom-face string

#### Scenario: cubeToString reuses face serialization
- **WHEN** `cubeToString` serializes top and bottom faces
- **THEN** face lines are produced using `cubeFaceToString`
