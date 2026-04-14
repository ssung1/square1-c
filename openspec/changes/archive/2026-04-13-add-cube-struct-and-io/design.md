## Context

The codebase currently models individual blocks and cube faces, including face parsing and face serialization. There is no aggregate type for the whole Square-1 state, so callers must manually coordinate top/bottom faces and history.

## Goals / Non-Goals

**Goals:**
- Introduce a `Cube` struct with top face, bottom face, and history.
- Provide `cubeFromString` to construct a cube from two face definition strings.
- Provide `cubeToString` to output three lines in this order: history, top face string, bottom face string.
- Reuse `cubeFaceFromString` and `cubeFaceToString` to avoid duplicated logic.

**Non-Goals:**
- Implement puzzle move logic in this change.
- Define a complex history grammar beyond plain string storage.
- Add persistence/storage outside in-memory structures.

## Decisions

- Use `CubeFace *` pointers for `topFace` and `bottomFace` inside `Cube`.
: Rationale: `CubeFace` is variable-sized (`blocks[]`), so pointer ownership is the practical representation.
- Store `history` as `char *`.
: Rationale: aligns with C conventions and allows dynamic content.
- `cubeFromString` returns `Cube *` and initializes history to an empty string (`""`).
: Rationale: ensures callers get a valid, deterministic initial state.
- `cubeToString` returns a string formatted as exactly three lines.
: Rationale: simple and testable full-state representation.
- If either face parse fails, construction fails and returns `NULL`.
: Rationale: avoid partially initialized cubes.

## Risks / Trade-offs

- [Risk] Memory ownership complexity for nested allocations → Mitigation: include explicit cleanup behavior and tests.
- [Risk] String buffer lifetime ambiguity in `cubeToString` → Mitigation: define and document return buffer strategy consistently with existing code style.
- [Trade-off] Returning formatted string may require fixed-size static buffer → Mitigation: keep tests constrained to expected small inputs for now.

## Migration Plan

1. Add `cube.h` and `cube.c` with struct and APIs.
2. Wire module into build and tests.
3. Add tests for parse/serialize behavior and error handling.
4. Validate via `make test`.

## Open Questions

- Should a dedicated `freeCube` function be added in this same change for ownership cleanup?
- Should `cubeToString` return `NULL` or an empty three-line form for `NULL` input?
