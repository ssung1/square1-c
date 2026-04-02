## 1. Bootstrap Source File

- [x] 1.1 Create top-level `main.c` with a valid `main` function that currently performs no application logic
- [x] 1.2 Add `#include <stdio.h>` to `main.c` while keeping runtime behavior intentionally minimal
- [x] 1.3 Verify `main.c` compiles cleanly with the configured compiler and warning flags

## 2. Establish Build Automation

- [x] 2.1 Create a top-level `Makefile` with variables for compiler, flags, target binary, and source file
- [x] 2.2 Implement default/all build target that compiles `main.c` into the configured binary
- [x] 2.3 Implement `clean` target that removes generated build artifacts

## 3. Validate Developer Workflow

- [x] 3.1 Run `make` to confirm the binary is produced from a clean checkout
- [x] 3.2 Run `make clean` to confirm build outputs are removed
- [x] 3.3 Confirm resulting files align with `c-project-bootstrap` spec scenarios
