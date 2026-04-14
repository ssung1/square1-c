## Context

`cubeFaceToString` currently outputs blocks sorted by ascending position as a space-separated string, using a static 256-byte buffer. The function always places the lowest-position block first. When this lowest block is at position 0, the output starts with the first block. When it is at position 1, the output still starts with position-1 block, but callers may incorrectly assume it is at position 0 without additional context.

## Goals / Non-Goals

**Goals:**
- Prefix the output string with `*` when the lowest block position is 1 (not 0)
- Preserve all existing output when the lowest position is 0 or ≥ 2
- Maintain the same static buffer approach and memory footprint

**Non-Goals:**
- Changing the block sort order or output format
- Adding prefix logic for any position other than 1
- Modifying the function signature

## Decisions

### Find the minimum block position first

Before building the output string, scan the face's blocks to determine the minimum position. If it is 1, output `*` to the buffer first, then continue with the space-separated blocks as before.

**Rationale:** Requires only a single O(n) scan over blocks before formatting. Keeps the logic localized.

**Alternative considered:** Determine the minimum during the qsort output phase. Adds unnecessary complexity; simpler to do two passes (find min, then format).

### Prefix placement in the static buffer

Insert `*` at buffer offset 0, then write the block string starting at offset 1. Ensure `snprintf` accounts for the reduced remaining buffer size.

**Rationale:** Non-intrusive; does not affect how blocks are formatted, only prepends a marker.

### No prefix for non-1 minimum positions

Only apply the prefix when `minPosition == 1`. All other values (0, 2, 3, ..., 11) produce unprefixed output.

**Rationale:** Position 0 is "canonical" (no marker needed); positions ≥ 2 are rare edge cases unrelated to the ambiguity problem. Minimizes output changes.

## Risks / Trade-offs

- [Risk] Buffer overflow if prefix reduces available space below the longest possible block string → Mitigation: Use `snprintf` with reduced buffer size (`sizeof(buffer) - 1`).
- [Risk] Callers unprepared for `*` prefix in their parsing → Mitigation: This is a spec change; callers must update. Document in spec.
- [Risk] Position 1 is not the most common case, so prefix rarely appears → Mitigation: This is intentional; prefix marks the exceptional case.

## Migration Plan

No migration complexity. This is purely an additive output change. Callers that ignore the prefix will still parse block data correctly; callers that need positional context can now detect it.
