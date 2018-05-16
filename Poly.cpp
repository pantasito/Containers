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
#include <iomanip>
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
      return acos(-1) * r * r;
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
  int command = rand() % 3;

  if (command == 0) {
    double r = (double)rand() / (double)RAND_MAX;    
    return new Circle(r*9+1);
  }

  if (command == 1) {

    double a, b, c;
    
    a = ((double)rand() / (double)RAND_MAX) * 10 + 1 ;
    b = ((double)rand() / (double)RAND_MAX) * 10 + 1;
   
    do
    {
      c = ((double)rand() / (double)RAND_MAX) * 10 + 1;
    } while (a + b <= c || a + c <= b || b + c <= a);
        

    return new Triangle(a, b, c);    
  }

  if (command == 2) {
    double a, b;
    a = ((double)rand() / (double)RAND_MAX) * 10 + 1;
    b = ((double)rand() / (double)RAND_MAX) * 10 + 1;
    
    return new Rectangle(a, b);    
  }
}

int main()
{
  int N;
  cout << "int N = ";
  cin >> N;
  
  list <Shape*> l;
  srand(time(0));

  l.push_back(gen());
  cout << (*l.begin())->area() << endl << "----------------------" << endl;
  
  list <Shape*>::iterator it;
  for (int i = 0; i < N-1; i++) {   
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
    
      for (auto p : l) {
        cout << setw(5) << p->area() << " ";
    }
    //cout << "----------------------" << endl;
      cout << endl;
  }
  
  system("pause");
}