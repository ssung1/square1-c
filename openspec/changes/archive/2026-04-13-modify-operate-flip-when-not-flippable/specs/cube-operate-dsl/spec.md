## MODIFIED Requirements

### Requirement: token character semantics drive operations
For each token, `operate` SHALL apply operations in this order:
1. first character: top-face clockwise rotation amount (`0`-`9`,`a`,`b`)
2. second character (if present): bottom-face clockwise rotation amount (`0`-`9`,`a`,`b`)
3. third character (if present): MUST be space and means request flip

When a flip is requested (third char is space), `operate` SHALL check whether the current cube state is flippable before invoking `flip`.
- If flippable, `operate` SHALL apply flip.
- If not flippable, `operate` SHALL perform no flip and continue processing subsequent tokens.

#### Scenario: 1-character token rotates top only
- **WHEN** token is `"5"`
- **THEN** top face rotates by 5 and no bottom rotation/flip is applied

#### Scenario: 2-character token rotates top and bottom only
- **WHEN** token is `"a3"`
- **THEN** top rotates by 10, bottom rotates by 3, and no flip is applied

#### Scenario: 3-character token applies flip when flippable
- **WHEN** token is `"b1 "` and current cube is flippable
- **THEN** top rotates by 11, bottom rotates by 1, then flip is applied

#### Scenario: 3-character token skips flip when not flippable
- **WHEN** token is `"00 "` and current cube is not flippable
- **THEN** top and bottom rotations are applied, flip is skipped (no-op), and `operate` continues without returning NULL

### Requirement: operate validates token characters
`operate` SHALL return NULL if token characters are invalid.

#### Scenario: invalid top digit
- **WHEN** first character is not in `0-9a-b`
- **THEN** `operate` returns NULL

#### Scenario: invalid bottom digit
- **WHEN** second character exists and is not in `0-9a-b`
- **THEN** `operate` returns NULL

#### Scenario: invalid third character
- **WHEN** third character exists and is not a space
- **THEN** `operate` returns NULL
