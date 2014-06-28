#include "stdafx.h"
#include "T_Shape.h"


T_Shape::T_Shape(void) {
  shape[0][0][0] = shape[0][0][1] = shape[0][0][2] = shape[0][1][1] = 1;
  shape[1][0][1] = shape[1][1][1] = shape[1][2][1] = shape[1][1][0] = 1;
  shape[2][1][0] = shape[2][1][1] = shape[2][1][2] = shape[2][0][1] = 1;
  shape[3][0][1] = shape[3][1][1] = shape[3][2][1] = shape[3][1][2] = 1;
}


