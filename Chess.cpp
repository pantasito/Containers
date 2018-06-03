#include <iostream>
#include <vector>
#include <ctime>
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
  int get_x() { return x; }
  int get_y() { return y; }

public:
  void set_x(int _x) { x = _x; }
  void set_y(int _y) { y = _y; }
  bool operator == (Position& lhs, Position& rhs) {
    if (lhs.get_x() == rhs.get_x() && lhs.get_y() = rhs.get_x()) return true;
    else return false;
  }
};

class ChessParty;

class Figure
{   
    friend ChessParty;
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
  bool cur_white = true;

  vector<Figure*> white_figures;
  vector<Figure*> black_figures;
  
  Figure* field[8][8];

  Figure* get_fig() {
    int size = (cur_white == 1) ? white_figures.size() : black_figures.size();
    if (size == 0) return;
    Figure * p = (cur_white == 1) ? white_figures[rand() % size] : black_figures[rand() % size];
    return p;
  }

  void check_and_delete_fig(bool cur_white, Position this_turn) {
    if (cur_white == 1) {
      for (vector<Figure*> ::iterator it = black_figures.begin(); it != black_figures.end(); it++) {
        if (*it.pos == this_turn) {
          black_figures.erase(it);
          field[this_turn.get_x()][this_turn.get_y()] = NULL;
        }
      }
    }
    else 
      for (vector<Figure*> ::iterator it = white_figures.begin(); it != white_figures.end(); it++) {
      if (*it.pos == this_turn) {
        white_figures.erase(it);
        field[this_turn.get_x()][this_turn.get_y()] = NULL;
      }
    }
  }

  public:
    ChessParty() {}
    void turn() {
      /*
      Метод turn:
      Осуществляет один ход, псевдокод:
          1) Фиксируется сторона, которая ходит
          2) Выбирается рандомная фигура
          3) Получаем массив всех возможных ходов для этой фигуры
          4) Если массив пуст, goto 2
          5) Из допустимых мест хода выбирается рандомное место, куда пойдет фигура
          6) Если в этом месте уже есть фигура, то goto 7, иначе goto 8
              7) Удаляем съеденную фигуру с поля и из массива фигур.
          8) Ставим на это место текущую фигуру
          9) Очищаем предыдущее место текущей фигуры
          10) Меняется сторона, которая ходит
       */

      vector<Position> avail_pos;
      srand(time(0));
      Figure* figure = get_fig();
      do {
        vector<Position> avail_pos = figure->get_avail_turns(*this);
      } while (avail_pos.size() == 0);

      Position this_turn = avail_pos[rand() % avail_pos.size()];

      check_and_delete_fig(cur_white, this_turn);
      field[figure->pos.get_x()][figure->pos.get_y()] = NULL;

      figure->pos.set_x(this_turn.get_x());
      figure->pos.set_y(this_turn.get_y());
      cur_white = 1 - cur_white;
    }

    void print() {
      for (auto i : field) {
        for (auto j : field) {
          if (*j == NULL) cout << ". ";
          else cout << ". ";
        }
        cout << endl;
      }
    }
};
