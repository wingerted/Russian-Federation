#include "stdafx.h"
#include "L_Shape.h"


L_Shape::L_Shape(void) {
  shape[0][0][0] = shape[0][1][0] = shape[0][2][0] = shape[0][2][1] = 1;
  shape[1][0][0] = shape[1][0][1] = shape[1][0][2] = shape[1][1][0] = 1;
  shape[2][0][0] = shape[2][0][1] = shape[2][1][1] = shape[2][2][1] = 1;
  shape[3][0][2] = shape[3][1][2] = shape[3][1][1] = shape[3][1][0] = 1;
}

