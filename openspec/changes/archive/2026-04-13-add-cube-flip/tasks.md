## 1. Implementation

- [x] 1.1 Declare `Cube *flip(const Cube *cube)` in `cube.h`
- [x] 1.2 Add private helper `buildFlippedFace(const CubeFace *sameFace, const CubeFace *otherFace)` in `cube.c` that builds a new `CubeFace` from the left-half blocks of `sameFace` and the reflected right-half blocks of `otherFace`
- [x] 1.3 Implement `flip` in `cube.c`: NULL guard returning NULL, then build new top face and new bottom face using the helper, copy history, assemble and return new Cube

## 2. Tests

- [x] 2.1 Add test: right-half triangle at position 0 on top moves to bottom at position 5 after flip
- [x] 2.2 Add test: right-half kite at position 0 on top moves to bottom at position 4 after flip
- [x] 2.3 Add test: right-half blocks from bottom move to top with reflected positions
- [x] 2.4 Add test: left-half blocks remain on their original face unchanged
- [x] 2.5 Add test: source Cube is unchanged after flip (immutability)
- [x] 2.6 Add test: NULL input returns NULL
- [x] 2.7 Run `make test` and confirm all tests pass
