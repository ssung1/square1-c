#include "block.h"

#include <ctype.h>
#include <string.h>

static int isSupportedColorCode(char code) {
    switch ((char)tolower((unsigned char)code)) {
        case 'w':
        case 'g':
        case 'y':
        case 'r':
        case 'b':
        case 'o':
            return 1;
    }
    return 0;
}

int blockFromString(const char *token, int position, Block *block, BlockColor *sideColor2Storage) {
    size_t len;

    if (token == NULL || block == NULL) {
        return 0;
    }

    len = strlen(token);
    if (len != 2 && len != 3) {
        return 0;
    }

    if (!isSupportedColorCode(token[0]) || !isSupportedColorCode(token[1])) {
        return 0;
    }

    block->position = position;
    block->faceColor = stringToBlockColor(&token[0]);
    block->sideColor1 = stringToBlockColor(&token[1]);

    if (len == 2) {
        block->shape = SHAPE_TRIANGLE;
        block->sideColor2 = NULL;
        return 1;
    }

    if (sideColor2Storage == NULL || !isSupportedColorCode(token[2])) {
        return 0;
    }

    block->shape = SHAPE_KITE;
    *sideColor2Storage = stringToBlockColor(&token[2]);
    block->sideColor2 = sideColor2Storage;
    return 1;
}

const char *blockToString(const Block *block) {
    static char buffer[4];
    
    buffer[0] = blockColorToString(block->faceColor)[0];
    buffer[1] = blockColorToString(block->sideColor1)[0];
    
    if (block->sideColor2 != NULL) {
        buffer[2] = blockColorToString(*block->sideColor2)[0];
        buffer[3] = '\0';
    } else {
        buffer[2] = '\0';
    }
    
    return buffer;
}
