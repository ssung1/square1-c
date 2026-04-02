## 1. Isolate Test Logic from Application Entry

- [x] 1.1 Identify test-oriented logic currently in main.c that should move to unit-test.c
- [x] 1.2 Create unit-test.c with a dedicated test runner main function
- [x] 1.3 Move existing test cases from main.c into unit-test.c and preserve behavior
- [x] 1.4 Update main.c so it contains only non-test application entry logic

## 2. Add Build and Test Targets

- [x] 2.1 Update Makefile to compile unit-test.c into a unit-test executable
- [x] 2.2 Add a Makefile target to run the unit-test executable
- [x] 2.3 Ensure clean target removes the unit-test executable

## 3. Validate Workflow

- [ ] 3.1 Run make for the main binary and confirm successful build
- [ ] 3.2 Run make unit-test and confirm successful test binary build
- [ ] 3.3 Run make test and confirm test execution returns appropriate exit status
