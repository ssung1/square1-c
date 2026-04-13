## Context

The project has `blockToString` that converts a single Block to a 2-3 character color string. No face-level string constructor exists, limiting testability and debugging visibility. A face string should reflect the positional order of blocks so parsing and round-trip conversion are intuitive.

## Goals / Non-Goals

**Goals:**
- Provide a simple public API to convert a CubeFace to a string.
- Output blocks in ascending position order (0, 1, 2, ..., 11).
- Separate blocks with spaces for readability.
- Return a stable, reusable string (allocated by caller or in static buffer per existing blockToString pattern).

**Non-Goals:**
- Serialize internal metadata or allocation details.
- Support custom ordering or filtering.
- Persist to file or network formats.

## Decisions

- Add public function signature: `const char *cubeFaceToString(const CubeFace *face);`.
- Rationale: Matches blockToString return type and naming convention; const input prevents accidental mutations.
- Allocate a temporary buffer and sort blocks by position before stringifying.
- Rationale: Ensures consistent output regardless of insertion order in face array.
- Reuse `blockToString` for per-block encoding.
- Rationale: Eliminates duplication and ensures block string format stays aligned.
- Return NULL for NULL input.
- Rationale: Consistent error handling.

Alternatives considered:
- Output blocks in storage order (no sort).
- Rejected: Position order is semantically meaningful for Square-1 faces.

## Risks / Trade-offs

- [Risk] String buffer lifetime (static vs allocated) → Mitigation: follow blockToString pattern (static buffer, document non-reentrancy if applicable).
- [Trade-off] Sort cost on each call → Mitigation: face block count is small (max 12), sort is negligible.
