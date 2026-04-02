#include <stdio.h>
#include "block-color.h"
#include "shape.h"
#include "block.h"

int main(void) {
    static const BlockColor sideColor2 = BLOCK_COLOR_BLUE;
    Block block = {
        .position = 0,
        .shape = SHAPE_TRIANGLE,
        .faceColor = BLOCK_COLOR_WHITE,
        .sideColor1 = BLOCK_COLOR_GREEN,
        .sideColor2 = &sideColor2
    };

    printf("%s\n", blockToString(&block));
    return 0;
}
