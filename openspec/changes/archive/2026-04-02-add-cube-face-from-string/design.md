## Context

The project currently defines Block and CubeFace data structures, but it has no parser that can convert a compact text representation into a populated CubeFace. A parser is needed to support fixture-style input where each token describes one block by color initials and implied shape.

## Goals / Non-Goals

**Goals:**
- Add a function in cube-face.c that constructs a CubeFace from a whitespace-delimited string.
- Tokenize on one or more contiguous whitespace characters.
- Parse each token into one Block in token order.
- Infer shape and color fields from token length and characters.
- Add stringToBlockColor in block-color.c and declare it in block-color.h.
- Convert Shape from enum-only to a structure with geometry kind and size.
- Define SHAPE_TRIANGLE and SHAPE_KITE constants in shape.c with sizes 1 and 2.
- Compute Block.position using previous block shape size (+1 after triangle, +2 after kite).
- Add unit tests that verify cubeFaceFromString behavior for tokenization, field mapping, and position progression.

**Non-Goals:**
- Introduce a full grammar or advanced error recovery.
- Replace the existing blockColorToString behavior.

## Decisions

- Parse tokens as length 2 or length 3 only.
Rationale: The provided mapping fully defines behavior for two-character and three-character tokens. Other lengths are considered invalid input for the first version.
Alternative considered: support one-character tokens. Rejected because no complete field mapping is defined.

- Interpret token fields deterministically:
  - length 2: SHAPE_TRIANGLE, faceColor=char0, sideColor1=char1, sideColor2=NULL
  - length 3: SHAPE_KITE, faceColor=char0, sideColor1=char1, sideColor2=char2
Rationale: This matches requested parsing semantics exactly.

- Convert shape model to structure-based representation:
  - define a Geometry enum (or equivalent) for triangle/kite kind
  - define Shape struct with geometry kind and size fields
  - define SHAPE_TRIANGLE and SHAPE_KITE constants in shape.c
Rationale: Position increments are shape-size driven and explicit size data belongs in the shape model.
Alternative considered: keep enum-only Shape and hardcode increments in parser. Rejected due duplicated semantics and weaker model clarity.

- Allocate CubeFace using block count discovered from tokenization and store Block values in flexible-array order.
Rationale: CubeFace is defined with blockCount plus flexible array member; this keeps stored order equal to input token order.
Alternative considered: store pointers to Block. Rejected due unnecessary ownership complexity.

- Add stringToBlockColor as reverse mapping of blockColorToString.
Rationale: Keeps color translation logic centralized and reusable by CubeFace parsing and future parsing code.

- Position calculation depends on previous block shape:
  - first block position = 0
  - next position increment = previous block shape size
Rationale: Implements the requested radial progression rule while centralizing size meaning in the shape constants.
- Extend unit-test.c with parser-focused cases.
Rationale: The parser introduces tokenization, conversion, and position rules that should be validated by automated tests to prevent regressions.
Alternative considered: rely only on manual runs in main. Rejected due weaker repeatability.

## Risks / Trade-offs

- [Invalid token characters] -> Mitigation: define deterministic fallback/error behavior in implementation and tests.
- [Ambiguity in token-length wording] -> Mitigation: lock parser behavior to 2-or-3 character tokens in spec and tasks.
- [Manual memory management for flexible array allocation] -> Mitigation: include explicit allocation-size and cleanup tasks.
- [Shape model migration impacts existing references] -> Mitigation: include dedicated migration tasks for shape.h, shape.c, and callers.
- [Parser regressions are hard to spot manually] -> Mitigation: add unit tests for happy path and invalid-input behavior.
