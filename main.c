#include <stdio.h>
#include "block-color.h"
#include "shape.h"
#include "block.h"
#include "cube-face.h"
#include "cube.h"

int main(void) {
    Cube *cube = cubeFromString(
        "woo go goo go goo go goo go",
        "goo wo woo wo woo wo woo wo"
    );
    printf("%s\n", cubeToString(rotateCubeTopFaceClockwise(cube, 2)));
    return 0;
}
