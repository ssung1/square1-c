## Why

The project can define individual Blocks and a CubeFace container, but it cannot yet construct a face directly from a compact string definition. Adding string-based CubeFace construction enables straightforward loading of face data and improves ergonomics for tests, fixtures, and future parsers.

## What Changes

- Add a new constructor-style function in cube-face.c that builds a CubeFace from a whitespace-delimited string.
- Parse each token as one Block definition and append Blocks in token order.
- Interpret token lengths: 2 characters for triangle blocks and 3 characters for kite blocks.
- Add reverse color conversion support via stringToBlockColor in block-color.c and declare it in block-color.h.
- Add/extend unit tests to verify cubeFaceFromString parsing behavior, including shape inference, color mapping, and position progression.
- **BREAKING**: Convert Shape from an enum-only definition into a structure that contains a geometry-kind field (renamed from Shape enum to Geometry, or equivalent) plus a size property.
- Define two shape constants in shape.c: SHAPE_TRIANGLE with size 1 and SHAPE_KITE with size 2.
- Compute Block.position progressively using the previous block shape size semantics: +1 after triangle, +2 after kite.

## Capabilities

### New Capabilities
- cube-face-from-string: Converts a whitespace-delimited face definition string into a CubeFace containing ordered Block values.
- block-color-from-string: Converts a one-character color code into the corresponding BlockColor value.

### Modified Capabilities
- shape-enum-definition: Replace the enum-only Shape model with a structure-based representation that includes geometry kind and size, while preserving SHAPE_TRIANGLE and SHAPE_KITE as constants.

## Impact

- Affected code: new cube-face.c, updates to cube-face.h if constructor declaration is needed, updates to block-color.c and block-color.h, updates to shape.h/shape.c for the new structure and constants, and updates to test sources (such as unit-test.c).
- Build/developer workflow: existing Makefile targets continue to work with added source file integration.
- APIs/systems: introduces parsing APIs for face construction and reverse color translation, and changes shape modeling from enum-only to structure-plus-constants.
