## 1. Add Reverse Color Parsing

- [x] 1.1 Add declaration for stringToBlockColor to block-color.h
- [x] 1.2 Implement stringToBlockColor in block-color.c using reverse mapping for w, g, y, r, b, and o
- [x] 1.3 Define and document deterministic handling for invalid color symbols

## 2. Convert Shape Model

- [x] 2.1 Replace enum-only Shape definition with structure-based model in shape.h
- [x] 2.2 Add Geometry enum (or equivalent) to represent triangle and kite kinds
- [x] 2.3 Add size property to Shape and define extern declarations for SHAPE_TRIANGLE and SHAPE_KITE
- [x] 2.4 Create shape.c and define SHAPE_TRIANGLE (size 1) and SHAPE_KITE (size 2)

## 3. Add CubeFace String Parser

- [x] 3.1 Add function declaration for creating a CubeFace from string input in cube-face.h
- [x] 3.2 Create cube-face.c and implement whitespace tokenization (one or more contiguous whitespace delimiters)
- [x] 3.3 Parse 2-character tokens into triangle Blocks with sideColor2 set to NULL
- [x] 3.4 Parse 3-character tokens into kite Blocks with all three colors populated
- [x] 3.5 Allocate CubeFace using block count and store parsed Block values in token order

## 4. Compute Positions and Validate

- [x] 4.1 Implement position assignment: first Block at 0, then increment by previous Block shape size
- [x] 4.2 Add validation behavior for unsupported token lengths and invalid symbols
- [x] 4.3 Update build inputs so cube-face.c and shape.c are compiled with the project
- [x] 4.4 Run make to verify clean compilation

## 5. Add Parser Test Coverage

- [x] 5.1 Add unit-test.c cases for cubeFaceFromString with mixed 2-character and 3-character tokens
- [x] 5.2 Assert parsed block shape, color fields, and position values match expected results
- [x] 5.3 Add invalid-input test cases for unsupported token lengths and invalid color symbols
- [x] 5.4 Run make test and confirm the new parser tests pass
