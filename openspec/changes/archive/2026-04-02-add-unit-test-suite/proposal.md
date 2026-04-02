## Why

The project currently keeps ad hoc validation logic in main.c, which mixes app entry behavior with test behavior. Creating a focused unit-test.c test suite improves maintainability and makes verification repeatable through the build system.

## What Changes

- Add a dedicated unit-test.c source file containing tests currently embedded in main.c.
- Keep main.c focused on application entry logic and remove test-oriented output from it.
- Update Makefile to build a unit-test executable target alongside the main program.
- Define a simple test execution flow so project changes can be validated consistently.

## Capabilities

### New Capabilities
- unit-test-suite: Provides a dedicated unit test source file and executable that runs project checks independently from the main application.
- makefile-test-target: Extends build behavior so the Makefile can build and run a unit test binary target.

### Modified Capabilities
- None.

## Impact

- Affected code: main.c, new unit-test.c, and Makefile.
- Build/developer workflow: adds an explicit test build target and executable.
- APIs/systems: no public API changes; this is a structure and workflow improvement.
