#include "cube.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicateString(const char *text) {
    size_t len = strlen(text);
    char *copy = malloc(len + 1);

    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, text, len + 1);
    return copy;
}

static int normalizePosition(int position) {
    int normalized = position % 12;

    if (normalized < 0) {
        normalized += 12;
    }

    return normalized;
}

static void freeCubeInternal(Cube *cube) {
    if (cube == NULL) {
        return;
    }

    free(cube->topFace);
    free(cube->bottomFace);
    free(cube->history);
    free(cube);
}

static Cube *cloneCube(const Cube *cube) {
    Cube *copy;

    if (cube == NULL) {
        return NULL;
    }

    copy = malloc(sizeof(Cube));
    if (copy == NULL) {
        return NULL;
    }

    copy->topFace = rotateClubFaceClockwise(cube->topFace, 0);
    if (copy->topFace == NULL) {
        free(copy);
        return NULL;
    }

    copy->bottomFace = rotateClubFaceClockwise(cube->bottomFace, 0);
    if (copy->bottomFace == NULL) {
        free(copy->topFace);
        free(copy);
        return NULL;
    }

    copy->history = duplicateString((cube->history != NULL) ? cube->history : "");
    if (copy->history == NULL) {
        free(copy->bottomFace);
        free(copy->topFace);
        free(copy);
        return NULL;
    }

    return copy;
}

Cube *cubeFromString(const char *topFace, const char *bottomFace) {
    Cube *cube = malloc(sizeof(Cube));

    if (cube == NULL) {
        return NULL;
    }

    cube->topFace = cubeFaceFromString(topFace);
    if (cube->topFace == NULL) {
        free(cube);
        return NULL;
    }

    cube->bottomFace = cubeFaceFromString(bottomFace);
    if (cube->bottomFace == NULL) {
        free(cube->topFace);
        free(cube);
        return NULL;
    }

    cube->history = duplicateString("");
    if (cube->history == NULL) {
        free(cube->bottomFace);
        free(cube->topFace);
        free(cube);
        return NULL;
    }

    return cube;
}

const char *cubeToString(const Cube *cube) {
    static char buffer[1024];
    char topFaceBuffer[256];
    char bottomFaceBuffer[256];
    const char *history;
    const char *topFaceString;
    const char *bottomFaceString;
    int written;

    if (cube == NULL) {
        return NULL;
    }

    topFaceString = cubeFaceToString(cube->topFace);
    if (topFaceString == NULL || strlen(topFaceString) >= sizeof(topFaceBuffer)) {
        return NULL;
    }
    memcpy(topFaceBuffer, topFaceString, strlen(topFaceString) + 1);

    bottomFaceString = cubeFaceToString(cube->bottomFace);
    if (bottomFaceString == NULL || strlen(bottomFaceString) >= sizeof(bottomFaceBuffer)) {
        return NULL;
    }
    memcpy(bottomFaceBuffer, bottomFaceString, strlen(bottomFaceString) + 1);

    history = (cube->history != NULL) ? cube->history : "";
    written = snprintf(buffer, sizeof(buffer), "%s\n%s\n%s", history, topFaceBuffer, bottomFaceBuffer);

    if (written < 0 || (size_t)written >= sizeof(buffer)) {
        return NULL;
    }

    return buffer;
}

Cube *rotateCubeTopFaceClockwise(const Cube *cube, int count) {
    Cube *rotatedCube;
    CubeFace *rotatedTopFace;

    if (cube == NULL) {
        return NULL;
    }

    rotatedCube = cloneCube(cube);
    if (rotatedCube == NULL) {
        return NULL;
    }

    rotatedTopFace = rotateClubFaceClockwise(cube->topFace, count);
    if (rotatedTopFace == NULL) {
        freeCubeInternal(rotatedCube);
        return NULL;
    }

    free(rotatedCube->topFace);
    rotatedCube->topFace = rotatedTopFace;
    return rotatedCube;
}

Cube *rotateCubeBottomFaceClockwise(const Cube *cube, int count) {
    Cube *rotatedCube;
    CubeFace *rotatedBottomFace;

    if (cube == NULL) {
        return NULL;
    }

    rotatedCube = cloneCube(cube);
    if (rotatedCube == NULL) {
        return NULL;
    }

    rotatedBottomFace = rotateClubFaceClockwise(cube->bottomFace, count);
    if (rotatedBottomFace == NULL) {
        freeCubeInternal(rotatedCube);
        return NULL;
    }

    free(rotatedCube->bottomFace);
    rotatedCube->bottomFace = rotatedBottomFace;
    return rotatedCube;
}

static CubeFace *buildFlippedFace(const CubeFace *sameFace, const CubeFace *otherFace) {
    size_t i;
    size_t blockCount = 0;
    size_t blockBytes;
    size_t sideColor2Bytes;
    CubeFace *resultFace;
    BlockColor *sideColor2Storage;
    size_t writeIndex = 0;
    size_t sideColor2Index = 0;

    if (sameFace == NULL || otherFace == NULL) {
        return NULL;
    }

    for (i = 0; i < sameFace->blockCount; ++i) {
        if (sameFace->blocks[i].position >= 6) {
            ++blockCount;
        }
    }

    for (i = 0; i < otherFace->blockCount; ++i) {
        if (otherFace->blocks[i].position < 6) {
            ++blockCount;
        }
    }

    blockBytes = blockCount * sizeof(Block);
    sideColor2Bytes = blockCount * sizeof(BlockColor);
    resultFace = malloc(sizeof(CubeFace) + blockBytes + sideColor2Bytes);
    if (resultFace == NULL) {
        return NULL;
    }

    resultFace->blockCount = blockCount;
    if (blockCount == 0) {
        return resultFace;
    }

    sideColor2Storage = (BlockColor *)((char *)resultFace->blocks + blockBytes);

    for (i = 0; i < sameFace->blockCount; ++i) {
        const Block *source = &sameFace->blocks[i];
        Block *dest;

        if (source->position < 6) {
            continue;
        }

        dest = &resultFace->blocks[writeIndex++];
        *dest = *source;
        if (source->sideColor2 != NULL) {
            sideColor2Storage[sideColor2Index] = *source->sideColor2;
            dest->sideColor2 = &sideColor2Storage[sideColor2Index++];
        } else {
            dest->sideColor2 = NULL;
        }
    }

    for (i = 0; i < otherFace->blockCount; ++i) {
        const Block *source = &otherFace->blocks[i];
        Block *dest;

        if (source->position >= 6) {
            continue;
        }

        dest = &resultFace->blocks[writeIndex++];
        *dest = *source;
        dest->position = normalizePosition(6 - source->position - source->shape.size);
        if (source->sideColor2 != NULL) {
            sideColor2Storage[sideColor2Index] = *source->sideColor2;
            dest->sideColor2 = &sideColor2Storage[sideColor2Index++];
        } else {
            dest->sideColor2 = NULL;
        }
    }

    return resultFace;
}

static int decodeRotationChar(char c, int *rotation) {
    if (rotation == NULL) {
        return 0;
    }

    if (c >= '0' && c <= '9') {
        *rotation = c - '0';
        return 1;
    }

    if (c >= 'a' && c <= 'b') {
        *rotation = 10 + (c - 'a');
        return 1;
    }

    if (c >= 'A' && c <= 'B') {
        *rotation = 10 + (c - 'A');
        return 1;
    }

    return 0;
}

static int isFaceFlippable(const CubeFace *face) {
    size_t i;
    int offset;

    if (face == NULL) {
        return 0;
    }

    for (i = 0; i < face->blockCount; ++i) {
        for (offset = 1; offset < face->blocks[i].shape.size; ++offset) {
            int interior = (face->blocks[i].position + offset) % 12;
            if (interior == 0 || interior == 6) {
                return 0;
            }
        }
    }

    return 1;
}

int isFlippable(const Cube *cube) {
    if (cube == NULL) {
        return 0;
    }

    return isFaceFlippable(cube->topFace) && isFaceFlippable(cube->bottomFace);
}

Cube *flip(const Cube *cube) {
    Cube *flippedCube;

    if (cube == NULL) {
        return NULL;
    }

    flippedCube = malloc(sizeof(Cube));
    if (flippedCube == NULL) {
        return NULL;
    }

    flippedCube->topFace = buildFlippedFace(cube->topFace, cube->bottomFace);
    if (flippedCube->topFace == NULL) {
        free(flippedCube);
        return NULL;
    }

    flippedCube->bottomFace = buildFlippedFace(cube->bottomFace, cube->topFace);
    if (flippedCube->bottomFace == NULL) {
        free(flippedCube->topFace);
        free(flippedCube);
        return NULL;
    }

    flippedCube->history = duplicateString((cube->history != NULL) ? cube->history : "");
    if (flippedCube->history == NULL) {
        free(flippedCube->bottomFace);
        free(flippedCube->topFace);
        free(flippedCube);
        return NULL;
    }

    return flippedCube;
}

Cube *operate(const Cube *cube, const char *ops) {
    Cube *current;
    size_t i;
    size_t opsLen;

    if (cube == NULL || ops == NULL) {
        return NULL;
    }

    current = cloneCube(cube);
    if (current == NULL) {
        return NULL;
    }

    opsLen = strlen(ops);
    for (i = 0; i < opsLen; i += 3) {
        size_t tokenLen = opsLen - i;
        int topRotation;
        Cube *next;

        if (tokenLen > 3) {
            tokenLen = 3;
        }

        if (!decodeRotationChar(ops[i], &topRotation)) {
            freeCubeInternal(current);
            return NULL;
        }

        next = rotateCubeTopFaceClockwise(current, topRotation);
        if (next == NULL) {
            freeCubeInternal(current);
            return NULL;
        }
        freeCubeInternal(current);
        current = next;

        if (tokenLen >= 2) {
            int bottomRotation;

            if (!decodeRotationChar(ops[i + 1], &bottomRotation)) {
                freeCubeInternal(current);
                return NULL;
            }

            next = rotateCubeBottomFaceClockwise(current, bottomRotation);
            if (next == NULL) {
                freeCubeInternal(current);
                return NULL;
            }
            freeCubeInternal(current);
            current = next;
        }

        if (tokenLen == 3) {
            if (ops[i + 2] != ' ') {
                freeCubeInternal(current);
                return NULL;
            }

            next = flip(current);
            if (next == NULL) {
                freeCubeInternal(current);
                return NULL;
            }
            freeCubeInternal(current);
            current = next;
        }
    }

    {
        const char *baseHistory = (current->history != NULL) ? current->history : "";
        size_t baseLen = strlen(baseHistory);
        char *newHistory = malloc(baseLen + opsLen + 1);

        if (newHistory == NULL) {
            freeCubeInternal(current);
            return NULL;
        }

        memcpy(newHistory, baseHistory, baseLen);
        memcpy(newHistory + baseLen, ops, opsLen + 1);

        free(current->history);
        current->history = newHistory;
    }

    return current;
}
