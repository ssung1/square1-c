# block-color-from-string Specification

## Purpose
Defines the reverse color conversion function `stringToBlockColor` that maps a one-character color code string to a `BlockColor` enum value, mirroring the `blockColorToString` symbol set.

## Requirements

### Requirement: Project SHALL provide reverse color conversion from one-character string
The project SHALL implement stringToBlockColor in block-color.c and declare it in block-color.h to convert a one-character color code to BlockColor.

#### Scenario: Declaration is available in block-color.h
- **WHEN** a developer includes block-color.h
- **THEN** stringToBlockColor is declared and available to call

### Requirement: Reverse mapping SHALL mirror blockColorToString symbols
stringToBlockColor SHALL map supported one-character codes to their matching BlockColor values using the same symbol set used by blockColorToString.

#### Scenario: Known symbols map to expected BlockColor values
- **WHEN** stringToBlockColor receives w, g, y, r, b, or o
- **THEN** it returns BLOCK_COLOR_WHITE, BLOCK_COLOR_GREEN, BLOCK_COLOR_YELLOW, BLOCK_COLOR_RED, BLOCK_COLOR_BLUE, or BLOCK_COLOR_ORANGE respectively

### Requirement: Unsupported symbols SHALL be handled deterministically
stringToBlockColor SHALL define deterministic behavior for unsupported or invalid input symbols so parser behavior remains predictable.

#### Scenario: Invalid symbol is passed
- **WHEN** stringToBlockColor receives an unsupported character
- **THEN** it returns a documented fallback value or signals failure in a documented way
