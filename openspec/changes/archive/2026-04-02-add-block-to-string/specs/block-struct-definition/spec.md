## MODIFIED Requirements

### Requirement: Block structure SHALL have five specified properties
The `Block` structure SHALL include exactly five properties: position (integer), shape (Shape enum), faceColor (BlockColor enum), sideColor1 (BlockColor enum), and sideColor2 (optional, stored as `const BlockColor *` pointer, may be `NULL` to indicate absence).

#### Scenario: All required properties are present
- **WHEN** the Block structure declaration is reviewed
- **THEN** it includes all five fields with correct types as specified, and `sideColor2` is declared as `const BlockColor *`

#### Scenario: sideColor2 can be NULL
- **WHEN** a Block is created with `sideColor2` set to `NULL`
- **THEN** the project compiles without error and the Block is valid
