## 1. Cube Module

- [x] 1.1 Add `cube.h` and `cube.c` with `Cube` struct definition (top face, bottom face, history).
- [x] 1.2 Implement `cubeFromString(topFace, bottomFace)` using `cubeFaceFromString` for both faces.
- [x] 1.3 Initialize cube history to empty string during construction and handle invalid parse inputs.

## 2. Cube Serialization

- [x] 2.1 Implement `cubeToString` to output exactly three lines: history, top face string, bottom face string.
- [x] 2.2 Ensure `cubeToString` uses `cubeFaceToString` for top and bottom face lines.

## 3. Validation

- [x] 3.1 Add/extend unit tests for successful cube construction from two strings.
- [x] 3.2 Add/extend unit tests for cubeToString line ordering and formatting.
- [x] 3.3 Run `make test` and confirm all tests pass.
