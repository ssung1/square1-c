#ifndef SHAPE_H
#define SHAPE_H

typedef enum {
    GEOMETRY_TRIANGLE = 0,
    GEOMETRY_KITE = 1
} Geometry;

typedef struct {
    Geometry geometry;
    int size;
} Shape;

extern const Shape SHAPE_TRIANGLE;
extern const Shape SHAPE_KITE;

#endif /* SHAPE_H */
