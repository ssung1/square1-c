## 1. Implementation
- [x] 1.1 Update `operate` flip branch in `cube.c` to check `isFlippable(current)` before calling `flip`
- [x] 1.2 When non-flippable and flip requested, skip flip as no-op and continue token processing
- [x] 1.3 Preserve existing invalid-token failure behavior

## 2. Tests
- [x] 2.1 Add test: flip token on non-flippable state in `operate` does not return NULL and behaves as no-op for flip
- [x] 2.2 Ensure existing `flip` direct-call non-flippable test remains strict (returns NULL)
- [x] 2.3 Run `make test`
