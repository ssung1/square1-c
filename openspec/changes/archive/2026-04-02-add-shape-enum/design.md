## Context

The project currently has C scalar types and BlockColor enum, but no Shape enum. Adding a dedicated Shape enum provides a second reusable type for the system, establishing a pattern for type contracts.

## Goals / Non-Goals

**Goals:**
- Introduce a canonical `Shape` enum in a dedicated file with exactly two members.
- Place the enum in `shape.h` so it is directly includable by multiple C translation units.
- Define the enum with exactly these members: TRIANGLE and KITE.

**Non-Goals:**
- Adding conversion utilities or string representations for shapes.
- Integrating shapes into application logic beyond basic compile validation.
- Introducing extra dependencies or changing build tooling.

## Decisions

- Place the enum declaration in `shape.h`.
Rationale: enums represent shared type contracts and headers are the natural exposure point in C.
Alternative considered: `shape.c` only. Rejected because it limits inclusion and would require additional declarations elsewhere.

- Use explicit, prefixed enum members (for example, `SHAPE_TRIANGLE`).
Rationale: C enums share the global identifier namespace within a translation unit, and prefixes reduce collision risk.
Alternative considered: unprefixed members like `TRIANGLE`. Rejected for weaker namespace safety.

- Define the enum with exactly two members as specified: TRIANGLE and KITE.
Rationale: establishes a precise, stable contract agreed upon upfront.
Alternative considered: minimal set with room for expansion. Rejected to eliminate ambiguity.

## Risks / Trade-offs

- [Enum members fixed in first version] -> Mitigation: future enhancements treated as backward-compatible additions in later changes.
- [Only two members may feel incomplete] -> Mitigation: scoped proposal is intentional; future changes can extend the enum.
- [Header-only enum without immediate usage could drift] -> Mitigation: include simple compile check during apply to keep declaration valid.
