## 1. CubeFace Rotation API

- [x] 1.1 Add `rotateCubeFaceCounterclockwise(CubeFace *face, int count)` declaration to the CubeFace public header.
- [x] 1.2 Implement counterclockwise rotation in the CubeFace source by applying modulo-12 wraparound to each block position.
- [x] 1.3 Ensure defensive handling for `NULL` face input.

## 2. Validation

- [x] 2.1 Add unit tests covering basic rotation and wraparound behavior (`11+1 -> 0`, `11+2 -> 1`).
- [x] 2.2 Add unit tests confirming shape/color fields are unchanged after rotation.
- [x] 2.3 Run the test target and verify all tests pass.
