## Context

The project now has a `Cube` type with `topFace` and `bottomFace`, and a face rotation function at the `CubeFace` level. Callers currently need to manually replace a face pointer after rotating, which leaks low-level details into cube-level logic.

## Goals / Non-Goals

**Goals:**
- Add cube-level functions for rotating top and bottom faces independently.
- Keep the API focused and easy to use for future move-sequence logic.
- Reuse existing face rotation implementation.

**Non-Goals:**
- Implement complete Square-1 move notation parsing.
- Add simultaneous top+bottom composite operations.
- Change rotation math in face-level rotation implementation.

## Decisions

- Add `rotateCubeTopFaceClockwise(const Cube *cube, int count)` and `rotateCubeBottomFaceClockwise(const Cube *cube, int count)` in `cube.c` and declare in `cube.h`, both returning `Cube *`.
: Rationale: explicit immutable API contract at cube level.
- Implement both APIs by creating and returning a new Cube copy; never mutate the input Cube.
: Rationale: keeps state transitions explicit and safer for callers.
- Implement cube-copy semantics by cloning history and both faces; rotate only the target face in the returned copy.
: Rationale: preserves non-target face and original cube state.
- If input cube pointer is NULL or allocation fails, return `NULL`.
: Rationale: deterministic failure semantics for immutable constructors.

## Risks / Trade-offs

- [Risk] Memory management complexity from deep-copying cube members -> Mitigation: centralize copy/cleanup paths and test failure-safe behavior.
- [Risk] Confusion between cube-level and face-level function names -> Mitigation: explicit `TopFace` / `BottomFace` naming in APIs and tests.

## Migration Plan

1. Add new API declarations to `cube.h`.
2. Implement rotation helpers in `cube.c` using face-level rotation.
3. Add tests validating target-face rotation and non-target face unchanged behavior.
4. Run `make test` and verify success.

## Open Questions

- None.
