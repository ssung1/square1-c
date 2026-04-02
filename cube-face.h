#ifndef CUBE_FACE_H
#define CUBE_FACE_H

#include <stddef.h>

#include "block.h"

typedef struct {
    size_t blockCount;
    /* Blocks are stored in face order; Block.position keeps radial placement. */
    Block blocks[];
} CubeFace;

CubeFace *cubeFaceFromString(const char *definition);

#endif