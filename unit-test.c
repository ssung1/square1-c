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

static const Block *findBlockByPosition(const CubeFace *face, int position) {
    size_t i;

    if (face == NULL) {
        return NULL;
    }

    for (i = 0; i < face->blockCount; ++i) {
        if (face->blocks[i].position == position) {
            return &face->blocks[i];
        }
    }

    return NULL;
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

    /* --- isFlippable: both faces flippable (12 triangles each) --- */
    Cube *flippableCube = cubeFromString(
        "wg wg wg wg wg wg wg wg wg wg wg wg",
        "wg wg wg wg wg wg wg wg wg wg wg wg");
    ++totalTests; passCount += assertNotNull("isFlippable cube not NULL", flippableCube);
    if (flippableCube != NULL) {
        ++totalTests; passCount += assertEqualInt("isFlippable both faces clean returns 1", 1, isFlippable(flippableCube));
        freeCubeForTest(flippableCube);
    }

    /* --- isFlippable: top face has kite at position 11 (interior at 0) --- */
    Cube *kitAt11TopCube = cubeFromString(
        "wg wg wg wg wg wg wg wg wg wg wg wrb",
        "wg wg wg wg wg wg wg wg wg wg wg wg");
    ++totalTests; passCount += assertNotNull("isFlippable kite-at-11 top cube not NULL", kitAt11TopCube);
    if (kitAt11TopCube != NULL) {
        ++totalTests; passCount += assertEqualInt("isFlippable top kite at 11 spanning 0 returns 0", 0, isFlippable(kitAt11TopCube));
        freeCubeForTest(kitAt11TopCube);
    }

    /* --- isFlippable: top face has kite at position 5 (interior at 6) --- */
    Cube *kiteAt5TopCube = cubeFromString(
        "wg wg wg wg wg wrb",
        "wg wg wg wg wg wg wg wg wg wg wg wg");
    ++totalTests; passCount += assertNotNull("isFlippable kite-at-5 top cube not NULL", kiteAt5TopCube);
    if (kiteAt5TopCube != NULL) {
        ++totalTests; passCount += assertEqualInt("isFlippable top kite at 5 spanning 6 returns 0", 0, isFlippable(kiteAt5TopCube));
        freeCubeForTest(kiteAt5TopCube);
    }

    /* --- isFlippable: top face flippable, bottom face has kite at position 11 --- */
    Cube *bottomNotFlippable = cubeFromString(
        "wg wg wg wg wg wg wg wg wg wg wg wg",
        "wg wg wg wg wg wg wg wg wg wg wg wrb");
    ++totalTests; passCount += assertNotNull("isFlippable bottom-not-flippable cube not NULL", bottomNotFlippable);
    if (bottomNotFlippable != NULL) {
        ++totalTests; passCount += assertEqualInt("isFlippable bottom kite at 11 returns 0", 0, isFlippable(bottomNotFlippable));
        freeCubeForTest(bottomNotFlippable);
    }

    /* --- isFlippable: NULL cube returns 0 --- */
    ++totalTests; passCount += assertEqualInt("isFlippable NULL cube returns 0", 0, isFlippable(NULL));

    /* --- cubeFaceToString: blocks starting at position 0 (no prefix) --- */
    CubeFace *faceAt0 = cubeFaceFromString("wg wg wg wg wg wg wg wg wg wg wg wg");
    ++totalTests; passCount += assertNotNull("cubeFaceToString face at 0 not NULL", faceAt0);
    if (faceAt0 != NULL) {
        const char *str0 = cubeFaceToString(faceAt0);
        ++totalTests; passCount += assertNotNull("cubeFaceToString at 0 returns non-NULL", str0);
        if (str0 != NULL) {
            ++totalTests; passCount += assertEqual("cubeFaceToString at 0 no prefix", "wg wg wg wg wg wg wg wg wg wg wg wg", str0);
        }
        free(faceAt0);
    }

    /* --- cubeFaceToString: blocks starting at position 1 (with prefix, via rotation) --- */
    CubeFace *faceBeforeRotate = cubeFaceFromString("wrb wrb");
    ++totalTests; passCount += assertNotNull("cubeFaceToString face before rotate not NULL", faceBeforeRotate);
    if (faceBeforeRotate != NULL) {
        CubeFace *faceAt1 = rotateClubFaceClockwise(faceBeforeRotate, 11);
        ++totalTests; passCount += assertNotNull("cubeFaceToString face at 1 (rotated) not NULL", faceAt1);
        if (faceAt1 != NULL) {
            const char *str1 = cubeFaceToString(faceAt1);
            ++totalTests; passCount += assertNotNull("cubeFaceToString at 1 returns non-NULL", str1);
            if (str1 != NULL) {
                ++totalTests; passCount += assertEqualInt("cubeFaceToString at 1 has prefix", 1, (str1[0] == '*' ? 1 : 0));
            }
            free(faceAt1);
        }
        free(faceBeforeRotate);
    }

    /* --- cubeFaceToString: blocks starting at position 2 (no prefix) --- */
    CubeFace *faceAt2 = cubeFaceFromString("wrb wrb");
    ++totalTests; passCount += assertNotNull("cubeFaceToString face at 2 not NULL", faceAt2);
    if (faceAt2 != NULL) {
        const char *str2 = cubeFaceToString(faceAt2);
        ++totalTests; passCount += assertNotNull("cubeFaceToString at 2 returns non-NULL", str2);
        if (str2 != NULL) {
            ++totalTests; passCount += assertEqualInt("cubeFaceToString at 2 no prefix", 0, (str2[0] == '*' ? 1 : 0));
        }
        free(faceAt2);
    }

    /* --- cubeFaceToString: NULL input returns NULL (unchanged) --- */
    const char *nullStr = cubeFaceToString(NULL);
    ++totalTests; passCount += assertNull("cubeFaceToString NULL returns NULL", nullStr);

    /* --- flip: right-half triangle at top position 0 moves to bottom position 5 --- */
    Cube *flipTriangleSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "bo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("flip triangle source cube not NULL", flipTriangleSource);
    if (flipTriangleSource != NULL) {
        Cube *flipTriangleResult = flip(flipTriangleSource);
        ++totalTests; passCount += assertNotNull("flip triangle result cube not NULL", flipTriangleResult);
        if (flipTriangleResult != NULL) {
            const Block *movedTriangle = findBlockByPosition(flipTriangleResult->bottomFace, 5);
            ++totalTests; passCount += assertNotNull("flip triangle moved block found at bottom pos 5", movedTriangle);
            if (movedTriangle != NULL) {
                ++totalTests; passCount += assertEqualInt("flip triangle moved block face color preserved", BLOCK_COLOR_RED, movedTriangle->faceColor);
                ++totalTests; passCount += assertEqualGeometry("flip triangle moved block remains triangle", GEOMETRY_TRIANGLE, movedTriangle->shape.geometry);
            }
            freeCubeForTest(flipTriangleResult);
        }
        freeCubeForTest(flipTriangleSource);
    }

    /* --- flip: right-half kite at top position 0 moves to bottom position 4 --- */
    Cube *flipKiteSource = cubeFromString(
        "wgb wg wg wg wg wg wg wg wg wg wg",
        "bo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("flip kite source cube not NULL", flipKiteSource);
    if (flipKiteSource != NULL) {
        Cube *flipKiteResult = flip(flipKiteSource);
        ++totalTests; passCount += assertNotNull("flip kite result cube not NULL", flipKiteResult);
        if (flipKiteResult != NULL) {
            const Block *movedKite = findBlockByPosition(flipKiteResult->bottomFace, 4);
            ++totalTests; passCount += assertNotNull("flip kite moved block found at bottom pos 4", movedKite);
            if (movedKite != NULL) {
                ++totalTests; passCount += assertEqualGeometry("flip kite moved block remains kite", GEOMETRY_KITE, movedKite->shape.geometry);
                ++totalTests; passCount += assertEqualInt("flip kite moved block sideColor2 preserved", BLOCK_COLOR_BLUE, (movedKite->sideColor2 != NULL) ? *movedKite->sideColor2 : -1);
            }
            freeCubeForTest(flipKiteResult);
        }
        freeCubeForTest(flipKiteSource);
    }

    /* --- flip: right-half blocks from bottom move to top with reflected position --- */
    Cube *bottomToTopSource = cubeFromString(
        "wg wg wg wg wg wg wg wg wg wg wg wg",
        "yo wg wg wg wg wg wg wg wg wg wg wg");
    ++totalTests; passCount += assertNotNull("flip bottom-to-top source cube not NULL", bottomToTopSource);
    if (bottomToTopSource != NULL) {
        Cube *bottomToTopResult = flip(bottomToTopSource);
        ++totalTests; passCount += assertNotNull("flip bottom-to-top result cube not NULL", bottomToTopResult);
        if (bottomToTopResult != NULL) {
            const Block *movedFromBottom = findBlockByPosition(bottomToTopResult->topFace, 5);
            ++totalTests; passCount += assertNotNull("flip block from bottom found at top pos 5", movedFromBottom);
            if (movedFromBottom != NULL) {
                ++totalTests; passCount += assertEqualInt("flip block from bottom face color preserved", BLOCK_COLOR_YELLOW, movedFromBottom->faceColor);
            }
            freeCubeForTest(bottomToTopResult);
        }
        freeCubeForTest(bottomToTopSource);
    }

    /* --- flip: left-half blocks remain on original face unchanged --- */
    Cube *leftHalfSource = cubeFromString(
        "wg wg wg wg wg wg rg wg wg wg wg wg",
        "bo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("flip left-half source cube not NULL", leftHalfSource);
    if (leftHalfSource != NULL) {
        Cube *leftHalfResult = flip(leftHalfSource);
        ++totalTests; passCount += assertNotNull("flip left-half result cube not NULL", leftHalfResult);
        if (leftHalfResult != NULL) {
            const Block *leftBlock = findBlockByPosition(leftHalfResult->topFace, 6);
            ++totalTests; passCount += assertNotNull("flip left-half block still at top pos 6", leftBlock);
            if (leftBlock != NULL) {
                ++totalTests; passCount += assertEqualInt("flip left-half block color unchanged", BLOCK_COLOR_RED, leftBlock->faceColor);
            }
            freeCubeForTest(leftHalfResult);
        }
        freeCubeForTest(leftHalfSource);
    }

    /* --- flip: source cube remains unchanged --- */
    Cube *immutSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "bo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("flip immutability source cube not NULL", immutSource);
    if (immutSource != NULL) {
        int sourceTopPos = immutSource->topFace->blocks[0].position;
        int sourceTopColor = immutSource->topFace->blocks[0].faceColor;
        Cube *immutResult = flip(immutSource);
        ++totalTests; passCount += assertNotNull("flip immutability result cube not NULL", immutResult);
        if (immutResult != NULL) {
            ++totalTests; passCount += assertEqualInt("flip immutability source top pos unchanged", sourceTopPos, immutSource->topFace->blocks[0].position);
            ++totalTests; passCount += assertEqualInt("flip immutability source top color unchanged", sourceTopColor, immutSource->topFace->blocks[0].faceColor);
            freeCubeForTest(immutResult);
        }
        freeCubeForTest(immutSource);
    }

    /* --- flip: NULL input returns NULL --- */
    Cube *nullFlip = flip(NULL);
    ++totalTests; passCount += assertNull("flip NULL returns NULL", nullFlip);

    /* --- flip: non-flippable cube returns NULL --- */
    Cube *nonFlippableFlipSource = cubeFromString(
        "wg wg wg wg wg wgb",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("flip non-flippable source not NULL", nonFlippableFlipSource);
    if (nonFlippableFlipSource != NULL) {
        Cube *nonFlippableFlipResult = flip(nonFlippableFlipSource);
        ++totalTests; passCount += assertNull("flip non-flippable returns NULL", nonFlippableFlipResult);
        freeCubeForTest(nonFlippableFlipSource);
    }

    /* --- operate: 1-char token rotates top only --- */
    Cube *operateTopSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "bo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate top-only source not NULL", operateTopSource);
    if (operateTopSource != NULL) {
        Cube *operateTopResult = operate(operateTopSource, "1");
        ++totalTests; passCount += assertNotNull("operate top-only result not NULL", operateTopResult);
        if (operateTopResult != NULL) {
            const Block *rotatedTop = findBlockByPosition(operateTopResult->topFace, 1);
            ++totalTests; passCount += assertNotNull("operate top-only moved top block to pos 1", rotatedTop);
            if (rotatedTop != NULL) {
                ++totalTests; passCount += assertEqualInt("operate top-only preserves top block color", BLOCK_COLOR_RED, rotatedTop->faceColor);
            }
            ++totalTests; passCount += assertEqualInt("operate top-only bottom unchanged", 0, operateTopResult->bottomFace->blocks[0].position);
            freeCubeForTest(operateTopResult);
        }
        freeCubeForTest(operateTopSource);
    }

    /* --- operate: 2-char token rotates top and bottom only --- */
    Cube *operateTwoSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate two-char source not NULL", operateTwoSource);
    if (operateTwoSource != NULL) {
        Cube *operateTwoResult = operate(operateTwoSource, "12");
        ++totalTests; passCount += assertNotNull("operate two-char result not NULL", operateTwoResult);
        if (operateTwoResult != NULL) {
            const Block *topAt1 = findBlockByPosition(operateTwoResult->topFace, 1);
            const Block *bottomAt2 = findBlockByPosition(operateTwoResult->bottomFace, 2);
            ++totalTests; passCount += assertNotNull("operate two-char top rotated to pos 1", topAt1);
            ++totalTests; passCount += assertNotNull("operate two-char bottom rotated to pos 2", bottomAt2);
            if (topAt1 != NULL) {
                ++totalTests; passCount += assertEqualInt("operate two-char top color preserved", BLOCK_COLOR_RED, topAt1->faceColor);
            }
            if (bottomAt2 != NULL) {
                ++totalTests; passCount += assertEqualInt("operate two-char bottom color preserved", BLOCK_COLOR_YELLOW, bottomAt2->faceColor);
            }
            freeCubeForTest(operateTwoResult);
        }
        freeCubeForTest(operateTwoSource);
    }

    /* --- operate: 3-char token applies flip when third char is space --- */
    Cube *operateFlipSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate flip source not NULL", operateFlipSource);
    if (operateFlipSource != NULL) {
        Cube *operateFlipResult = operate(operateFlipSource, "00 ");
        ++totalTests; passCount += assertNotNull("operate flip result not NULL", operateFlipResult);
        if (operateFlipResult != NULL) {
            const Block *topFromBottom = findBlockByPosition(operateFlipResult->topFace, 5);
            const Block *bottomFromTop = findBlockByPosition(operateFlipResult->bottomFace, 5);
            ++totalTests; passCount += assertNotNull("operate flip moved bottom block to top pos 5", topFromBottom);
            ++totalTests; passCount += assertNotNull("operate flip moved top block to bottom pos 5", bottomFromTop);
            if (topFromBottom != NULL) {
                ++totalTests; passCount += assertEqualInt("operate flip top received bottom color", BLOCK_COLOR_YELLOW, topFromBottom->faceColor);
            }
            if (bottomFromTop != NULL) {
                ++totalTests; passCount += assertEqualInt("operate flip bottom received top color", BLOCK_COLOR_RED, bottomFromTop->faceColor);
            }
            freeCubeForTest(operateFlipResult);
        }
        freeCubeForTest(operateFlipSource);
    }

    /* --- operate: non-flippable flip token is a no-op and does not fail --- */
    Cube *operateNonFlippableSource = cubeFromString(
        "wg wg wg wg wg wgb",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate non-flippable source not NULL", operateNonFlippableSource);
    if (operateNonFlippableSource != NULL) {
        Cube *operateNonFlippableResult = operate(operateNonFlippableSource, "00 ");
        ++totalTests; passCount += assertNotNull("operate non-flippable flip token does not fail", operateNonFlippableResult);
        if (operateNonFlippableResult != NULL) {
            const char *resultTop = cubeFaceToString(operateNonFlippableResult->topFace);
            const char *resultBottom = cubeFaceToString(operateNonFlippableResult->bottomFace);
            const char *sourceTop = cubeFaceToString(operateNonFlippableSource->topFace);
            const char *sourceBottom = cubeFaceToString(operateNonFlippableSource->bottomFace);

            ++totalTests; passCount += assertNotNull("operate non-flippable result top string not NULL", resultTop);
            ++totalTests; passCount += assertNotNull("operate non-flippable result bottom string not NULL", resultBottom);
            ++totalTests; passCount += assertNotNull("operate non-flippable source top string not NULL", sourceTop);
            ++totalTests; passCount += assertNotNull("operate non-flippable source bottom string not NULL", sourceBottom);

            if (resultTop != NULL && sourceTop != NULL) {
                ++totalTests; passCount += assertEqual("operate non-flippable top unchanged", sourceTop, resultTop);
            }
            if (resultBottom != NULL && sourceBottom != NULL) {
                ++totalTests; passCount += assertEqual("operate non-flippable bottom unchanged", sourceBottom, resultBottom);
            }

            freeCubeForTest(operateNonFlippableResult);
        }
        freeCubeForTest(operateNonFlippableSource);
    }

    /* --- operate: invalid token characters return NULL --- */
    Cube *operateInvalidSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate invalid source not NULL", operateInvalidSource);
    if (operateInvalidSource != NULL) {
        Cube *invalidTop = operate(operateInvalidSource, "z");
        Cube *invalidBottom = operate(operateInvalidSource, "1z");
        Cube *invalidThird = operate(operateInvalidSource, "10x");
        ++totalTests; passCount += assertNull("operate invalid top char returns NULL", invalidTop);
        ++totalTests; passCount += assertNull("operate invalid bottom char returns NULL", invalidBottom);
        ++totalTests; passCount += assertNull("operate invalid third char returns NULL", invalidThird);
        freeCubeForTest(operateInvalidSource);
    }

    /* --- operate: source cube unchanged after operate --- */
    Cube *operateImmutSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate immutability source not NULL", operateImmutSource);
    if (operateImmutSource != NULL) {
        char *sourceHistory = duplicateStringForTest("U");
        ++totalTests; passCount += assertNotNull("operate immutability history alloc", sourceHistory);
        if (sourceHistory != NULL) {
            int sourceTopPos = operateImmutSource->topFace->blocks[0].position;
            int sourceBottomPos = operateImmutSource->bottomFace->blocks[0].position;
            free(operateImmutSource->history);
            operateImmutSource->history = sourceHistory;

            Cube *operateImmutResult = operate(operateImmutSource, "1b ");
            ++totalTests; passCount += assertNotNull("operate immutability result not NULL", operateImmutResult);
            if (operateImmutResult != NULL) {
                ++totalTests; passCount += assertEqualInt("operate source top unchanged", sourceTopPos, operateImmutSource->topFace->blocks[0].position);
                ++totalTests; passCount += assertEqualInt("operate source bottom unchanged", sourceBottomPos, operateImmutSource->bottomFace->blocks[0].position);
                ++totalTests; passCount += assertEqual("operate source history unchanged", "U", operateImmutSource->history);
                freeCubeForTest(operateImmutResult);
            }
        }
        freeCubeForTest(operateImmutSource);
    }

    /* --- operate: history appends operation string --- */
    Cube *operateHistorySource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate history source not NULL", operateHistorySource);
    if (operateHistorySource != NULL) {
        char *history = duplicateStringForTest("U");
        ++totalTests; passCount += assertNotNull("operate history alloc", history);
        if (history != NULL) {
            free(operateHistorySource->history);
            operateHistorySource->history = history;

            Cube *operateHistoryResult = operate(operateHistorySource, "1a ");
            ++totalTests; passCount += assertNotNull("operate history result not NULL", operateHistoryResult);
            if (operateHistoryResult != NULL) {
                ++totalTests; passCount += assertEqual("operate history appended", "U1a ", operateHistoryResult->history);
                freeCubeForTest(operateHistoryResult);
            }
        }
        freeCubeForTest(operateHistorySource);
    }

    /* --- operate: NULL cube or NULL ops returns NULL --- */
    Cube *operateNullSource = cubeFromString(
        "rg wg wg wg wg wg wg wg wg wg wg wg",
        "yo bo bo bo bo bo bo bo bo bo bo bo");
    ++totalTests; passCount += assertNotNull("operate NULL-arg source not NULL", operateNullSource);
    if (operateNullSource != NULL) {
        Cube *nullCubeResult = operate(NULL, "1");
        Cube *nullOpsResult = operate(operateNullSource, NULL);
        ++totalTests; passCount += assertNull("operate NULL cube returns NULL", nullCubeResult);
        ++totalTests; passCount += assertNull("operate NULL ops returns NULL", nullOpsResult);
        freeCubeForTest(operateNullSource);
    }

    printf("\n%d/%d tests passed\n", passCount, totalTests);

    return (passCount == totalTests) ? 0 : 1;
}
