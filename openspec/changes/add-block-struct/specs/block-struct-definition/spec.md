## ADDED Requirements

### Requirement: Project SHALL define a Block structure in dedicated files
The project SHALL define a `Block` structure with dedicated source files `block.h` (declaration) and `block.c` (implementation).

#### Scenario: Block structure files exist
- **WHEN** a developer inspects the project files
- **THEN** files `block.h` and `block.c` exist and contain the Block structure definition

### Requirement: Block structure SHALL have five specified properties
The `Block` structure SHALL include exactly five properties: position (integer), shape (Shape enum), faceColor (BlockColor enum), sideColor1 (BlockColor enum), and sideColor2 (BlockColor enum).

#### Scenario: All required properties are present
- **WHEN** the Block structure declaration is reviewed
- **THEN** it includes all five fields with correct types as specified

### Requirement: Block structure SHALL be reusable by other modules
The Block structure declaration SHALL be available for reuse by other C modules through standard include/compilation workflows.

#### Scenario: Structure is available to other compilation units
- **WHEN** another module includes block.h and uses Block
- **THEN** the project compiles without requiring duplicated structure declarations
