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
