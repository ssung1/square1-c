#include "block.h"
#include <string.h>

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
