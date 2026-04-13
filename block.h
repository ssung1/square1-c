#ifndef BLOCK_H
#define BLOCK_H

#include "block-color.h"
#include "shape.h"

typedef struct {
    int position;
    Shape shape;
    BlockColor faceColor;
    BlockColor sideColor1;
    const BlockColor *sideColor2;
} Block;

int blockFromString(const char *token, int position, Block *block, BlockColor *sideColor2Storage);
const char *blockToString(const Block *block);

#endif
