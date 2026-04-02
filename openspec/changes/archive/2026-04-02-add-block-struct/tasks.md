## 1. Define Block Structure

- [x] 1.1 Create `block.h` with include guards and necessary includes (block-color.h, shape.h)
- [x] 1.2 Define `typedef struct Block` with five fields: position (int), shape (Shape), faceColor (BlockColor), sideColor1 (BlockColor), sideColor2 (BlockColor)
- [x] 1.3 Ensure naming and formatting are consistent with C conventions used in the repository

## 2. Provide Block Implementation

- [x] 2.1 Create `block.c` with any necessary implementation or forward declarations
- [x] 2.2 Reference the Block structure from existing project code (or a minimal compile path) to verify cross-file usability
- [x] 2.3 Run `make` to confirm the project compiles with the new structure files included in the workflow

## 3. Confirm Requirements Coverage

- [x] 3.1 Verify dedicated files `block.h` and `block.c` exist and contain Block structure
- [x] 3.2 Verify all five required fields are present with correct types (position, shape, faceColor, sideColor1, sideColor2)
- [x] 3.3 Verify another compilation unit can use Block without duplicating structure declarations
