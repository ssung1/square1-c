## 1. Add Color Enum Definition

- [x] 1.1 Create a dedicated file for the enum using `block-color.h` (or `block-color.c` if explicitly chosen)
- [x] 1.2 Define `typedef enum BlockColor` with exactly these six members: BLOCK_COLOR_WHITE, BLOCK_COLOR_GREEN, BLOCK_COLOR_YELLOW, BLOCK_COLOR_RED, BLOCK_COLOR_BLUE, BLOCK_COLOR_ORANGE
- [x] 1.3 Ensure naming and formatting are consistent with C conventions used in the repository

## 2. Expose and Validate Reusability

- [x] 2.1 If `block-color.h` is used, add include guards to make the declaration safely reusable
- [x] 2.2 Reference the enum from existing project code (or a minimal compile path) to verify cross-file usability
- [x] 2.3 Run `make` to confirm the project compiles with the new enum file included in the workflow

## 3. Confirm Requirements Coverage

- [x] 3.1 Verify a dedicated file named `block-color.h` or `block-color.c` exists and contains `BlockColor`
- [x] 3.2 Verify all six required color enum values are present (WHITE, GREEN, YELLOW, RED, BLUE, ORANGE)
- [x] 3.3 Verify another compilation unit can use `BlockColor` without duplicating declarations
