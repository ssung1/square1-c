## ADDED Requirements

### Requirement: Project SHALL provide CubeFace to string conversion
The project SHALL implement a `cubeFaceToString` function in `cube-face.c` and declare it in `cube-face.h` that converts a CubeFace to a space-delimited string.

#### Scenario: Function is available to callers
- **WHEN** a developer includes the CubeFace interface and links project sources
- **THEN** a CubeFace-to-string function can be called to produce a string representation of an existing CubeFace

### Requirement: Output SHALL order blocks by ascending position
The `cubeFaceToString` function SHALL output blocks in ascending order of their position field, starting from the lowest position.

#### Scenario: Blocks output in position order
- **WHEN** a CubeFace contains blocks with positions 0, 2, and 1 (in storage order)
- **THEN** the output string lists them in the order: position 0 block, position 1 block, position 2 block

### Requirement: Blocks SHALL be separated by single space
Each block string representation SHALL be separated from the next by a single space character.

#### Scenario: Multiple blocks are space-separated
- **WHEN** a CubeFace has multiple blocks
- **THEN** the output string contains exactly one space between consecutive block representations

### Requirement: cubeFaceToString SHALL reuse blockToString format
Each block in the output SHALL be formatted using the existing `blockToString` function encoding (2-3 color characters per block).

#### Scenario: Block format matches blockToString output
- **WHEN** a CubeFace is converted to string
- **THEN** each block segment in the output matches what `blockToString` would produce for that block

### Requirement: cubeFaceToString SHALL handle NULL and empty inputs safely
The function SHALL return NULL for NULL input and a valid empty string representation for zero-block faces.

#### Scenario: NULL face returns NULL
- **WHEN** cubeFaceToString is called with a NULL pointer
- **THEN** the function returns NULL

#### Scenario: Empty face returns valid string
- **WHEN** cubeFaceToString is called with a valid CubeFace containing zero blocks
- **THEN** the function returns an empty string or a minimal valid representation
