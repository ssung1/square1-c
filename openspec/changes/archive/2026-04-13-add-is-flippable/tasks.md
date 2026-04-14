## 1. Implementation

- [x] 1.1 Declare `isFlippable(const Cube *cube)` in `cube.h`
- [x] 1.2 Add private helper `isFaceFlippable(const CubeFace *face)` in `cube.c` that scans all blocks and returns `0` if any block has an interior position at 0 or 6
- [x] 1.3 Implement `isFlippable` in `cube.c` that returns `isFaceFlippable(cube->topFace) && isFaceFlippable(cube->bottomFace)`, with NULL guard returning `0`

## 2. Tests

- [x] 2.1 Add test: both faces flippable (triangles cleanly at 0 and 6 boundaries) → returns `1`
- [x] 2.2 Add test: top face kite at position 11 spans position 0 → returns `0`
- [x] 2.3 Add test: top face kite at position 5 spans position 6 → returns `0`
- [x] 2.4 Add test: bottom face not flippable, top face is → returns `0`
- [x] 2.5 Add test: NULL cube → returns `0`
- [x] 2.6 Run `make test` and confirm all tests pass
