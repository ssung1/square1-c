## Context

The codebase already supports immutable operations on Cube objects: top rotation, bottom rotation, and flip. The new `operate` API composes these operations from a compact DSL where each token is up to 3 characters long. Cube history already exists as a string field and should track operations performed.

## Goals / Non-Goals

**Goals:**
- Parse operation strings in 3-char token units (last token may be shorter).
- Execute token operations in order: top rotation, optional bottom rotation, optional flip.
- Preserve immutability by returning a new Cube and leaving input unchanged.
- Append original operation string to returned cube history.

**Non-Goals:**
- Introducing delimiters or variable-length token parsing beyond fixed 3-char chunking.
- Supporting rotation digits beyond `b` (11).
- Mutating input Cube in place.

## Decisions

- `operate(const Cube *cube, const char *ops)` will be public in `cube.h`.
- Each token is interpreted positionally:
- index 0: required top-rotation digit
- index 1: optional bottom-rotation digit
- index 2: optional flip marker (` `)
- Tokens are read from left to right in chunks of 3; tail chunk can be length 1 or 2.
- Invalid input (NULL cube/ops, invalid digit, invalid 3rd char, bad 2nd char) returns NULL.
- Execution is pipelined with immutable helpers:
- start from a clone of input cube
- apply each operation by replacing current cube with returned copy
- free intermediate cubes along the way
- Final history is previous history + operation string.

## Risks / Trade-offs

- [Risk] Memory leaks during chained immutable operations -> Mitigation: free intermediate cube after each successful step and centralize cleanup on error.
- [Risk] Ambiguity around third character semantics -> Mitigation: require third char to be exactly space when present; reject others.
- [Risk] History concatenation overflow/alloc failure -> Mitigation: allocate exact length and return NULL on allocation failure.
