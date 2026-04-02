## ADDED Requirements

### Requirement: Project SHALL define a BlockColor enum in a dedicated file
The project SHALL define a `BlockColor` enum in a dedicated source file, and that file SHALL be either `block-color.h` or `block-color.c`.

#### Scenario: Dedicated file exists for BlockColor enum
- **WHEN** a developer inspects the project files
- **THEN** a dedicated file named `block-color.h` or `block-color.c` exists and contains the `BlockColor` enum definition

### Requirement: BlockColor enum SHALL provide exactly six specified color members
The `BlockColor` enum SHALL include the following six color members: BLOCK_COLOR_WHITE, BLOCK_COLOR_GREEN, BLOCK_COLOR_YELLOW, BLOCK_COLOR_RED, BLOCK_COLOR_BLUE, BLOCK_COLOR_ORANGE.

#### Scenario: All required enum members are present
- **WHEN** the `BlockColor` enum declaration is reviewed
- **THEN** it includes exactly six members: WHITE, GREEN, YELLOW, RED, BLUE, and ORANGE with BLOCK_COLOR_ prefix

### Requirement: BlockColor enum SHALL be reusable by other modules
The `BlockColor` enum declaration SHALL be available for reuse by other C modules through standard include/compilation workflows.

#### Scenario: Enum is available to other compilation units
- **WHEN** another module references the `BlockColor` enum using normal C project conventions
- **THEN** the project compiles without requiring duplicated enum declarations
