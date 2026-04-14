## 1. Cube Rotation APIs

- [x] 1.1 Add immutable top and bottom face rotation function declarations to `cube.h` that return `Cube *` copies.
- [x] 1.2 Implement top-face rotation in `cube.c` by creating a Cube copy and rotating only top face via face-level rotation logic.
- [x] 1.3 Implement bottom-face rotation in `cube.c` by creating a Cube copy and rotating only bottom face via face-level rotation logic.
- [x] 1.4 Ensure null-safety and failure handling return `NULL` without mutating the input Cube.

## 2. Validation

- [x] 2.1 Add unit tests for top-face rotation behavior.
- [x] 2.2 Add unit tests for bottom-face rotation behavior.
- [x] 2.3 Add assertions that source cube and non-target face remain unchanged for each API.
- [x] 2.4 Run `make test` and verify all tests pass.
