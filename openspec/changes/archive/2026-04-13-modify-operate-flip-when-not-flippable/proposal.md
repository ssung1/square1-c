## Why

`flip` now has a safety guard and returns `NULL` for non-flippable cubes. In `operate`, the third token character (` `) currently attempts to flip directly; this can cause the whole operation pipeline to fail. The desired behavior is softer: when a flip is requested but not legal, skip that flip and continue processing remaining tokens.

## What Changes

- Modify `operate` in `cube.c` so that when a token requests flip (`third char == space`), it first checks flippability.
- If current cube is flippable, apply flip as before.
- If current cube is not flippable, treat flip as a no-op (do nothing) and continue.
- Keep existing parsing/validation rules unchanged.
- Keep `flip` safety check unchanged (still returns `NULL` for direct non-flippable input).

## Capabilities

### New Capabilities

### Modified Capabilities
- `cube-operate-dsl`: flip step within `operate` is now conditional and becomes a no-op when cube is not flippable.

## Impact

- `cube.c`: update `operate` flip branch
- `unit-test.c`: add/adjust test coverage for non-flippable flip token behavior
