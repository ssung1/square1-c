## Context

The codebase currently uses main.c for both entry-point logic and manual behavior checks, which makes the binary output mix application and testing concerns. The project already has a simple Makefile-driven workflow, so adding a dedicated unit-test.c executable path can stay lightweight while improving repeatability.

## Goals / Non-Goals

**Goals:**
- Move test-like checks from main.c into a dedicated unit-test.c file.
- Keep main.c focused on application behavior only.
- Extend the Makefile to build a test binary in a consistent way.
- Make test execution straightforward for contributors.

**Non-Goals:**
- Introduce third-party test frameworks.
- Add code coverage tooling.
- Refactor unrelated modules beyond what is needed to isolate tests.

## Decisions

- Use a standalone C test runner source file named unit-test.c.
Rationale: This matches the project size and avoids dependency overhead while still separating concerns.
Alternative considered: embed tests in main.c behind preprocessor flags. Rejected because it keeps mixed responsibilities.

- Keep tests as deterministic print-and-return style checks.
Rationale: Existing project complexity is low, so explicit assertions with process exit status are sufficient.
Alternative considered: a full assertion macro library. Rejected as premature.

- Add Makefile targets for building unit-test and running tests.
Rationale: Keeps verification integrated with existing toolchain and easy to invoke.
Alternative considered: manual compile commands in README. Rejected due to drift risk.

## Risks / Trade-offs

- [No external test framework] -> Mitigation: keep tests small and explicit, and adopt a framework later if complexity grows.
- [Separate test binary can duplicate setup code] -> Mitigation: extract common helpers only when duplication appears.
- [Target naming could diverge from contributor expectations] -> Mitigation: use clear Makefile target names and keep them documented.
