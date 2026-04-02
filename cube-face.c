#include "cube-face.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "block-color.h"

#define TOKEN_DELIMS " \t\r\n\v\f"

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

static size_t countTokens(const char *text) {
    size_t count = 0;
    int inToken = 0;

    for (size_t i = 0; text[i] != '\0'; ++i) {
        if (isspace((unsigned char)text[i])) {
            inToken = 0;
            continue;
        }

        if (!inToken) {
            ++count;
            inToken = 1;
        }
    }

    return count;
}

static char *duplicateString(const char *text) {
    size_t len = strlen(text);
    char *copy = malloc(len + 1);

    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, text, len + 1);
    return copy;
}

static int parseToken(const char *token, Block *block, BlockColor *sideColor2Storage, int position) {
    size_t len = strlen(token);

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

    if (!isSupportedColorCode(token[2])) {
        return 0;
    }

    block->shape = SHAPE_KITE;
    *sideColor2Storage = stringToBlockColor(&token[2]);
    block->sideColor2 = sideColor2Storage;
    return 1;
}

CubeFace *cubeFaceFromString(const char *definition) {
    if (definition == NULL) {
        return NULL;
    }

    size_t blockCount = countTokens(definition);
    size_t blockBytes = blockCount * sizeof(Block);
    size_t sideColor2Bytes = blockCount * sizeof(BlockColor);
    CubeFace *face = malloc(sizeof(CubeFace) + blockBytes + sideColor2Bytes);

    if (face == NULL) {
        return NULL;
    }

    face->blockCount = blockCount;

    if (blockCount == 0) {
        return face;
    }

    BlockColor *sideColor2Storage = (BlockColor *)((char *)face->blocks + blockBytes);
    char *copy = duplicateString(definition);

    if (copy == NULL) {
        free(face);
        return NULL;
    }

    size_t index = 0;
    int position = 0;

    for (char *token = strtok(copy, TOKEN_DELIMS); token != NULL; token = strtok(NULL, TOKEN_DELIMS)) {
        Block *block = &face->blocks[index];

        if (!parseToken(token, block, &sideColor2Storage[index], position)) {
            free(copy);
            free(face);
            return NULL;
        }

        position += block->shape.size;
        ++index;
    }

    free(copy);
    return face;
}
