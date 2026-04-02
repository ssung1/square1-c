#include "block-color.h"

const char *blockColorToString(BlockColor color) {
    switch (color) {
        case BLOCK_COLOR_WHITE:  return "w";
        case BLOCK_COLOR_GREEN:  return "g";
        case BLOCK_COLOR_YELLOW: return "y";
        case BLOCK_COLOR_RED:    return "r";
        case BLOCK_COLOR_BLUE:   return "b";
        case BLOCK_COLOR_ORANGE: return "o";
    }
    return "?";
}
