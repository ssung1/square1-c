## Context

`operate` parses DSL tokens and applies top rotation, optional bottom rotation, then optional flip when token[2] is space. After the recent `flip` safety update, calling `flip` on a non-flippable state returns `NULL`. Without a guard in `operate`, a requested flip on a non-flippable state aborts the whole operation.

## Goals / Non-Goals

**Goals:**
- In `operate`, evaluate flippability before invoking `flip` for a token with third char space.
- If not flippable, skip flip (no-op) and continue to next token.
- Preserve all existing token parsing and validation behavior.

**Non-Goals:**
- Changing `flip` behavior itself.
- Relaxing token grammar or character validation.
- Altering immutable execution semantics.

## Decisions

- In the tokenLen==3 and token[2]==' ' branch:
- `if (isFlippable(current))` apply flip exactly as today.
- `else` do nothing and keep `current` unchanged.
- Keep failure behavior for actual flip allocation errors unchanged when a flip is attempted.
- Keep invalid third-character behavior unchanged (`return NULL`).

Rationale: `operate` is a high-level sequencing DSL; skipping illegal flip requests is more ergonomic and matches desired "do nothing" semantics.

## Risks / Trade-offs

- [Risk] Silent no-op may mask user mistakes -> Mitigation: add explicit tests documenting behavior.
- [Risk] Behavior divergence from direct `flip` API -> Mitigation: keep `flip` strict; document DSL-specific conditional semantics.
