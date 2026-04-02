## ADDED Requirements

### Requirement: Project SHALL provide a blockToString function
The project SHALL implement a `blockToString` function in `block.c` and declare it in `block.h` that converts a `Block` to a `const char *` string.

#### Scenario: Function is declared in block.h
- **WHEN** a developer includes `block.h`
- **THEN** the `blockToString` function declaration is available without additional includes

### Requirement: blockToString SHALL concatenate color fields in order
The `blockToString` function SHALL return a string formed by concatenating the single-character string of `faceColor`, followed by `sideColor1`, followed by `sideColor2` if present.

#### Scenario: Block with all three colors
- **WHEN** `blockToString` is called with a `Block` where `faceColor` is `BLOCK_COLOR_WHITE`, `sideColor1` is `BLOCK_COLOR_GREEN`, and `sideColor2` points to `BLOCK_COLOR_BLUE`
- **THEN** the function returns the string `"wgb"`

#### Scenario: Block with only two colors (sideColor2 is NULL)
- **WHEN** `blockToString` is called with a `Block` where `faceColor` is `BLOCK_COLOR_RED`, `sideColor1` is `BLOCK_COLOR_ORANGE`, and `sideColor2` is `NULL`
- **THEN** the function returns the string `"ro"`
