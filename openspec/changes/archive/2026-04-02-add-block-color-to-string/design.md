## Context

The project has a `BlockColor` enum defined in `block-color.h` with six members. Currently there is no source file for block color — the header is header-only. Adding `block-color.c` with a `blockColorToString` function introduces a canonical string conversion and establishes the pattern for pairing `.h`/`.c` files for each type.

## Goals / Non-Goals

**Goals:**
- Add `blockColorToString(BlockColor)` that returns a `const char *` for each of the six enum members.
- Declare the function in `block-color.h` so any module that includes the header can use it.
- Update the `Makefile` to compile `block-color.c`.

**Non-Goals:**
- Adding reverse (string-to-enum) conversion.
- Returning multi-character display names (e.g., `"white"`); only the single-character codes are in scope.
- Input validation or error handling for out-of-range enum values beyond a safe fallback.

## Decisions

- **Return `const char *`, not `char`.**
  Rationale: the return type is a string (as specified by the user), making it consistent with standard C string-handling patterns and extensible if multi-character strings are needed later.
  Alternative considered: return `char`. Rejected because the user specification says "converts to a string."

- **Use a `switch` statement for the mapping.**
  Rationale: explicit, readable, and the compiler warns if a new enum member is added without a corresponding case.
  Alternative considered: a lookup table (array indexed by enum value). Rejected as less safe when enum values change.

- **Return `"?"` for unknown values.**
  Rationale: avoids undefined behavior (NULL dereference) if an out-of-range value is passed; signals an unexpected value without crashing.
  Alternative considered: return NULL. Rejected — callers would need to NULL-check before every use.

- **Character mapping (first letter of each color name):**
  | Enum member            | Return value |
  |------------------------|-------------|
  | `BLOCK_COLOR_WHITE`    | `"w"`       |
  | `BLOCK_COLOR_GREEN`    | `"g"`       |
  | `BLOCK_COLOR_YELLOW`   | `"y"`       |
  | `BLOCK_COLOR_RED`      | `"r"`       |
  | `BLOCK_COLOR_BLUE`     | `"b"`       |
  | `BLOCK_COLOR_ORANGE`   | `"o"`       |

## Risks / Trade-offs

- [New `.c` file requires Makefile update] → Mitigation: add `block-color.c` to `SRC` in the Makefile as part of this change.
- [Enum member added in future without updating function] → Mitigation: `switch` without a `default` produces a compiler warning with `-Wswitch`; the fallback `"?"` is only reached if the warning is ignored.
