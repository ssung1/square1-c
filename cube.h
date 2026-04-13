#ifndef CUBE_H
#define CUBE_H

#include "cube-face.h"

typedef struct {
    CubeFace *topFace;
    CubeFace *bottomFace;
    char *history;
} Cube;

Cube *cubeFromString(const char *topFace, const char *bottomFace);
const char *cubeToString(const Cube *cube);

#endif
