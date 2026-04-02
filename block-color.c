#include "block-color.h"

#include <ctype.h>
#include <stddef.h>

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

BlockColor stringToBlockColor(const char *symbol) {
    if (symbol == NULL || symbol[0] == '\0') {
        /* Deterministic fallback for invalid input. */
        return BLOCK_COLOR_WHITE;
    }

    switch (tolower((unsigned char)symbol[0])) {
        case 'w': return BLOCK_COLOR_WHITE;
        case 'g': return BLOCK_COLOR_GREEN;
        case 'y': return BLOCK_COLOR_YELLOW;
        case 'r': return BLOCK_COLOR_RED;
        case 'b': return BLOCK_COLOR_BLUE;
        case 'o': return BLOCK_COLOR_ORANGE;
    }

    /* Deterministic fallback for unsupported color codes. */
    return BLOCK_COLOR_WHITE;
}
