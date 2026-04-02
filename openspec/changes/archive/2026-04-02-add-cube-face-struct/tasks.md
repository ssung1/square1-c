## 1. Add CubeFace Header

- [x] 1.1 Create cube-face.h with include guards and required includes
- [x] 1.2 Declare the CubeFace structure in cube-face.h
- [x] 1.3 Add fields needed to represent a variable-length array of Block objects in CubeFace

## 2. Preserve Face Layout Semantics

- [x] 2.1 Ensure CubeFace stores Block values in face order
- [x] 2.2 Document or encode that Block.position represents radial placement within the face

## 3. Validate Integration

- [x] 3.1 Verify cube-face.h can include block.h without compile issues
- [x] 3.2 Run make to confirm the project still builds cleanly after adding the new header
