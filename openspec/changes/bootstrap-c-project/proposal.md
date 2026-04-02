## Why

This project needs a minimal, reliable C build baseline so implementation can begin with predictable tooling and entry points. Establishing this now reduces setup churn and lets future tasks focus on functionality instead of scaffolding.

## What Changes

- Add an initial C entry point in `main.c` that currently does no work.
- Include `stdio.h` in `main.c` to support immediate extension for output and basic I/O.
- Add a `Makefile` with standard targets to build and clean the project.
- The executable output of `Makefile` shall be named `square1`
- Define expected behavior and build workflow in OpenSpec artifacts so implementation is structured and reviewable.

## Capabilities

### New Capabilities
- `c-project-bootstrap`: Establishes a compilable C project foundation with a starter `main.c` and `Makefile`-driven build flow.

### Modified Capabilities
- None.

## Impact

- Affected code: new top-level `main.c` and `Makefile`.
- Build/developer workflow: introduces `make`-based compile and cleanup commands.
- Dependencies: relies on a standard C compiler and `make` available in the development environment.
