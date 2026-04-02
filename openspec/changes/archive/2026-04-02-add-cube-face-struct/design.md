## Context

The codebase already models individual pieces with the Block structure, including a position field that can describe radial placement on a face. There is not yet a face-level structure that groups those Blocks into a single ordered collection, so the project has no dedicated type for representing one cube face.

## Goals / Non-Goals

**Goals:**
- Add a dedicated CubeFace structure declaration in cube-face.h.
- Represent a face as an ordered collection of Block values.
- Preserve Block.position as the radial placement indicator for each Block within the face.
- Keep the design header-only and lightweight for initial adoption.

**Non-Goals:**
- Implement face mutation helpers or allocation utilities.
- Define solving or rotation algorithms.
- Change the existing Block structure layout.

## Decisions

- Define CubeFace in a dedicated header file named cube-face.h.
Rationale: This matches the current project pattern of separate type headers and keeps the new model reusable across modules.
Alternative considered: place CubeFace in block.h. Rejected because it mixes piece-level and face-level concerns.

- Represent the contained Blocks using a count field plus a flexible array member of Block values.
Rationale: The request calls for an array of Block objects, and a flexible array member keeps that representation explicit in C while allowing different face sizes.
Alternative considered: use a Block pointer field. Rejected because it weakens the direct “contains an array” model and pushes ownership semantics into the first version of the type.
Alternative considered: use a fixed-size Block array. Rejected because the required face size is not defined yet.

- Treat the order of blocks in the array as face order, with each Block.position continuing to describe radial placement.
Rationale: This preserves the existing meaning of position and allows callers to validate or interpret arrangement without duplicating location fields at the face level.

## Risks / Trade-offs

- [Flexible array members require separate allocation sizing] -> Mitigation: keep initial scope limited to the structure definition and document that helper constructors are out of scope.
- [Array order and Block.position could diverge] -> Mitigation: require that CubeFace preserve radial arrangement semantics in the spec.
- [Future algorithms may require additional metadata] -> Mitigation: keep CubeFace minimal now and extend it in a later change if needed.
