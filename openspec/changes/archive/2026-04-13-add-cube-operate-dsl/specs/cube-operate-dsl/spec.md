## ADDED Requirements

### Requirement: operate parses fixed-width operation tokens
`operate` SHALL parse the operation string into 3-character tokens from left to right. The final token MAY be shorter (length 1 or 2).

#### Scenario: Full token parsing
- **WHEN** `operate` receives `"12 34 "`
- **THEN** it processes two 3-character tokens in order: `"12 "` then `"34 "`

#### Scenario: Short final token parsing
- **WHEN** `operate` receives `"1a 2"`
- **THEN** it processes token `"1a "` followed by final 1-character token `"2"`

### Requirement: token character semantics drive operations
For each token, `operate` SHALL apply operations in this order:
1. first character: top-face clockwise rotation amount (`0`-`9`,`a`,`b`)
2. second character (if present): bottom-face clockwise rotation amount (`0`-`9`,`a`,`b`)
3. third character (if present): MUST be space and means apply flip

#### Scenario: 1-character token rotates top only
- **WHEN** token is `"5"`
- **THEN** top face rotates by 5 and no bottom rotation/flip is applied

#### Scenario: 2-character token rotates top and bottom only
- **WHEN** token is `"a3"`
- **THEN** top rotates by 10, bottom rotates by 3, and no flip is applied

#### Scenario: 3-character token applies flip
- **WHEN** token is `"b1 "`
- **THEN** top rotates by 11, bottom rotates by 1, then flip is applied

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

### Requirement: operate is immutable and appends history
`operate` SHALL return a new Cube instance, SHALL NOT modify input Cube, and SHALL append the operation string to the returned Cube history.

#### Scenario: input cube unchanged
- **WHEN** `operate` executes a valid operation string
- **THEN** original Cube faces and history remain unchanged

#### Scenario: history append on success
- **WHEN** input history is `"U"` and ops is `"1a "`
- **THEN** returned Cube history is `"U1a "`

#### Scenario: NULL arguments
- **WHEN** cube or ops is NULL
- **THEN** `operate` returns NULL
