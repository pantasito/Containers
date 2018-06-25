#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
#include "ColorCout.h"
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


class ChessParty
{
  friend Figure;
  bool cur_white;

  vector<Figure*> white_figures;
  vector<Figure*> black_figures;

  Figure* field[8][8];

  Figure* get_figure() {
    int size = (cur_white) ? white_figures.size() : black_figures.size();
    if (size == 0) return NULL;
    return (cur_white) ? white_figures[rand() % size] : black_figures[rand() % size];
  }

  void check_and_delete_fig(bool cur_white, Position this_turn) {
    if (field[this_turn.x][this_turn.y] == NULL) return;
    if (field[this_turn.x][this_turn.y]->is_white == cur_white) assert(0);

    vector<Figure*>& enemy_figures = cur_white ? black_figures : white_figures;
    for (vector<Figure*> ::iterator it = enemy_figures.begin(); it != enemy_figures.end(); it++) {
      if ((*it)->pos == this_turn) {
        enemy_figures.erase(it);
        field[this_turn.x][this_turn.y] = NULL;
        break;
      }
    }
  }
  /*
  bool shah_check(bool cur_white, Position desired_pos, class ChessParty* a) {
    vector<Figure*>& enemy_figures = cur_white ? black_figures : white_figures;
    for (vector<Figure*> ::iterator it = enemy_figures.begin(); it != enemy_figures.end(); it++) {
      vector<Position> p = (*it)->get_avail_turns(*this);
      for (auto pos : p) {
        if (pos == desired_pos) {
          return true;
        }
      }
    }
  }
  */

  class Pawn : public Figure
  {
  public:
    Pawn(Position _pos, bool _is_white) : Figure(_pos, _is_white) {}

    void print() {
      if (is_white) ColorOutput::SetTextColor(ColorOutput::White);
      else ColorOutput::SetTextColor(ColorOutput::Yellow);
      cout << "p "; ColorOutput::ResetColor();
    }

    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;
      if (is_white == true && pos.y < 7) {
        if (party.field[pos.x][pos.y + 1] == NULL) p.push_back(Position(pos.x, pos.y + 1));
        if (pos.x > 0 && party.field[pos.x - 1][pos.y + 1] != NULL && is_white != party.field[pos.x - 1][pos.y + 1]->is_white) p.push_back(Position(pos.x - 1, pos.y + 1));
        if (pos.x < 7 && party.field[pos.x + 1][pos.y + 1] != NULL && is_white != party.field[pos.x + 1][pos.y + 1]->is_white) p.push_back(Position(pos.x + 1, pos.y + 1));
      }
      if (is_white == false && pos.y > 0) {
        if (party.field[pos.x][pos.y - 1] == NULL) p.push_back(Position(pos.x, pos.y - 1));
        if (pos.x > 0 && party.field[pos.x - 1][pos.y - 1] != NULL && is_white != party.field[pos.x - 1][pos.y - 1]->is_white) p.push_back(Position(pos.x - 1, pos.y - 1));
        if (pos.x < 7 && party.field[pos.x + 1][pos.y - 1] != NULL && is_white != party.field[pos.x + 1][pos.y - 1]->is_white) p.push_back(Position(pos.x + 1, pos.y - 1));
      }
      return p;
    }
  };

  class Rook : public Figure
  {
  public:
  Rook(Position _pos, bool _is_white) : Figure(_pos, _is_white) {}

  void print() {
    if (is_white) ColorOutput::SetTextColor(ColorOutput::White);
    else ColorOutput::SetTextColor(ColorOutput::Yellow);
    cout << "r "; ColorOutput::ResetColor();
  }

  vector<Position> get_avail_turns(ChessParty& party) {
    vector<Position> p;

    int x_i[4] = { 1, -1, 0,  0 };
    int y_i[4] = { 0,  0, 1, -1 };

    for (int i = 0; i < 4; ++i) {
      for (int j = 1; j < 8; ++j) {
        int px = pos.x + j * x_i[i];
        int py = pos.y + j * y_i[i];
        if (px < 0 || px > 7 || py < 0 || py > 7) continue;
        if (party.field[px][py] == NULL) { p.push_back(Position(px, py)); }
        if (party.field[px][py] != NULL) {
          if (party.field[px][py]->is_white != is_white) { p.push_back(Position(px, py)); }
          break;
        }
      }
    }
    return p;
  }

  /*
  vector<Position> get_avail_turns(ChessParty& party) {
    vector<Position> p;

    for (int i = 1; (pos.x - i) >= 0; ++i) {
      if (party.field[pos.x - i][pos.y] == NULL) p.push_back(Position(pos.x - i, pos.y));
      if (party.field[pos.x - i][pos.y] != NULL) {
        if (party.field[pos.x - i][pos.y]->is_white != is_white) {
          p.push_back(Position(pos.x - i, pos.y));
        }
        break;
      }
    }

    for (int i = 1; (pos.x + i) <= 7; ++i) {
      if (party.field[pos.x + i][pos.y] == NULL) p.push_back(Position(pos.x + i, pos.y));
      if (party.field[pos.x + i][pos.y] != NULL) {
        if (party.field[pos.x + i][pos.y]->is_white != is_white) {
          p.push_back(Position(pos.x + i, pos.y));
        }
        break;
      }
    }

    for (int i = 1; (pos.y - i) >= 0; ++i) {
      if (party.field[pos.x][pos.y - i] == NULL) p.push_back(Position(pos.x, pos.y - i));
      if (party.field[pos.x][pos.y - i] != NULL) {
        if (party.field[pos.x][pos.y - i]->is_white != is_white) {
          p.push_back(Position(pos.x, pos.y - i));
        }
        break;
      }
    }

    for (int i = 1; (pos.y + i) <= 7; ++i) {
      if (party.field[pos.x][pos.y + i] == NULL) p.push_back(Position(pos.x, pos.y + i));
      if (party.field[pos.x][pos.y + i] != NULL) {
        if (party.field[pos.x][pos.y + i]->is_white != is_white) {
          p.push_back(Position(pos.x, pos.y + i));
        }
        break;
      }
    }

    return p;
    }
    */
  };

  class Bishop : public Figure 
  {
  public:
    Bishop(Position _pos, bool _is_white) : Figure(_pos, _is_white) {}

    void print() {
      if (is_white) ColorOutput::SetTextColor(ColorOutput::White);
      else ColorOutput::SetTextColor(ColorOutput::Yellow);
      cout << "b "; ColorOutput::ResetColor();
    }

    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;

      int x_i[4] = { 1,  1, -1, -1 };
      int y_i[4] = { 1, -1,  1, -1 };

      for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 8; ++j) {
          int px = pos.x + j * x_i[i];
          int py = pos.y + j * y_i[i];
          if (px < 0 || px > 7 || py < 0 || py > 7) continue;
          if (party.field[px][py] == NULL) { p.push_back(Position(px, py)); }
          if (party.field[px][py] != NULL) {
            if (party.field[px][py]->is_white != is_white) { p.push_back(Position(px, py)); }
            break;
          }
        }
      }
      return p;
    }

    /*
    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;

      for (int i = 1; (pos.x - i) >= 0 && (pos.y - i) >= 0; ++i) {
        if (party.field[pos.x - i][pos.y - i] == NULL) p.push_back(Position(pos.x - i, pos.y - i));
        if (party.field[pos.x - i][pos.y - i] != NULL) {
          if (party.field[pos.x - i][pos.y - i]->is_white != is_white) {
            p.push_back(Position(pos.x - i, pos.y - i));
          }
          break;
        }
      }

      for (int i = 1; (pos.x + i) <= 7 && (pos.y - i) >= 0; ++i) {
        if (party.field[pos.x + i][pos.y - i] == NULL) p.push_back(Position(pos.x + i, pos.y - i));
        if (party.field[pos.x + i][pos.y - i] != NULL) {
          if (party.field[pos.x + i][pos.y - i]->is_white != is_white) {
            p.push_back(Position(pos.x + i, pos.y - i));
          }
          break;
        }
      }

      for (int i = 1; (pos.x - i) >= 0 && (pos.y + i) <= 7; ++i) {
        if (party.field[pos.x - i][pos.y + i] == NULL) p.push_back(Position(pos.x - i, pos.y + i));
        if (party.field[pos.x - i][pos.y + i] != NULL) {
          if (party.field[pos.x - i][pos.y + i]->is_white != is_white) {   //тут ошибка
            p.push_back(Position(pos.x - i, pos.y + i));
          }
          break;
        }
      }

      for (int i = 1; (pos.x + i) <= 7 && (pos.y + i) <= 7; ++i) {
        if (party.field[pos.x + i][pos.y + i] == NULL) p.push_back(Position(pos.x + i, pos.y + i));
        if (party.field[pos.x + i][pos.y + i] != NULL) {
          if (party.field[pos.x + i][pos.y + i]->is_white != is_white) {
            p.push_back(Position(pos.x + i, pos.y + i));
          }
          break;
        }
      }
      
      return p;
    }
    */
  };

  class Knight : public Figure
  {
  public:
    Knight(Position _pos, bool _is_white) : Figure(_pos, _is_white) {}

    void print() {
      if (is_white) ColorOutput::SetTextColor(ColorOutput::White);
      else ColorOutput::SetTextColor(ColorOutput::Yellow);
      cout << "k "; ColorOutput::ResetColor();
    }

    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;
    
      int i_x[8] = { 1,  1, -1, -1,  2,  2, -2, -2 };
      int i_y[8] = { 2, -2,  2, -2,  1, -1,  1, -1 };

      for (int i = 0; i < 8; i++) {
        int px = pos.x + i_x[i];
        int py = pos.y + i_y[i];
        if (px < 0 || px > 7 || py < 0 || py > 7) continue;
        if (party.field[px][py] == NULL) p.push_back(Position(px, py));
        if (party.field[px][py] != NULL && party.field[px][py]->is_white != is_white) p.push_back(Position(px, py));
      }
      return p;
    }
    
    /*
    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;

      if (pos.x - 2 >= 0 && pos.y + 1 <= 7 && party.field[pos.x - 2][pos.y + 1] == NULL) p.push_back(Position(pos.x - 2, pos.y + 1));
      if (party.field[pos.x - 2][pos.y + 1] != NULL && pos.x - 2 >= 0 && pos.y + 1 <= 7 && party.field[pos.x - 2][pos.y + 1]->is_white != is_white) p.push_back(Position(pos.x - 2, pos.y + 1));

      if (party.field[pos.x + 2][pos.y + 1] == NULL && pos.x + 2 <= 7 && pos.y + 1 <= 7) p.push_back(Position(pos.x + 2, pos.y + 1));
      if (party.field[pos.x + 2][pos.y + 1] != NULL && pos.x + 2 <= 7 && pos.y + 1 <= 7 && party.field[pos.x + 2][pos.y + 1]->is_white != is_white) p.push_back(Position(pos.x + 2, pos.y + 1));

      if (party.field[pos.x - 2][pos.y - 1] == NULL && pos.x - 2 >= 0 && pos.y - 1 >= 0) p.push_back(Position(pos.x - 2, pos.y - 1));
      if (party.field[pos.x - 2][pos.y - 1] != NULL && pos.x - 2 >= 0 && pos.y - 1 >= 0 && party.field[pos.x - 2][pos.y - 1]->is_white != is_white) p.push_back(Position(pos.x - 2, pos.y - 1));

      if (party.field[pos.x + 2][pos.y - 1] == NULL && pos.x + 2 <= 7 && pos.y - 1 >= 0) p.push_back(Position(pos.x + 2, pos.y - 1));
      if (party.field[pos.x + 2][pos.y - 1] != NULL && pos.x + 2 <= 7 && pos.y - 1 >= 0 && party.field[pos.x + 2][pos.y - 1]->is_white != is_white) p.push_back(Position(pos.x + 2, pos.y - 1));
      return p;
    }
   */ 
  };

  class Queen : public Figure
  {
  public:
    Queen(Position _pos, bool _is_white) : Figure(_pos, _is_white) {}

    void print() {
      if (is_white) ColorOutput::SetTextColor(ColorOutput::White);
      else ColorOutput::SetTextColor(ColorOutput::Yellow);
      cout << "q "; ColorOutput::ResetColor();
    }

    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;

      int x_i[8] = { 1,  1, -1, -1, 1, -1,  0,  0 };
      int y_i[8] = { 1, -1,  1, -1, 0,  0,  1, -1 };

      for (int i = 0; i < 8; ++i) {
        for (int j = 1; j < 8; ++j) {
          int px = pos.x + j * x_i[i];
          int py = pos.y + j * y_i[i];
          if (px < 0 || px > 7 || py < 0 || py > 7) continue;
          if (party.field[px][py] == NULL) { p.push_back(Position(px, py)); }
          if (party.field[px][py] != NULL) {
            if (party.field[px][py]->is_white != is_white) { p.push_back(Position(px, py)); }
            break;
          }
        }
      }
      return p;
    }
    /*
    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;

      for (int i = 1; (pos.x - i) >= 0 && (pos.y - i) >= 0; ++i) {
        if (party.field[pos.x - i][pos.y - i] == NULL) p.push_back(Position(pos.x - i, pos.y - i));
        if (party.field[pos.x - i][pos.y - i] != NULL && party.field[pos.x - i][pos.y - i]->is_white != is_white) {
          p.push_back(Position(pos.x - i, pos.y - i));
          break;
        }
        if (party.field[pos.x - i][pos.y - i] != NULL && party.field[pos.x - i][pos.y - i]->is_white == is_white) break;
      }

      for (int i = 1; (pos.x + i) <= 7 && (pos.y + i) <= 7; ++i) {
        if (party.field[pos.x + i][pos.y + i] == NULL) p.push_back(Position(pos.x + i, pos.y + i));
        if (party.field[pos.x + i][pos.y + i] != NULL && party.field[pos.x + i][pos.y + i]->is_white != is_white) {
          p.push_back(Position(pos.x + i, pos.y + i));
          break;
        }
        if (party.field[pos.x + i][pos.y + i] != NULL && party.field[pos.x + i][pos.y + i]->is_white == is_white) break;
      }
      for (int i = 1; (pos.x - i) >= 0; ++i) {
        if (party.field[pos.x - i][pos.y] == NULL) p.push_back(Position(pos.x - i, pos.y));
        if (party.field[pos.x - i][pos.y] != NULL && party.field[pos.x - i][pos.y]->is_white != is_white) {
          p.push_back(Position(pos.x - i, pos.y));
          break;
        }
        if (party.field[pos.x - i][pos.y] != NULL && party.field[pos.x - i][pos.y]->is_white == is_white) break;
      }

      for (int i = 1; (pos.x + i) <= 7; ++i) {
        if (party.field[pos.x + i][pos.y] == NULL) p.push_back(Position(pos.x + i, pos.y));
        if (party.field[pos.x + i][pos.y] != NULL && party.field[pos.x + i][pos.y]->is_white != is_white) {
          p.push_back(Position(pos.x + i, pos.y));
          break;
        }
        if (party.field[pos.x + i][pos.y] != NULL && party.field[pos.x + i][pos.y]->is_white == is_white) break;
      }
      for (int i = 1; (pos.y - i) >= 0; ++i) {
        if (party.field[pos.x][pos.y - i] == NULL) p.push_back(Position(pos.x, pos.y - i));
        if (party.field[pos.x][pos.y - i] != NULL && party.field[pos.x][pos.y - i]->is_white != is_white) {
          p.push_back(Position(pos.x, pos.y - i));
          break;
        }
        if (party.field[pos.x][pos.y - i] != NULL && party.field[pos.x][pos.y - i]->is_white == is_white) break;
      }

      for (int i = 1; (pos.y + i) <= 7; ++i) {
        if (party.field[pos.x][pos.y + i] == NULL) p.push_back(Position(pos.x, pos.y + i));
        if (party.field[pos.x][pos.y + i] != NULL && party.field[pos.x][pos.y + i]->is_white != is_white) {
          p.push_back(Position(pos.x, pos.y + i));
          break;
        }
        if (party.field[pos.x][pos.y + i] != NULL && party.field[pos.x][pos.y + i]->is_white == is_white) break;
      }
      return p;
    }
    */
  };

  class King : public Figure
  {
    // ороль должен будет запускать функцию сканер опасности от других фигур. 
    //написать эту функцию в партии.
    
    //после каждого хода в методе turn провер€ть есть ли шах, если есть вывести месседж, что вот шах! 
    //после этого нужно передвинут корол€
    //если нет ходов, то играла закончилась

  public:
    King(Position _pos, bool _is_white) : Figure(_pos, _is_white) {}

    void print() {
      if (is_white) ColorOutput::SetTextColor(ColorOutput::White);
      else ColorOutput::SetTextColor(ColorOutput::Yellow);
      cout << "1 "; ColorOutput::ResetColor();
    }

    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;

      int x_i[8] = { 1,  1, -1, -1, 1, -1,  0,  0 };
      int y_i[8] = { 1, -1,  1, -1, 0,  0,  1, -1 };

      for (int i = 0; i < 8; ++i) {
        int px = pos.x + x_i[i];
        int py = pos.y + y_i[i];
        if (px < 0 || px > 7 || py < 0 || py > 7) continue;
        if (party.field[px][py] == NULL) { 
     //     if (!shah_check(is_white, Position(px, py)), *this) p.push_back(Position(px, py));
        }
        if (party.field[px][py] != NULL) {
          if (party.field[px][py]->is_white != is_white) { p.push_back(Position(px, py)); }
          break;
        }
      }
      return p;
    }

    /*
    vector<Position> get_avail_turns(ChessParty& party) {
      vector<Position> p;

      if (party.field[pos.x - 1][pos.y - 1] == NULL && pos.x - 1 >= 0 && pos.y - 1 >= 0) p.push_back(Position(pos.x - 1, pos.y - 1));
      if (party.field[pos.x - 1][pos.y] == NULL && pos.x - 1 >= 0) p.push_back(Position(pos.x - 1, pos.y));
      if (party.field[pos.x - 1][pos.y + 1] == NULL && pos.x - 1 >= 0 && pos.y + 1 <= 7) p.push_back(Position(pos.x - 1, pos.y + 1));

      if (party.field[pos.x + 1][pos.y - 1] == NULL && pos.x + 1 <= 7 && pos.y - 1 >= 0) p.push_back(Position(pos.x + 1, pos.y - 1));
      if (party.field[pos.x + 1][pos.y] == NULL && pos.x + 1 <= 7) p.push_back(Position(pos.x + 1, pos.y));
      if (party.field[pos.x + 1][pos.y + 1] == NULL && pos.x + 1 <= 7 && pos.y + 1 <= 7) p.push_back(Position(pos.x + 1, pos.y + 1));

      if (party.field[pos.x][pos.y - 1] == NULL && pos.y - 1 >= 0) p.push_back(Position(pos.x, pos.y - 1));
      if (party.field[pos.x][pos.y + 1] == NULL && pos.y + 1 <= 7) p.push_back(Position(pos.x, pos.y + 1));

      return p;
    }
    */
  };

  public:
    ChessParty() {
      {
        cur_white = true;

        for (int i = 0; i < 8; i++)
          for (int j = 0; j < 8; j++)
          {
            field[i][j] = NULL;
            if ((j == 0 && i == 0) || (j == 0 && i == 7)) {
              field[i][j] = new Rook(Position(i, j), true);
              white_figures.push_back(field[i][j]);
            }
            if ((j == 7 && i == 0) || (j == 7 && i == 7)) {
              field[i][j] = new Rook(Position(i, j), false);
              black_figures.push_back(field[i][j]);
            }
            if ((j == 0 && i == 1) || (j == 0 && i == 6)) {
              field[i][j] = new Knight(Position(i, j), true);
              white_figures.push_back(field[i][j]);
            }
            if ((j == 7 && i == 1) || (j == 7 && i == 6)) {
              field[i][j] = new Knight(Position(i, j), false);
              black_figures.push_back(field[i][j]);
            }
            if ((j == 0 && i == 2) || (j == 0 && i == 5)) {
              field[i][j] = new Bishop(Position(i, j), true);
              white_figures.push_back(field[i][j]);
            }
            if ((j == 7 && i == 2) || (j == 7 && i == 5)) {
              field[i][j] = new Bishop(Position(i, j), false);
              black_figures.push_back(field[i][j]);
            }
            if (i == 3 && j == 0) {
              field[i][j] = new Queen(Position(i, j), true);
              white_figures.push_back(field[i][j]);
            }
            if (i == 3 && j == 7) {
              field[i][j] = new Queen(Position(i, j), false);
              black_figures.push_back(field[i][j]);
            }
            if (i == 4 && j == 0) {
              field[i][j] = new King(Position(i, j), true);
              white_figures.push_back(field[i][j]);
            }
            if (i == 4 && j == 7) {
              field[i][j] = new King(Position(i, j), false);
              black_figures.push_back(field[i][j]);
            }
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

    /* проверка есть ли шах
    vector<Position> is_now_shah = figure->get_avail_turns(*this);
    
    for (auto pos : is_now_shah) {
      if (pos == King.pos) {
        cout << endl << "SHAH!" << endl;
      }
    }
    */


    cur_white = !cur_white;
  }

  void print() {
    for (int j = 0; j < 8; ++j) {
      for (int i = 0; i < 8; ++i) {
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
  srand(time(0));
  ChessParty party;
  while (true){
//  for (int i = 0; i < 100; i++) {
 
    party.print();
    party.turn();
  }

  system("pause");
}
