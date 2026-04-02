## Context

The project currently has a basic C scaffold with `main.c` and a `Makefile`, but no shared domain types. A dedicated `BlockColor` enum is needed as an early reusable type so future modules can represent color values consistently without ad hoc constants.

## Goals / Non-Goals

**Goals:**
- Introduce a canonical `BlockColor` enum in a dedicated file with a specific set of color members.
- Prefer placing the enum in `block-color.h` so it is directly includable by multiple C translation units.
- Define the enum with exactly these members: BLOCK_COLOR_WHITE, BLOCK_COLOR_GREEN, BLOCK_COLOR_YELLOW, BLOCK_COLOR_RED, BLOCK_COLOR_BLUE, BLOCK_COLOR_ORANGE.

**Non-Goals:**
- Adding conversion utilities (string parsing/formatting) for color values.
- Integrating the enum into application logic beyond basic compile validation.
- Introducing extra dependencies or changing build tooling.

## Decisions

- Place the enum declaration in `block-color.h`.
Rationale: enums represent shared type contracts and headers are the natural exposure point in C.
Alternative considered: `block-color.c` only. Rejected because it limits inclusion and would require additional declarations elsewhere.

- Use explicit, prefixed enum members with uppercase names (for example, `BLOCK_COLOR_RED`).
Rationale: C enums share the global identifier namespace within a translation unit, and prefixes reduce collision risk.
Alternative considered: unprefixed members like `RED`. Rejected for weaker namespace safety.

- Define the enum with exactly six color members as specified in the proposal: WHITE, GREEN, YELLOW, RED, BLUE, ORANGE.
Rationale: establishes a precise, stable contract agreed upon upfront.
Alternative considered: minimal set with room for expansion. Rejected to eliminate ambiguity.

## Risks / Trade-offs

- [Enum members fixed in first version] -> Mitigation: future enhancements treated as backward-compatible additions in later changes.
- [Specific member set may not cover all use cases initially] -> Mitigation: early validation with stakeholders before commit.
- [Header-only enum without immediate usage could drift] -> Mitigation: include simple compile check during apply to keep declaration valid.
