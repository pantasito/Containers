/*
1) Добавить класс прямоугольник

2) Реализовать: итерационный процесс, N задается

У тебя есть список фигур, изначально он пустой. Задача поддерживать список упорядоченный по площадям.

list<Shape*>

На каждой итерации:
Генерируется случайная фигура. Для этой фигуры генерируются случайные параметры.
И она добавляется в список сразу в нужное место.
Можешь принтовать площади.
*/



#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
using namespace std;

class Shape
{
  public:
    virtual double area() = 0; // У функции нет реализации (она называется чистой функцией)
    // => класс Shape стал абстрактным
};

/*
void print_max(Shape* s1, Shape* s2) {
  if (s1->area() > s2->area())
    cout << s1->area();
  else
    cout << s2->area();
  cout << endl;
}
*/

class Triangle : public Shape
{
    double a, b, c;
  public:
    Triangle(double a, double b, double c) :a(a), b(b), c(c) {}

    double area() {
      double p = (a + b + c) / 2.0;
      return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class Circle : public Shape
{
    double r;
  public:
    Circle(double r) :r(r) {}
    
    double area() {
      return 3.14 * r * r;
    }
};

class Rectangle : public Shape
{
   double a, b;
 public:
   Rectangle(double a, double b) : a(a), b(b) {};

   double area() {
     return a * b;
   }

};

Shape* gen() {
  int command;
  command = rand() % 3;

  if (command == 0) {
    double r = 0;
    while(r == 0) {
      r = rand() % 10;
    }

    Circle* pc = new Circle(r);
    return pc;
  }

  if (command == 1) {

    double a, b, c;
    a = b = c = 0;

    while (a == 0) {
      a = rand() % 10;
    }

    while (b == 0) {
      b = rand() % 10;
    }

    c = rand() % 10;

    while (a + b <= c || a + c <= b || b + c <= a) {
      c = rand() % 10;
    }

    Triangle* pt = new Triangle(a, b, c);
    return pt;
  }

  if (command == 2) {
    double a, b;
    a = b = 0;
    
    while (a == 0) {
      a = rand() % 10;
    }

    while (b == 0) {
      b = rand() % 10;
    }
    Rectangle* pr = new Rectangle(a, b);
    return pr;
  }
}

int main()
{
  int N;
  cout << "int N = ";
  cin >> N;

  list <Shape*> l;
  srand(time(0));

  Shape* p = gen();
  l.push_back(p);
  N--;
  cout << p->area() << endl << "----------------------" << endl;
  list <Shape*>::iterator it = l.begin();


  while (N > 0) {
    N--;

    Shape* p = gen();

    for (it = l.begin(); it != l.end(); it++) {

      if ((*it)->area() > p->area()) {
        l.insert(it, p);
        break;
      }
    }

    if (it == l.end()) {
      l.push_back(p);
    }

    for (auto i : l) {
      cout << i->area() << endl;
    }
    cout << "----------------------" << endl;
  }
  
  system("pause");
}