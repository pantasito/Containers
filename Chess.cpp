#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
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

//  int get_x() { return x; }
//  int get_y() { return y; }

//public:
//  void set_x(int _x) { x = _x; }
//  void set_y(int _y) { y = _y; }

  bool operator == (Position& rhs) {
    if (x == rhs.x && y == rhs.y) return true;
    else return false;
  }
};


class ChessParty;

class Figure
{
public:
    friend ChessParty;
    Position pos;
    bool is_white;
    Figure(Position _pos, bool _is_white) :pos(_pos), is_white(_is_white) {}
    virtual void print() = 0;
    virtual vector<Position> get_avail_turns(ChessParty& party) = 0;
};

/*
class Rook : public Figure
{
public:
  Pawn(Position _pos, bool _is_white) : Figure(_pos, _is_white) {
    pos = _pos;
    is_white = _is_white;
  }

  void print() { cout << "p "; }

  vector<Position> get_avail_turns(ChessParty& party) {
    vector<Position> p;
    if (is_white == true && pos.y < 7) {
      if (party.field[pos.x][pos.y + 1] == NULL) p.push_back(Position(pos.x, pos.y + 1));
      if (pos.x != 0 && party.field[pos.x - 1][pos.y + 1] != NULL) p.push_back(Position(pos.x - 1, pos.y + 1));
      if (pos.x != 7 && party.field[pos.x + 1][pos.y + 1] != NULL) p.push_back(Position(pos.x + 1, pos.y + 1));
    }
    if (is_white == false && pos.y > 0) {
      if (party.field[pos.x][pos.y - 1] == NULL) p.push_back(Position(pos.x, pos.y - 1));
      if (pos.x != 0 && party.field[pos.x - 1][pos.y - 1] != NULL) p.push_back(Position(pos.x - 1, pos.y - 1));
      if (pos.x != 7 && party.field[pos.x + 1][pos.y - 1] != NULL) p.push_back(Position(pos.x + 1, pos.y - 1));
    }
    return p;
  }
};
*/

class ChessParty
{
  friend Figure;
  bool cur_white;

  vector<Figure*> white_figures;
  vector<Figure*> black_figures;
  
  Figure* field[8][8];

  Figure* get_figure() {
    int size = (cur_white == 1) ? white_figures.size() : black_figures.size();
    if (size == 0) return NULL;
    return (cur_white == 1) ? white_figures[rand() % size] : black_figures[rand() % size];
  }

  void check_and_delete_fig(bool cur_white, Position this_turn) {
    if (field[this_turn.x][this_turn.y] == NULL) return;
    if (field[this_turn.x][this_turn.y]->is_white == cur_white) assert(0);

    vector<Figure*>& enemy_figures = cur_white ? black_figures : white_figures;
    for (vector<Figure*> ::iterator it = enemy_figures.begin(); it != enemy_figures.end(); it++) {
      if ((*it)->pos == this_turn) {
        enemy_figures.erase(it);
        cout << enemy_figures.size() << endl;
        field[this_turn.x][this_turn.y] = NULL;
      }
    }
  }

  class Pawn : public Figure
  {
  public:
    Pawn(Position _pos, bool _is_white) : Figure(_pos, _is_white) {
      pos = _pos;
      is_white = _is_white;
    }

    void print() { cout << "p "; }

    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;
      if (is_white == true && pos.y < 7) {
        if (party.field[pos.x][pos.y + 1] == NULL) p.push_back(Position(pos.x, pos.y + 1));
        if (pos.x != 0 && party.field[pos.x - 1][pos.y + 1] != NULL && party.field[pos.x][pos.y]->is_white != party.field[pos.x - 1][pos.y + 1]->is_white) p.push_back(Position(pos.x - 1, pos.y + 1));
        if (pos.x != 7 && party.field[pos.x + 1][pos.y + 1] != NULL && party.field[pos.x][pos.y]->is_white != party.field[pos.x + 1][pos.y + 1]->is_white) p.push_back(Position(pos.x + 1, pos.y + 1));
      }
      if (is_white == false && pos.y > 0) {
        if (party.field[pos.x][pos.y - 1] == NULL) p.push_back(Position(pos.x, pos.y - 1));
        if (pos.x != 0 && party.field[pos.x - 1][pos.y - 1] != NULL && party.field[pos.x][pos.y]->is_white != party.field[pos.x - 1][pos.y - 1]->is_white) p.push_back(Position(pos.x - 1, pos.y - 1));
        if (pos.x != 7 && party.field[pos.x + 1][pos.y - 1] != NULL && party.field[pos.x][pos.y]->is_white != party.field[pos.x + 1][pos.y - 1]->is_white) p.push_back(Position(pos.x + 1, pos.y - 1));
      }
      return p;
    }
  };


  public:
    ChessParty() {
      {
        cur_white = true;

        for (int i = 0; i < 8; i++)
          for (int j = 0; j < 8; j++)
          {
            field[i][j] = NULL;

            if (j == 1) {
              field[i][j] = new Pawn(Position(i, j), true);
              white_figures.push_back(field[i][j]);
            }
            if (j == 6) {
              field[i][j] = new Pawn(Position(i, j), false);
              black_figures.push_back(field[i][j]);
            }
         }
      }
    }
    void turn() {
   
    vector<Position> avail_pos;
    srand(time(0));
    Figure* figure;
    do {
      figure = get_figure();
      avail_pos = figure->get_avail_turns(*this);
    } while (avail_pos.size() == 0);

    Position this_turn = avail_pos[rand() % avail_pos.size()];

    check_and_delete_fig(cur_white, this_turn);
    field[figure->pos.x][figure->pos.y] = NULL;

    figure->pos.x = this_turn.x;
    figure->pos.y = this_turn.y;
    field[this_turn.x][this_turn.y] = figure;
    cur_white = 1 - cur_white;
  }

  void print() {
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (field[i][j] == NULL) cout << ". ";
        else field[i][j]->print();
      }
      cout << endl;
    }
    cout << endl;
  }
};

int main()
{
  ChessParty party;

  for (int i = 0; i < 300; i++)
  {
    party.print();
    party.turn();
  }

  system("pause");
}
