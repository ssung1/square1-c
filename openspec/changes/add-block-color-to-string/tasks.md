## 1. Update block-color.h

- [x] 1.1 Add declaration for `blockColorToString(BlockColor color)` returning `const char *` to `block-color.h`

## 2. Implement block-color.c

- [x] 2.1 Create `block-color.c` with `#include "block-color.h"`
- [x] 2.2 Implement `blockColorToString` using a `switch` statement mapping all six `BlockColor` members to their single-character strings (`"w"`, `"g"`, `"y"`, `"r"`, `"b"`, `"o"`)
- [x] 2.3 Add a fallback return value of `"?"` for unrecognized enum values

## 3. Update Build

- [x] 3.1 Add `block-color.c` to `SRC` in `Makefile`
- [x] 3.2 Run `make` to confirm the project compiles cleanly with the new source file

## 4. Confirm Requirements Coverage

- [x] 4.1 Verify `blockColorToString` is declared in `block-color.h` and usable from other modules
- [x] 4.2 Verify all six `BlockColor` members return the correct single-character string
