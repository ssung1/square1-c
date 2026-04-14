## Why

Applying multiple Square-1 operations one function call at a time is verbose and error-prone. A compact operation string will make it easier to script and replay move sequences for solving, scrambling, and tests.

## What Changes

- Add `operate` function in `cube.c` / `cube.h` that takes a Cube and an operation string.
- Parse the operation string into fixed-width tokens of 3 characters, except the final token which may be shorter.
- For each token:
- first character (`0`-`9`, `a`, `b`) rotates top face clockwise by that amount.
- second character (optional, same range) rotates bottom face clockwise.
- third character (optional) must be a space (` `) and means apply `flip`.
- Support short tail tokens:
- length 1 token: rotate top only.
- length 2 token: rotate top and bottom only.
- Return a new Cube (input Cube unchanged) and append the processed operation string to Cube history.

## Capabilities

### New Capabilities
- `cube-operate-dsl`: Apply a sequence of top/bottom rotations and optional flip operations from a compact tokenized string.

### Modified Capabilities

## Impact

- `cube.h`: declare `operate`
- `cube.c`: implement parser/executor and history append behavior
- `unit-test.c`: add operate parsing/execution/history tests
