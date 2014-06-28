#include "stdafx.h"
#include "I_Shape.h"


I_Shape::I_Shape(void)
{
  for (int i=0; i!=4; ++i) {
    shape[0][0][i] = 1;
    shape[1][i][0] = 1;
    shape[2][0][i] = 1;
    shape[3][i][0] = 1;
  }
}