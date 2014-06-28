#include "stdafx.h"
#include "BaseShape.h"


BaseShape::BaseShape(void) : shape(4, vector< vector<int> >(4, vector<int>(4))), 
                             x(1), y(8) {
  srand((int)time(0));
  shape_num = rand() % 4;
}

bool BaseShape::Bumb(vector< vector<int> > big_map) {
  for (int m=0, i=x; i!=x+4; ++i, ++m) {
    for (int n=0, j=y; j!=y+4; ++j, ++n) {
      if (shape[shape_num][m][n] + big_map[i][j] == 3) {
        return false;
      }
    }
  }

  return true;
}

void BaseShape::Change(Background *background) {
  for (int i=x; i!=x+4; ++i) {
    for (int j=y; j!=y+4; ++j) {
      if (background->big_map[i][j] == 1) {
        background->big_map[i][j] = 0;
      }
    }
  }

  shape_num = (shape_num + 1) % 4;
  
  if (!Bumb(background->GetBigMap())) {
    shape_num = (shape_num + 3) % 4;
  }
  background->SetBigMap(shape[shape_num], x, y);
}

int BaseShape::GetX() {
  return x;
}
  
int BaseShape::GetY() {
  return y;
}

vector< vector<int> > BaseShape::GetShape() {
  return shape[shape_num];
}

bool BaseShape::Down(Background *background) {
  for (int i=x; i!=x+4; ++i) {
    for (int j=y; j!=y+4; ++j) {
      if (background->big_map[i][j] == 1) {
        background->big_map[i][j] = 0;
      }
    }
  }

  x++;
  
  if (!Bumb(background->GetBigMap())) {
    x--;
    background->SetBigMap(shape[shape_num], x, y);
    
    return false;
  }
  background->SetBigMap(shape[shape_num], x, y);
  return true;
}
  
void BaseShape::Left(Background *background) {
 
  for (int i=x; i!=x+4; ++i) {
    for (int j=y; j!=y+4; ++j) {
      if (background->big_map[i][j] == 1) {
        background->big_map[i][j] = 0;
      }
    }
  }

  y--;
  
  if (!Bumb(background->GetBigMap())) {
    y++;
    
  }
  background->SetBigMap(shape[shape_num], x, y);
}
  
void BaseShape::Right(Background *background) {
  for (int i=x; i!=x+4; ++i) {
    for (int j=y; j!=y+4; ++j) {
      if (background->big_map[i][j] == 1) {
        background->big_map[i][j] = 0;
      }
    }
  }

  y++;
  
  if (!Bumb(background->GetBigMap())) {
    y--;
  }
  background->SetBigMap(shape[shape_num], x, y);
}