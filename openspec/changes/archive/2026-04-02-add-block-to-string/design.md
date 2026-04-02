## Context

The project converts individual `BlockColor` values to strings via `blockColorToString`. However, there is no way to represent a complete `Block` as a string. The `Block` struct currently stores `sideColor2` as a value type (`BlockColor`), which cannot represent the absence of a second side color. This change adds a `blockToString` function and makes `sideColor2` a nullable pointer.

## Goals / Non-Goals

**Goals:**
- Add `blockToString(const Block *block)` in `block.c` that returns a `const char *` formed by concatenating color field strings.
- Change `sideColor2` in the `Block` struct from `BlockColor` to `const BlockColor *` to support optional absence.
- Declare `blockToString` in `block.h`.
- Update `main.c` to pass a pointer for `sideColor2`.

**Non-Goals:**
- Including `position` or `shape` in the string output.
- Dynamic memory allocation; a static buffer is sufficient given the fixed maximum output size.
- Making `faceColor` or `sideColor1` nullable.

## Decisions

- **Use a `static char` buffer for the return value.**
  Rationale: The maximum output length is 3 characters (faceColor + sideColor1 + optional sideColor2) plus a null terminator — a static `char[4]` is safe, simple, and avoids requiring callers to free memory.
  Alternative considered: return a dynamically allocated string. Rejected — unnecessary complexity for a fixed small output; requires caller memory management.
  Alternative considered: accept a caller-provided buffer. Rejected — adds verbosity at every call site.

- **Change `sideColor2` to `const BlockColor *` (pointer).**
  Rationale: directly models the user's "null means absent" requirement; idiomatic C for optional values without introducing sentinel enum values that pollute `BlockColor`.
  Alternative considered: add `BLOCK_COLOR_NONE = -1` sentinel to `BlockColor`. Rejected — mixes "no color" into the color type, which is a separate concern.
  Alternative considered: add a `bool hasSideColor2` field to `Block`. Rejected — more verbose and redundant when a pointer already encodes presence/absence.

- **Concatenation logic:**
  1. Write `blockColorToString(block->faceColor)` into position 0.
  2. Write `blockColorToString(block->sideColor1)` into position 1.
  3. If `block->sideColor2 != NULL`, write `blockColorToString(*block->sideColor2)` into position 2; otherwise leave position 2 empty.
  4. Null-terminate and return.

## Risks / Trade-offs

- [Breaking change to `Block` struct] → Mitigation: update `main.c` as part of this change; document as breaking in proposal.
- [Static buffer is not thread-safe] → Mitigation: acceptable for a single-threaded game project at this stage; can be revisited if concurrency is introduced.
- [Pointer must remain valid for the duration of the Block's lifetime] → Mitigation: documented in the function contract; typical stack/static usage is safe.
