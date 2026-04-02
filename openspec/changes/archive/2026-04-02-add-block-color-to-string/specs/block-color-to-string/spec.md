## ADDED Requirements

### Requirement: Project SHALL provide a BlockColor-to-string conversion function
The project SHALL implement a `blockColorToString` function in `block-color.c` and declare it in `block-color.h` that converts a `BlockColor` enum value to a single-character `const char *` string.

#### Scenario: Function is declared in block-color.h
- **WHEN** a developer includes `block-color.h`
- **THEN** the `blockColorToString` function declaration is available without any additional includes

#### Scenario: BLOCK_COLOR_WHITE converts to "w"
- **WHEN** `blockColorToString(BLOCK_COLOR_WHITE)` is called
- **THEN** the function returns the string `"w"`

#### Scenario: BLOCK_COLOR_GREEN converts to "g"
- **WHEN** `blockColorToString(BLOCK_COLOR_GREEN)` is called
- **THEN** the function returns the string `"g"`

#### Scenario: BLOCK_COLOR_YELLOW converts to "y"
- **WHEN** `blockColorToString(BLOCK_COLOR_YELLOW)` is called
- **THEN** the function returns the string `"y"`

#### Scenario: BLOCK_COLOR_RED converts to "r"
- **WHEN** `blockColorToString(BLOCK_COLOR_RED)` is called
- **THEN** the function returns the string `"r"`

#### Scenario: BLOCK_COLOR_BLUE converts to "b"
- **WHEN** `blockColorToString(BLOCK_COLOR_BLUE)` is called
- **THEN** the function returns the string `"b"`

#### Scenario: BLOCK_COLOR_ORANGE converts to "o"
- **WHEN** `blockColorToString(BLOCK_COLOR_ORANGE)` is called
- **THEN** the function returns the string `"o"`

### Requirement: block-color.c SHALL be included in the build
The `block-color.c` source file SHALL be compiled as part of the standard project build.

#### Scenario: Project builds with block-color.c included
- **WHEN** a developer runs `make`
- **THEN** the project compiles successfully with `block-color.c` as a compiled translation unit
