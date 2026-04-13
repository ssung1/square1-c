#include "cube-face.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"

#define TOKEN_DELIMS " \t\r\n\v\f"
#define FACE_POSITION_COUNT 12

static int normalizeFacePosition(int position) {
    int normalized = position % FACE_POSITION_COUNT;

    if (normalized < 0) {
        normalized += FACE_POSITION_COUNT;
    }

    return normalized;
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

static int compareBlocksByPosition(const void *a, const void *b) {
    const Block *blockA = (const Block *)a;
    const Block *blockB = (const Block *)b;
    return blockA->position - blockB->position;
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

CubeFace *rotateClubFaceClockwise(const CubeFace *face, int count) {
    if (face == NULL) {
        return NULL;
    }

    size_t blockCount = face->blockCount;
    size_t blockBytes = blockCount * sizeof(Block);
    size_t sideColor2Bytes = blockCount * sizeof(BlockColor);
    CubeFace *rotatedFace = malloc(sizeof(CubeFace) + blockBytes + sideColor2Bytes);

    if (rotatedFace == NULL) {
        return NULL;
    }

    rotatedFace->blockCount = blockCount;
    if (blockCount == 0) {
        return rotatedFace;
    }

    BlockColor *sideColor2Storage = (BlockColor *)((char *)rotatedFace->blocks + blockBytes);
    size_t sideColor2Index = 0;
    int normalizedCount = normalizeFacePosition(count);

    for (size_t i = 0; i < blockCount; ++i) {
        rotatedFace->blocks[i] = face->blocks[i];
        rotatedFace->blocks[i].position = normalizeFacePosition(face->blocks[i].position + normalizedCount);

        if (face->blocks[i].sideColor2 != NULL) {
            sideColor2Storage[sideColor2Index] = *face->blocks[i].sideColor2;
            rotatedFace->blocks[i].sideColor2 = &sideColor2Storage[sideColor2Index];
            ++sideColor2Index;
        } else {
            rotatedFace->blocks[i].sideColor2 = NULL;
        }
    }

    return rotatedFace;
}

const char *cubeFaceToString(const CubeFace *face) {
    static char buffer[256];
    size_t bufferPos = 0;

    if (face == NULL) {
        return NULL;
    }

    if (face->blockCount == 0) {
        buffer[0] = '\0';
        return buffer;
    }

    Block *sortedBlocks = malloc(face->blockCount * sizeof(Block));
    if (sortedBlocks == NULL) {
        return NULL;
    }

    memcpy(sortedBlocks, face->blocks, face->blockCount * sizeof(Block));
    qsort(sortedBlocks, face->blockCount, sizeof(Block), compareBlocksByPosition);

    for (size_t i = 0; i < face->blockCount; ++i) {
        const char *blockStr = blockToString(&sortedBlocks[i]);
        size_t blockLen = strlen(blockStr);

        if (i > 0) {
            if (bufferPos + 1 >= sizeof(buffer)) {
                free(sortedBlocks);
                return NULL;
            }
            buffer[bufferPos++] = ' ';
        }

        if (bufferPos + blockLen >= sizeof(buffer)) {
            free(sortedBlocks);
            return NULL;
        }

        memcpy(&buffer[bufferPos], blockStr, blockLen);
        bufferPos += blockLen;
    }

    buffer[bufferPos] = '\0';
    free(sortedBlocks);
    return buffer;
}
