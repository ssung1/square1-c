#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "cube-face.h"
#include "shape.h"

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

    printf("\n%d/%d tests passed\n", passCount, totalTests);

    return (passCount == totalTests) ? 0 : 1;
}
