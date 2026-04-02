#ifndef BLOCK_COLOR_H
#define BLOCK_COLOR_H

typedef enum {
    BLOCK_COLOR_WHITE = 0,
    BLOCK_COLOR_GREEN = 1,
    BLOCK_COLOR_YELLOW = 2,
    BLOCK_COLOR_RED = 3,
    BLOCK_COLOR_BLUE = 4,
    BLOCK_COLOR_ORANGE = 5
} BlockColor;

const char *blockColorToString(BlockColor color);

#endif /* BLOCK_COLOR_H */
