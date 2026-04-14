## MODIFIED Requirements

### Requirement: Output SHALL order blocks by ascending position, with optional `*` prefix
The `cubeFaceToString` function SHALL output blocks in ascending order of their position field, starting from the lowest position. If the lowest position in the face is 1 (not 0), the output SHALL be prefixed with a single asterisk (`*`).

#### Scenario: Blocks output in position order with no prefix when starting at 0
- **WHEN** a CubeFace has blocks starting at position 0 (or any position other than 1)
- **THEN** the output string lists them in ascending position order with no prefix

#### Scenario: Blocks output with asterisk prefix when starting at position 1
- **WHEN** a CubeFace has blocks where the lowest position is 1 (e.g., blocks at positions 1, 3, 5)
- **THEN** the output string is prefixed with `*` followed by the block representations in ascending position order

#### Scenario: Asterisk prefix appears only for minimum position 1
- **WHEN** a CubeFace has blocks with the lowest position at any value other than 0 or 1 (e.g., 2, 6, 11)
- **THEN** the output string contains no `*` prefix
