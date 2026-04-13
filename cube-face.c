#include "cube-face.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_DELIMS " \t\r\n\v\f"

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

        if (!blockFromString(token, position, block, &sideColor2Storage[index])) {
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
