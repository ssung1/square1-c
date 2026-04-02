# cube-face-from-string Specification

## Purpose
Defines the `cubeFaceFromString` function that parses a whitespace-delimited token string into a `CubeFace` containing fully initialized `Block` objects with shapes, colors, and positions.

## Requirements

### Requirement: Project SHALL provide CubeFace construction from a definition string
The project SHALL implement a function in cube-face.c that takes an input string and constructs a CubeFace from it.

#### Scenario: Function is available for callers
- **WHEN** a developer includes the CubeFace interface and links project sources
- **THEN** a CubeFace-from-string function can be called to build a CubeFace from text input

### Requirement: Parser SHALL tokenize by one or more whitespace characters
The CubeFace parser SHALL split input into tokens separated by one or more contiguous whitespace characters, and each token SHALL define exactly one Block.

#### Scenario: Multiple spaces still separate tokens
- **WHEN** input contains repeated spaces or mixed whitespace between block tokens
- **THEN** each non-empty token is parsed as a separate Block in CubeFace order

### Requirement: Token length SHALL determine shape and block fields
The parser SHALL interpret token length 2 as a triangle block and token length 3 as a kite block, assigning the corresponding SHAPE_TRIANGLE and SHAPE_KITE shape constants.

#### Scenario: Two-character token maps to triangle block
- **WHEN** a token has exactly 2 characters
- **THEN** resulting Block has shape SHAPE_TRIANGLE, faceColor from char 1, sideColor1 from char 2, and sideColor2 set to NULL

#### Scenario: Three-character token maps to kite block
- **WHEN** a token has exactly 3 characters
- **THEN** resulting Block has shape SHAPE_KITE, faceColor from char 1, sideColor1 from char 2, and sideColor2 from char 3

### Requirement: Block positions SHALL be derived from previous block shape
The first parsed Block SHALL have position 0. Each subsequent Block position SHALL be previous position plus the size value of the previous Block shape constant.

#### Scenario: Position progression follows shape-based increments
- **WHEN** parsing a sequence of tokens into Blocks
- **THEN** each Block position is computed using the previous parsed Block shape size (1 for SHAPE_TRIANGLE, 2 for SHAPE_KITE)

### Requirement: Project SHALL provide tests for cubeFaceFromString
The unit test suite SHALL include tests for cubeFaceFromString that verify token parsing, shape assignment, color mapping, and position progression.

#### Scenario: Parser test validates mixed tokens
- **WHEN** unit tests run with an input containing both 2-character and 3-character tokens
- **THEN** the resulting CubeFace blocks match expected shapes, colors, and positions

#### Scenario: Parser test validates invalid token handling
- **WHEN** unit tests run with invalid token lengths or unsupported color symbols
- **THEN** cubeFaceFromString exhibits the documented deterministic failure behavior
