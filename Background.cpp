#include "stdafx.h"
#include "Background.h"


Background::Background(HDC in_hdc) : hdc(in_hdc), score(0), grade(0), x(5), y(1), 
    big_map(24, vector<int>(18)), small_map(4, vector<int>(4)), line(18){
  
  for (int i=0; i!=18; ++i) {
    big_map[0][i] = 2;
    big_map[21][i] = 2;
    big_map[22][i] = 2;
    big_map[23][i] = 2;
    line[i] = 2;
  }
  
  for (int i=0; i!=24; ++i) {
    big_map[i][0] = 2;
    big_map[i][1] = 2;
    big_map[i][2] = 2;
    big_map[i][15] = 2;
    big_map[i][16] = 2;
    big_map[i][17] = 2;
  }

  SelectObject (hdc, GetStockObject (BLACK_BRUSH));
        
  Rectangle (hdc, 20, 80, 260, 480) ;

  Rectangle (hdc, 290, 80, 370, 160) ;
}

void Background::DrawPiece(int x, int y) {
  SelectObject (hdc, GetStockObject(BLACK_PEN));		//Ñ¡ÔñºÚÉ«»­±Ê
  SelectObject (hdc, GetStockObject(WHITE_BRUSH));	    //Ñ¡Ôñ°×É«±ÊË¢
  Rectangle(hdc, x, y, x+20, y+20);
}

void Background::DrawSmallMap() {
  SelectObject (hdc, GetStockObject(BLACK_BRUSH));
  Rectangle (hdc, 290, 80, 370, 160);

  for (int i=0; i!=4; ++i) {
    for (int j=0; j!=4; ++j) {
      if (small_map[i][j] == 1) {
        DrawPiece(290+j*20, 80+i*20);
      }
    }
  }
}

void Background::SetSmallMap(vector< vector<int> > in_map) {
  small_map = in_map;
}

void Background::SetBigMap(vector< vector<int> > in_map, int x, int y) {
  for (int m=0, i=x; i!=x+4; ++i, ++m) {
    for (int n=0, j=y; j!=y+4; ++j, ++n) {
      big_map[i][j] = in_map[m][n] + big_map[i][j];
    }
  }
}

void Background::FillBigMap(vector< vector<int> > in_map, int x, int y) {
  for (int m=0, i=x; i!=x+4; ++i, ++m) {
    for (int n=0, j=y; j!=y+4; ++j, ++n) {
      if (in_map[m][n] == 1) {
        big_map[i][j] = 2;
      }
    }
  }
}

void Background::DrawBigMap() {
  SelectObject (hdc, GetStockObject (BLACK_BRUSH));
        
  Rectangle (hdc, 20, 80, 260, 480) ;
  
  for (int i=1; i!=21; ++i) {
    for (int j=3; j!=15; ++j) {
      if (big_map[i][j] == 1 || big_map[i][j] == 2) {
        DrawPiece(20+(j-3)*20, 80+(i-1)*20);
      }
    }
  }
}

vector< vector<int> > Background::GetBigMap() {
  return big_map;
}

int Background::GetX() {
  return x;
}
  
int Background::GetY() {
  return y;
}

void Background::ClearLine() {
  for (int i=20; i!=0; --i) {
    if (big_map[i] == line) {
      for (int j=i-1; j!=0; --j) {
        big_map[j+1] = big_map[j];
      }

      score = score * 10;
    }
  }

  score += 1;
}
