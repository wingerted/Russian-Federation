#include "stdafx.h"
#include "Z_Shape.h"


Z_Shape::Z_Shape(void) {
  shape[0][0][1] = shape[0][1][0] = shape[0][1][1] = shape[0][2][0] = 1;
  shape[1][0][0] = shape[1][0][1] = shape[1][1][1] = shape[1][1][2] = 1;
  shape[2][0][1] = shape[2][1][0] = shape[2][1][1] = shape[2][2][0] = 1;
  shape[3][0][0] = shape[3][0][1] = shape[3][1][1] = shape[3][1][2] = 1;
}


