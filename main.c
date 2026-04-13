#include <stdio.h>
#include "block-color.h"
#include "shape.h"
#include "block.h"
#include "cube-face.h"
#include "cube.h"

int main(void) {
    Cube *cube = cubeFromString(
        "woo wo woo wo woo wo woo wo",
        "goo go goo go goo go goo go"
    );
    printf("%s\n", cubeToString(operate(cube, "b0")));
    return 0;
}
