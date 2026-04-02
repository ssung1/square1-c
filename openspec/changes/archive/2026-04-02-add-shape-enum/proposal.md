## Why

Introducing a Shape enum adds a reusable type for representing geometric shapes in the project. This establishes a foundation for future code that needs to work with shape types, avoiding scattered constant definitions and ensuring consistency.

## What Changes

- Add a new Shape enum in a dedicated source file (`shape.h` with preference for header format for direct inclusion).
- Define the enum with exactly two members: TRIANGLE and KITE.
- Ensure the enum declaration is available for inclusion by other compilation units.
- Keep this change scoped to enum definition only, without adding behavior.

## Capabilities

### New Capabilities
- `shape-enum-definition`: Introduces a canonical `Shape` enum in a dedicated file for consistent shape representation across the codebase.

### Modified Capabilities
- None.

## Impact

- Affected code: adds a new top-level shape enum file (`shape.h`).
- Build/developer workflow: no additional dependencies; standard C toolchain remains sufficient.
- APIs/systems: creates a shared type contract that future modules can include.
