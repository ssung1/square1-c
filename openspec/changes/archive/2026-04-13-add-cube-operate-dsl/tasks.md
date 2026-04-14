## 1. API and Parsing

- [x] 1.1 Declare `Cube *operate(const Cube *cube, const char *ops)` in `cube.h`
- [x] 1.2 Add helper to decode hex-like digits `0-9,a,b` to rotation counts in `cube.c`
- [x] 1.3 Implement token iteration in `cube.c` using fixed 3-char chunks, with final token allowed to be length 1 or 2
- [x] 1.4 Validate token characters and return NULL for invalid input

## 2. Operation Execution

- [x] 2.1 Implement immutable execution pipeline: apply top rotation, optional bottom rotation, optional flip per token
- [x] 2.2 Ensure input cube is unchanged and all intermediates are freed on success/failure
- [x] 2.3 Append operation string to returned cube history on success

## 3. Tests

- [x] 3.1 Add test: 1-char token rotates top only
- [x] 3.2 Add test: 2-char token rotates top and bottom (no flip)
- [x] 3.3 Add test: 3-char token includes flip with third char space
- [x] 3.4 Add test: invalid top/bottom/third chars return NULL
- [x] 3.5 Add test: source cube unchanged after operate
- [x] 3.6 Add test: history appends operation string
- [x] 3.7 Add test: NULL cube or NULL ops returns NULL
- [x] 3.8 Run `make test` and confirm all tests pass
