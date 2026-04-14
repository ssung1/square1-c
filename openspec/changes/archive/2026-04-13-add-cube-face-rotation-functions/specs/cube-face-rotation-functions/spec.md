## ADDED Requirements

### Requirement: Project SHALL provide top-face rotation on Cube
The project SHALL provide a Cube API that returns a rotated Cube copy where only the top face is rotated by a caller-provided clockwise count.

#### Scenario: Top-face rotation function is available
- **WHEN** a developer includes the Cube interface and links project sources
- **THEN** a function can be called to rotate only the Cube top face

#### Scenario: Top-face rotation does not mutate bottom face
- **WHEN** the top-face rotation function is called on a Cube with distinct top and bottom faces
- **THEN** the top face is updated according to rotation count and bottom face remains unchanged

#### Scenario: Top-face rotation does not mutate source Cube
- **WHEN** the top-face rotation function is called with a valid Cube
- **THEN** the original Cube remains unchanged and a new rotated Cube is returned

### Requirement: Project SHALL provide bottom-face rotation on Cube
The project SHALL provide a Cube API that returns a rotated Cube copy where only the bottom face is rotated by a caller-provided clockwise count.

#### Scenario: Bottom-face rotation function is available
- **WHEN** a developer includes the Cube interface and links project sources
- **THEN** a function can be called to rotate only the Cube bottom face

#### Scenario: Bottom-face rotation does not mutate top face
- **WHEN** the bottom-face rotation function is called on a Cube with distinct top and bottom faces
- **THEN** the bottom face is updated according to rotation count and top face remains unchanged

#### Scenario: Bottom-face rotation does not mutate source Cube
- **WHEN** the bottom-face rotation function is called with a valid Cube
- **THEN** the original Cube remains unchanged and a new rotated Cube is returned

### Requirement: Cube face-rotation APIs SHALL reuse face-level rotation logic
Cube top/bottom rotation APIs SHALL delegate rotation behavior to the existing CubeFace rotation function.

#### Scenario: Cube APIs follow face-level rotation semantics
- **WHEN** cube-level top or bottom rotation is invoked with a valid count
- **THEN** resulting positions follow the same clockwise wraparound semantics as the face-level rotation function
