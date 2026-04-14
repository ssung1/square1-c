## 1. Implementation Update

- [x] 1.1 Modify `cubeFaceToString` in `cube-face.c` to find the minimum block position before building output
- [x] 1.2 Add logic to prepend `*` to the output buffer when minimum position is 1
- [x] 1.3 Adjust snprintf call to account for the `*` prefix in the buffer length calculation

## 2. Tests

- [x] 2.1 Add test: CubeFace with blocks starting at position 0 → no prefix
- [x] 2.2 Add test: CubeFace with blocks starting at position 1 → `*` prefix
- [x] 2.3 Add test: CubeFace with blocks starting at position 2 → no prefix (edge case)
- [x] 2.4 Add test: NULL input → NULL output (unchanged behavior)
- [ ] 2.5 Run `make test` and confirm all tests pass
