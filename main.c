#include <stdio.h>
#include "block-color.h"
#include "shape.h"
#include "block.h"

int main(void) {
    BlockColor color = BLOCK_COLOR_WHITE;
    Shape shape = SHAPE_TRIANGLE;
    Block block = {.position = 0, .shape = SHAPE_TRIANGLE, .faceColor = BLOCK_COLOR_WHITE, .sideColor1 = BLOCK_COLOR_GREEN, .sideColor2 = BLOCK_COLOR_BLUE};
    (void)color;
    (void)shape;
    (void)block;
    return 0;
}
