## 1. Add Shape Enum Definition

- [x] 1.1 Create a dedicated file `shape.h` in the top level of the project
- [x] 1.2 Define `typedef enum Shape` with exactly these two members: SHAPE_TRIANGLE and SHAPE_KITE
- [x] 1.3 Ensure naming and formatting are consistent with C conventions used in the repository

## 2. Expose and Validate Reusability

- [x] 2.1 Add include guards to `shape.h` to make the declaration safely reusable
- [x] 2.2 Reference the enum from existing project code (or a minimal compile path) to verify cross-file usability
- [x] 2.3 Run `make` to confirm the project compiles with the new enum file included in the workflow

## 3. Confirm Requirements Coverage

- [x] 3.1 Verify a dedicated file named `shape.h` exists and contains `Shape`
- [x] 3.2 Verify exactly two required enum members are present (TRIANGLE and KITE with SHAPE_ prefix)
- [x] 3.3 Verify another compilation unit can use `Shape` without duplicating declarations
