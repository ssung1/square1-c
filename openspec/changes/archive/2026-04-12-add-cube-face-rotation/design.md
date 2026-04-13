## Context

`cubeFaceFromString` builds faces with blocks that carry a `position` field used for radial placement. The codebase currently has no operation that updates all positions as a group to model a face rotation. A rotation operation must preserve each block’s shape/colors and only transform position values using Square-1’s 12-slot ring semantics.

## Goals / Non-Goals

**Goals:**
- Provide a simple public API to rotate a `CubeFace` counterclockwise.
- Keep all resulting positions normalized to `0..11`.
- Preserve current behavior of parsing/string conversion and existing tests.

**Non-Goals:**
- Clockwise rotation API.
- Whole-cube move sequencing or multi-face synchronization.
- Any change to block memory layout.

## Decisions

- Add a public function in the CubeFace module: `void rotateCubeFaceCounterclockwise(CubeFace *face, int count);`.
: Rationale: keeps rotation behavior localized in the owning module of face/block arrays.
- Use modulo-12 normalization per block position after adding `count`.
: Rationale: directly implements ring behavior (`12 -> 0`, `13 -> 1`).
- Treat `NULL` face as a no-op.
: Rationale: consistent defensive behavior and avoids caller crashes in tests/simulation glue.
- Accept any integer count, normalizing it with modulo arithmetic before application.
: Rationale: handles larger values while preserving expected behavior for hex-range inputs `0..b`.

Alternatives considered:
- Rebuild a new `CubeFace` from rotated tokens.
: Rejected due to avoidable allocation/parsing overhead and more failure modes.

## Risks / Trade-offs

- [Risk] Ambiguity around clockwise vs counterclockwise direction in future features → Mitigation: encode direction in function name and tests.
- [Risk] Future code may assume positions can reach 12 → Mitigation: enforce normalization to `0..11` in one helper path.
- [Trade-off] Public API addition increases surface area slightly → Mitigation: keep function narrow and documented by tests.
