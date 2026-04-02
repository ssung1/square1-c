#ifndef BLOCK_H
#define BLOCK_H

#include "block-color.h"
#include "shape.h"

typedef struct {
    int position;
    Shape shape;
    BlockColor faceColor;
    BlockColor sideColor1;
    BlockColor sideColor2;
} Block;

#endif
