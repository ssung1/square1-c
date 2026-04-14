## Context

The current `flip(const Cube *cube)` implementation builds and returns a new cube by exchanging and reflecting right-half blocks between faces. It already handles `NULL` input by returning `NULL`, but it does not guard against non-flippable states. The project already exposes `isFlippable(const Cube *cube)` which identifies legal flip states.

## Goals / Non-Goals

**Goals:**
- Enforce flippability inside `flip`.
- Return `NULL` when `cube` is non-flippable.
- Keep existing immutable behavior for valid inputs.

**Non-Goals:**
- Changing the reflection math or face-building logic.
- Changing function signatures.

## Decisions

- Add a precondition in `flip`:
- if `cube == NULL`, return `NULL` (existing behavior)
- if `!isFlippable(cube)`, return `NULL` (new behavior)
- Only run existing flip construction for valid flippable cubes.

Rationale: centralizes safety in one API boundary and avoids undefined/invalid flips even if callers skip checks.

## Risks / Trade-offs

- [Risk] Existing callers may rely on flipping non-flippable states -> Mitigation: explicit test coverage and clear return-NULL contract.
- [Risk] Slight runtime overhead from additional check -> Mitigation: single predicate call; negligible cost compared to allocation/copy work.

## Migration Plan

No data migration required. Callers should handle `NULL` return from `flip` for non-flippable cubes.
