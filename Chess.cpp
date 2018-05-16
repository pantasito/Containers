#include <iostream>
#include <vector>
using namespace std;

/*
class A
{
  public:
    A(int a) {}
};

vector<A*> a; // 0
 // 1
int ind;


void f()
{
  vector<A*>& m = (ind == 0) ? a : b;
  vector<A*>& y = (ind == 1) ? a : b;
}


int main()
{
  A* arr[8][8];

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      if (i == j) {
        arr[i][j] = new A(i);
      }
      else {
        arr[i][j] = NULL;
      }
    }
  }

  
}
*/

struct Position
{
  int x;
  int y;
  Position(int x, int y):x(x),y(y) {}
};

class ChessParty;

class Figure
{       
    Position pos;
    bool is_white;
  public:
    Figure(Position pos, bool is_white) :pos(pos), is_white(is_white) {}
    virtual void print() = 0;
    virtual vector<Position> get_avail_turns(ChessParty& party) = 0;
};

class ChessParty
{ 
  friend Figure;
  bool cur_white;

  vector<Figure*> white_figures;
  vector<Figure*> black_figures;
  
  Figure* field[8][8];

  public:
    ChessParty() {}
    void turn() {
      

      //vector<Position> avail_pos = p->get_avail_turns(*this);
    }
    void print() {}
};
