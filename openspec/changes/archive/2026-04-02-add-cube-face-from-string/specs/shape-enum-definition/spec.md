## MODIFIED Requirements

### Requirement: Project SHALL define Shape and Geometry in dedicated files
The project SHALL define a `Geometry` enum and a `Shape` structure in `shape.h`, and define shape constants in `shape.c`.

#### Scenario: Dedicated shape files exist
- **WHEN** a developer inspects the project files
- **THEN** `shape.h` contains Geometry and Shape type definitions and `shape.c` contains shape constant definitions

### Requirement: Geometry SHALL provide exactly two specified members
The `Geometry` enum SHALL include exactly two members representing triangle and kite geometry.

#### Scenario: All required geometry members are present
- **WHEN** the `Geometry` enum declaration is reviewed
- **THEN** it includes exactly two members corresponding to TRIANGLE and KITE

### Requirement: Shape constants SHALL expose geometry kind and size
The project SHALL provide two shape constants, `SHAPE_TRIANGLE` and `SHAPE_KITE`, each with geometry kind and size values.

#### Scenario: Triangle shape constant values
- **WHEN** `SHAPE_TRIANGLE` is reviewed
- **THEN** it has triangle geometry kind and size value 1

#### Scenario: Kite shape constant values
- **WHEN** `SHAPE_KITE` is reviewed
- **THEN** it has kite geometry kind and size value 2

### Requirement: Shape model SHALL be reusable by other modules
The Shape and Geometry declarations and constants SHALL be available for reuse by other C modules through standard include/compilation workflows.

#### Scenario: Shape model is available to other compilation units
- **WHEN** another module includes `shape.h` and references `Shape`, `Geometry`, or shape constants
- **THEN** the project compiles without requiring duplicated declarations
