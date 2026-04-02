## Context

The project currently has BlockColor and Shape enums, but no composite structure combining them with positional data. Adding a Block structure provides a container for game block properties and establishes a pattern for aggregate types in the system.

## Goals / Non-Goals

**Goals:**
- Introduce a canonical `Block` structure combining position, shape, and color information.
- Define the structure with the five specified properties: position, shape, faceColor, sideColor1, sideColor2.
- Place declarations in `block.h` for inclusion by other modules, with implementations in `block.c`.

**Non-Goals:**
- Adding methods or functions for Block manipulation.
- Adding validation logic for property ranges.
- Integrating Block into application logic beyond basic compile validation.
- Introducing extra dependencies or changing build tooling.

## Decisions

- Place structure declaration in `block.h` and forward declarations/const definitions in `block.c`.
Rationale: separation of interface (header) and implementation is standard C practice.
Alternative considered: all code in header. Rejected as less clean for this composite type.

- Use field names matching the user specification: `position`, `shape`, `faceColor`, `sideColor1`, `sideColor2`.
Rationale: clear, self-documenting naming aligned with domain concepts.
Alternative considered: abbreviated names. Rejected for reduced readability.

- Define position as an integer without explicit range checking in the struct.
Rationale: struct itself is a data container; range validation belongs in higher-level code.
Alternative considered: add validation getters. Rejected to keep struct definition minimal.

## Risks / Trade-offs

- [Position integer not constrained by type] -> Mitigation: range (0-11) enforced at call sites via code review and tests.
- [Three color fields may seem verbose] -> Mitigation: matches user requirements and enables precise 3D block rendering.
- [No accessor functions limits future refactoring] -> Mitigation: can be added in future changes without breaking binary compatibility.
