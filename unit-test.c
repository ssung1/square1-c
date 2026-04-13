#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "cube.h"
#include "cube-face.h"
#include "shape.h"

static char *duplicateStringForTest(const char *text) {
    size_t len = strlen(text);
    char *copy = malloc(len + 1);

    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, text, len + 1);
    return copy;
}

static void freeCubeForTest(Cube *cube) {
    if (cube == NULL) {
        return;
    }

    free(cube->topFace);
    free(cube->bottomFace);
    free(cube->history);
    free(cube);
}

static int assertEqual(const char *name, const char *expected, const char *actual) {
    if (strcmp(expected, actual) == 0) {
        printf("PASS: %s\n", name);
        return 1;
    }

    printf("FAIL: %s (expected: %s, actual: %s)\n", name, expected, actual);
    return 0;
}

static int assertEqualInt(const char *name, int expected, int actual) {
    if (expected == actual) {
        printf("PASS: %s\n", name);
        return 1;
    }

    printf("FAIL: %s (expected: %d, actual: %d)\n", name, expected, actual);
    return 0;
}

static int assertEqualGeometry(const char *name, Geometry expected, Geometry actual) {
    if (expected == actual) {
        printf("PASS: %s\n", name);
        return 1;
    }

    printf("FAIL: %s (expected geometry: %d, actual: %d)\n", name, (int)expected, (int)actual);
    return 0;
}

static int assertNotNull(const char *name, const void *ptr) {
    if (ptr != NULL) {
        printf("PASS: %s\n", name);
        return 1;
    }

    printf("FAIL: %s (expected non-NULL, got NULL)\n", name);
    return 0;
}

static int assertNull(const char *name, const void *ptr) {
    if (ptr == NULL) {
        printf("PASS: %s\n", name);
        return 1;
    }

    printf("FAIL: %s (expected NULL, got non-NULL)\n", name);
    return 0;
}

int main(void) {
    int passCount = 0;
    int totalTests = 0;

    /* --- blockToString tests --- */

    static const BlockColor sideColorBlue = BLOCK_COLOR_BLUE;
    Block threeColorBlock = {
        .position = 0,
        .shape = SHAPE_TRIANGLE,
        .faceColor = BLOCK_COLOR_WHITE,
        .sideColor1 = BLOCK_COLOR_GREEN,
        .sideColor2 = &sideColorBlue
    };

    Block twoColorBlock = {
        .position = 1,
        .shape = SHAPE_TRIANGLE,
        .faceColor = BLOCK_COLOR_RED,
        .sideColor1 = BLOCK_COLOR_ORANGE,
        .sideColor2 = NULL
    };

    ++totalTests; passCount += assertEqual("three-color block string", "wgb", blockToString(&threeColorBlock));
    ++totalTests; passCount += assertEqual("two-color block string", "ro", blockToString(&twoColorBlock));

    /* --- cubeFaceFromString: mixed 2-char and 3-char tokens --- */
    /* Input: "wg rob" — "wg" is triangle (face=w, side1=g), "rob" is kite (face=r, side1=o, side2=b) */
    CubeFace *mixedFace = cubeFaceFromString("wg rob");

    ++totalTests; passCount += assertNotNull("mixed face not NULL", mixedFace);
    if (mixedFace != NULL) {
        ++totalTests; passCount += assertEqualInt("mixed face block count", 2, (int)mixedFace->blockCount);

        /* Block 0: triangle, white face, green side1, no side2, position 0 */
        ++totalTests; passCount += assertEqualInt("block 0 position", 0, mixedFace->blocks[0].position);
        ++totalTests; passCount += assertEqualGeometry("block 0 geometry", GEOMETRY_TRIANGLE, mixedFace->blocks[0].shape.geometry);
        ++totalTests; passCount += assertEqualInt("block 0 shape size", 1, mixedFace->blocks[0].shape.size);
        ++totalTests; passCount += assertEqualInt("block 0 faceColor", BLOCK_COLOR_WHITE, (int)mixedFace->blocks[0].faceColor);
        ++totalTests; passCount += assertEqualInt("block 0 sideColor1", BLOCK_COLOR_GREEN, (int)mixedFace->blocks[0].sideColor1);
        ++totalTests; passCount += assertNull("block 0 sideColor2 is NULL", mixedFace->blocks[0].sideColor2);

        /* Block 1: kite, red face, orange side1, blue side2, position 0+1=1 */
        ++totalTests; passCount += assertEqualInt("block 1 position", 1, mixedFace->blocks[1].position);
        ++totalTests; passCount += assertEqualGeometry("block 1 geometry", GEOMETRY_KITE, mixedFace->blocks[1].shape.geometry);
        ++totalTests; passCount += assertEqualInt("block 1 shape size", 2, mixedFace->blocks[1].shape.size);
        ++totalTests; passCount += assertEqualInt("block 1 faceColor", BLOCK_COLOR_RED, (int)mixedFace->blocks[1].faceColor);
        ++totalTests; passCount += assertEqualInt("block 1 sideColor1", BLOCK_COLOR_ORANGE, (int)mixedFace->blocks[1].sideColor1);
        ++totalTests; passCount += assertNotNull("block 1 sideColor2 not NULL", mixedFace->blocks[1].sideColor2);
        if (mixedFace->blocks[1].sideColor2 != NULL) {
            ++totalTests; passCount += assertEqualInt("block 1 sideColor2 value", BLOCK_COLOR_BLUE, (int)*mixedFace->blocks[1].sideColor2);
        }

        free(mixedFace);
    }

    /* --- cubeFaceFromString: leading/trailing/multiple whitespace --- */
    CubeFace *spaceFace = cubeFaceFromString("  wg   ro  ");

    ++totalTests; passCount += assertNotNull("space face not NULL", spaceFace);
    if (spaceFace != NULL) {
        ++totalTests; passCount += assertEqualInt("space face block count", 2, (int)spaceFace->blockCount);
        ++totalTests; passCount += assertEqualInt("space face block 0 position", 0, spaceFace->blocks[0].position);
        ++totalTests; passCount += assertEqualInt("space face block 1 position", 1, spaceFace->blocks[1].position);
        free(spaceFace);
    }

    /* --- cubeFaceFromString: position progression with two kite blocks --- */
    /* "wgb rob" — both kite, positions 0 and 2 */
    CubeFace *kiteFace = cubeFaceFromString("wgb rob");

    ++totalTests; passCount += assertNotNull("kite face not NULL", kiteFace);
    if (kiteFace != NULL) {
        ++totalTests; passCount += assertEqualInt("kite face block 0 position", 0, kiteFace->blocks[0].position);
        ++totalTests; passCount += assertEqualInt("kite face block 1 position", 2, kiteFace->blocks[1].position);
        free(kiteFace);
    }

    /* --- cubeFaceFromString: invalid token length returns NULL --- */
    CubeFace *invalidLenFace = cubeFaceFromString("w");

    ++totalTests; passCount += assertNull("invalid token length yields NULL", invalidLenFace);
    if (invalidLenFace != NULL) { free(invalidLenFace); }

    /* --- cubeFaceFromString: invalid color symbol returns NULL --- */
    CubeFace *invalidColorFace = cubeFaceFromString("xz");

    ++totalTests; passCount += assertNull("invalid color symbol yields NULL", invalidColorFace);
    if (invalidColorFace != NULL) { free(invalidColorFace); }

    /* --- rotateClubFaceClockwise: wraps around 12-slot ring --- */
    CubeFace *rotWrapFace = cubeFaceFromString("wgb rob");

    ++totalTests; passCount += assertNotNull("rotate wrap face not NULL", rotWrapFace);
    if (rotWrapFace != NULL) {
        rotWrapFace->blocks[0].position = 11;
        rotWrapFace->blocks[1].position = 11;

        CubeFace *rotWrapBy1 = rotateClubFaceClockwise(rotWrapFace, 1);
        ++totalTests; passCount += assertNotNull("rotate by 1 returns new face", rotWrapBy1);
        if (rotWrapBy1 != NULL) {
            ++totalTests; passCount += assertEqualInt("rotate 11+1 wraps to 0", 0, rotWrapBy1->blocks[0].position);
            ++totalTests; passCount += assertEqualInt("rotate original remains unchanged", 11, rotWrapFace->blocks[0].position);
            free(rotWrapBy1);
        }

        rotWrapFace->blocks[1].position = 11;
        CubeFace *rotWrapBy2 = rotateClubFaceClockwise(rotWrapFace, 2);
        ++totalTests; passCount += assertNotNull("rotate by 2 returns new face", rotWrapBy2);
        if (rotWrapBy2 != NULL) {
            ++totalTests; passCount += assertEqualInt("rotate 11+2 wraps to 1", 1, rotWrapBy2->blocks[1].position);
            ++totalTests; passCount += assertEqualInt("rotate original remains unchanged 2", 11, rotWrapFace->blocks[1].position);
            free(rotWrapBy2);
        }

        free(rotWrapFace);
    }

    /* --- rotateClubFaceClockwise: preserves shape/color fields --- */
    CubeFace *rotPreserveFace = cubeFaceFromString("wgb ro");

    ++totalTests; passCount += assertNotNull("rotate preserve face not NULL", rotPreserveFace);
    if (rotPreserveFace != NULL) {
        Geometry beforeGeometry = rotPreserveFace->blocks[0].shape.geometry;
        int beforeSize = rotPreserveFace->blocks[0].shape.size;
        BlockColor beforeFaceColor = rotPreserveFace->blocks[0].faceColor;
        BlockColor beforeSideColor1 = rotPreserveFace->blocks[0].sideColor1;
        const BlockColor *beforeSideColor2Ptr = rotPreserveFace->blocks[0].sideColor2;
        BlockColor beforeSideColor2Val = BLOCK_COLOR_WHITE;

        if (beforeSideColor2Ptr != NULL) {
            beforeSideColor2Val = *beforeSideColor2Ptr;
        }

        CubeFace *rotatedPreserveFace = rotateClubFaceClockwise(rotPreserveFace, 5);
        ++totalTests; passCount += assertNotNull("rotate preserve returns new face", rotatedPreserveFace);
        if (rotatedPreserveFace != NULL) {
            ++totalTests; passCount += assertEqualGeometry("rotate preserves geometry", beforeGeometry, rotatedPreserveFace->blocks[0].shape.geometry);
            ++totalTests; passCount += assertEqualInt("rotate preserves shape size", beforeSize, rotatedPreserveFace->blocks[0].shape.size);
            ++totalTests; passCount += assertEqualInt("rotate preserves faceColor", (int)beforeFaceColor, (int)rotatedPreserveFace->blocks[0].faceColor);
            ++totalTests; passCount += assertEqualInt("rotate preserves sideColor1", (int)beforeSideColor1, (int)rotatedPreserveFace->blocks[0].sideColor1);
            ++totalTests; passCount += assertNotNull("rotate preserves sideColor2 pointer", rotatedPreserveFace->blocks[0].sideColor2);
            if (rotatedPreserveFace->blocks[0].sideColor2 != NULL) {
                ++totalTests; passCount += assertEqualInt("rotate preserves sideColor2 value", (int)beforeSideColor2Val, (int)*rotatedPreserveFace->blocks[0].sideColor2);
            }

            ++totalTests; passCount += assertEqualInt("rotate source face unchanged position", 0, rotPreserveFace->blocks[0].position);
            free(rotatedPreserveFace);
        }

        free(rotPreserveFace);
    }

    /* --- rotateClubFaceClockwise: NULL face returns NULL --- */
    CubeFace *nullRotatedFace = rotateClubFaceClockwise(NULL, 3);
    ++totalTests; passCount += assertNull("rotate NULL face returns NULL", nullRotatedFace);

    /* --- cubeFaceToString: position ordering --- */
    CubeFace *orderFace = cubeFaceFromString("wg rob");
    ++totalTests; passCount += assertNotNull("order face not NULL", orderFace);
    if (orderFace != NULL) {
        const char *orderStr = cubeFaceToString(orderFace);
        ++totalTests; passCount += assertNotNull("cubeFaceToString order not NULL", orderStr);
        ++totalTests; passCount += assertEqual("cubeFaceToString position order", "wg rob", orderStr);
        free(orderFace);
    }

    /* --- cubeFaceToString: space separation --- */
    CubeFace *spaceSepFace = cubeFaceFromString("wgb ro");
    ++totalTests; passCount += assertNotNull("space sep face not NULL", spaceSepFace);
    if (spaceSepFace != NULL) {
        const char *spaceSepStr = cubeFaceToString(spaceSepFace);
        ++totalTests; passCount += assertNotNull("cubeFaceToString space sep not NULL", spaceSepStr);
        ++totalTests; passCount += assertEqual("cubeFaceToString space separated", "wgb ro", spaceSepStr);
        free(spaceSepFace);
    }

    /* --- cubeFaceToString: NULL face returns NULL --- */
    const char *nullFaceStr = cubeFaceToString(NULL);
    ++totalTests; passCount += assertNull("cubeFaceToString NULL face returns NULL", nullFaceStr);

    /* --- cubeFaceToString: empty face returns empty string --- */
    CubeFace *emptyFace = cubeFaceFromString("");
    ++totalTests; passCount += assertNotNull("empty face not NULL", emptyFace);
    if (emptyFace != NULL) {
        const char *emptyStr = cubeFaceToString(emptyFace);
        ++totalTests; passCount += assertNotNull("cubeFaceToString empty not NULL", emptyStr);
        ++totalTests; passCount += assertEqual("cubeFaceToString empty string", "", emptyStr);
        free(emptyFace);
    }

    /* --- cubeFromString: successful construction from two face strings --- */
    Cube *cube = cubeFromString("wg rob", "wgb ro");
    ++totalTests; passCount += assertNotNull("cubeFromString returns cube", cube);
    if (cube != NULL) {
        ++totalTests; passCount += assertNotNull("cube top face not NULL", cube->topFace);
        ++totalTests; passCount += assertNotNull("cube bottom face not NULL", cube->bottomFace);
        ++totalTests; passCount += assertNotNull("cube history not NULL", cube->history);
        if (cube->history != NULL) {
            ++totalTests; passCount += assertEqual("cube history initialized empty", "", cube->history);
        }

        freeCubeForTest(cube);
    }

    /* --- cubeFromString: invalid face input returns NULL --- */
    Cube *invalidCube = cubeFromString("wg", "x");
    ++totalTests; passCount += assertNull("cubeFromString invalid input returns NULL", invalidCube);

    /* --- cubeToString: outputs history, top, bottom lines in order --- */
    Cube *cubeForString = cubeFromString("wg rob", "wgb ro");
    ++totalTests; passCount += assertNotNull("cube for toString not NULL", cubeForString);
    if (cubeForString != NULL) {
        char *history = duplicateStringForTest("U");
        ++totalTests; passCount += assertNotNull("history allocation for test", history);
        if (history != NULL) {
            free(cubeForString->history);
            cubeForString->history = history;

            const char *cubeString = cubeToString(cubeForString);
            ++totalTests; passCount += assertNotNull("cubeToString returns non-NULL", cubeString);
            if (cubeString != NULL) {
                ++totalTests; passCount += assertEqual("cubeToString line ordering", "U\nwg rob\nwgb ro", cubeString);
            }
        }

        freeCubeForTest(cubeForString);
    }

    /* --- cubeToString: NULL cube returns NULL --- */
    const char *nullCubeStr = cubeToString(NULL);
    ++totalTests; passCount += assertNull("cubeToString NULL returns NULL", nullCubeStr);

    /* --- rotateCubeTopFaceClockwise: returns rotated copy and keeps source unchanged --- */
    Cube *topRotateSource = cubeFromString("wg rob", "wgb ro");
    ++totalTests; passCount += assertNotNull("top rotate source cube not NULL", topRotateSource);
    if (topRotateSource != NULL) {
        Cube *topRotated = rotateCubeTopFaceClockwise(topRotateSource, 1);
        ++totalTests; passCount += assertNotNull("top rotate returns cube", topRotated);
        if (topRotated != NULL) {
            ++totalTests; passCount += assertEqualInt("top rotated position updated", 1, topRotated->topFace->blocks[0].position);
            ++totalTests; passCount += assertEqualInt("top source cube unchanged", 0, topRotateSource->topFace->blocks[0].position);
            ++totalTests; passCount += assertEqualInt("top rotate keeps bottom unchanged", topRotateSource->bottomFace->blocks[0].position, topRotated->bottomFace->blocks[0].position);
            freeCubeForTest(topRotated);
        }
        freeCubeForTest(topRotateSource);
    }

    /* --- rotateCubeBottomFaceClockwise: returns rotated copy and keeps source unchanged --- */
    Cube *bottomRotateSource = cubeFromString("wg rob", "wgb ro");
    ++totalTests; passCount += assertNotNull("bottom rotate source cube not NULL", bottomRotateSource);
    if (bottomRotateSource != NULL) {
        Cube *bottomRotated = rotateCubeBottomFaceClockwise(bottomRotateSource, 2);
        ++totalTests; passCount += assertNotNull("bottom rotate returns cube", bottomRotated);
        if (bottomRotated != NULL) {
            ++totalTests; passCount += assertEqualInt("bottom rotated position updated", 2, bottomRotated->bottomFace->blocks[0].position);
            ++totalTests; passCount += assertEqualInt("bottom source cube unchanged", 0, bottomRotateSource->bottomFace->blocks[0].position);
            ++totalTests; passCount += assertEqualInt("bottom rotate keeps top unchanged", bottomRotateSource->topFace->blocks[0].position, bottomRotated->topFace->blocks[0].position);
            freeCubeForTest(bottomRotated);
        }
        freeCubeForTest(bottomRotateSource);
    }

    /* --- immutable cube rotation APIs: NULL input returns NULL --- */
    Cube *nullTopRotate = rotateCubeTopFaceClockwise(NULL, 1);
    ++totalTests; passCount += assertNull("rotateCubeTopFaceClockwise NULL returns NULL", nullTopRotate);
    Cube *nullBottomRotate = rotateCubeBottomFaceClockwise(NULL, 1);
    ++totalTests; passCount += assertNull("rotateCubeBottomFaceClockwise NULL returns NULL", nullBottomRotate);

    printf("\n%d/%d tests passed\n", passCount, totalTests);

    return (passCount == totalTests) ? 0 : 1;
}
