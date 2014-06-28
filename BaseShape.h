#pragma once
#include "Background.h"
#include <time.h>
class BaseShape
{
public:
  BaseShape(void);
  void Change(Background *background);
  bool Bumb(vector< vector<int> > big_map);
  int GetX(void);
  int GetY(void);
  vector< vector<int> > GetShape();
  bool Down(Background *background);
  void Left(Background *background);
  void Right(Background *background);
protected:
  int shape_num;
  vector< vector< vector<int> > > shape;
  int x;
  int y;
};

