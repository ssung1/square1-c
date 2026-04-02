## ADDED Requirements

### Requirement: Makefile SHALL build a unit-test binary target
The Makefile SHALL define a build target that compiles unit-test.c and required project sources into a unit-test executable.

#### Scenario: Unit-test binary builds successfully
- **WHEN** the unit-test build target is invoked
- **THEN** the build completes without errors and produces the unit-test executable

### Requirement: Makefile SHALL provide a target to execute unit tests
The Makefile SHALL define a target that executes the unit-test binary as part of the standard workflow.

#### Scenario: Test target runs unit tests
- **WHEN** the test run target is invoked
- **THEN** the unit-test executable is run and its exit status is returned to the caller
