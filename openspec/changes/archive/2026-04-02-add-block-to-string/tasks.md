## 1. Update Block Struct

- [x] 1.1 Change `sideColor2` field in `block.h` from `BlockColor` to `const BlockColor *`
- [x] 1.2 Update `main.c` to pass a pointer (or `NULL`) for `sideColor2` in the Block initializer

## 2. Add blockToString to block.h

- [x] 2.1 Add declaration `const char *blockToString(const Block *block)` to `block.h`

## 3. Implement blockToString in block.c

- [x] 3.1 Add `#include <string.h>` (or equivalent) and define a `static char` buffer of size 4 in `blockToString`
- [x] 3.2 Write `blockColorToString(block->faceColor)[0]` into buffer position 0
- [x] 3.3 Write `blockColorToString(block->sideColor1)[0]` into buffer position 1
- [x] 3.4 If `block->sideColor2 != NULL`, write `blockColorToString(*block->sideColor2)[0]` into position 2; otherwise null-terminate at position 2
- [x] 3.5 Null-terminate the buffer and return it

## 4. Validate

- [x] 4.1 Run `make` to confirm the project compiles cleanly with all changes
- [x] 4.2 Verify a Block with all three colors produces a 3-character string (e.g., `"wgb"`)
- [x] 4.3 Verify a Block with `sideColor2 = NULL` produces a 2-character string (e.g., `"ro"`)
