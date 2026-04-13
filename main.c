#include <stdio.h>
#include "block-color.h"
#include "shape.h"
#include "block.h"
#include "cube-face.h"

int main(void) {
    CubeFace *face = cubeFaceFromString("woo go goo go goo go goo go");
    CubeFace *newFace = rotateCubeFaceCounterclockwise(face, 1);

    printf("%s\n", cubeFaceToString(newFace));
    return 0;
}
