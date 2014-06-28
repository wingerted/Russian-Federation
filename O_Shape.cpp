#include "stdafx.h"
#include "O_Shape.h"


O_Shape::O_Shape(void) {
  for (int i=0; i!=4; ++i) {
    shape[i][0][0] = 1;
    shape[i][0][1] = 1;
    shape[i][1][0] = 1;
    shape[i][1][1] = 1;
  }
}

