#include <iostream>
using namespace std;

class Shape
{
  public:
    virtual double area() = 0; // У функции нет реализации (она называется чистой функцией)
    // => класс Shape стал абстрактным
};


void print_max(Shape* s1, Shape* s2) {
  if (s1->area() > s2->area())
    cout << s1->area();
  else
    cout << s2->area();
  cout << endl;
}

class Triangle : public Shape
{
    int a, b, c;
  public:
    Triangle(int a, int b, int c) :a(a), b(b), c(c) {}

    double area() {
      return a + b + c;
    }
};

class Circle : public Shape
{
    double r;
  public:
    Circle(double r) :r(r) {}
    
    double area() {
      return acos(-1)*r*r;
    }
};

int main()
{
  Triangle t1(1, 2, 3);
  Triangle* pt2 = new Triangle(2, 3, 4);
  Circle c1(2);
  Circle* pc2 = new Circle(3);

  print_max(&t1, pt2);
  print_max(&t1, pc2);

  cout << "\n";
  system("pause");
}