#pragma once
#include <vector>

using namespace std;

class Background
{
    
public:
  friend class BaseShape;

  Background(HDC in_hdc);
  void SetSmallMap(vector< vector<int> > in_map);
  void DrawSmallMap();
  void DrawPiece(int x, int y);
  vector< vector<int> > GetBigMap();
  int GetX();
  int GetY();
  void SetBigMap(vector< vector<int> > in_map, int x, int y);
  void FillBigMap(vector< vector<int> > in_map, int x, int y);
  void DrawBigMap();
  void ClearLine();

  int score;                                 
  int grade;
private:
  vector<int> line;
  vector< vector<int> > big_map;
  vector< vector<int> > small_map;
  int x;
  int y;
  HDC hdc;
};

