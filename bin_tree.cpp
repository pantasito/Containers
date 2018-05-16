#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>
#include "BinaryTree.h"
#include "Map.h"
#include <algorithm>

using namespace std;

/*
void test() {
  Binary_tree a;
  int v = 10;
  srand(time(0));

  for (int i = 0; i < v; ++i) {
    a.add(rand() % 10);
  }

  a.print();
  cout << endl;


  for (int i = 0; i < v; ++i) {
    cout << "number of " << i << " " << a.count(i) << endl;
  }

  cout << endl;

  for (int i = 0; i < v; ++i) {
    cout << "number " << i << " is in our tree - ";
    if (a.is_in(i)) cout << "true";
    else cout << "false";
    cout << endl;
  }
}
*/
/*
void test1() {
  for (int i = 0; i < 1; ++i) {
    Binary_tree a;
    int v = 10;
    vector <int> s;
    int tmp;

    srand(time(0));

    for (int j = 0; j < v; ++j) {
      tmp = rand() % 25;
      a.add(tmp);
      s.push_back(tmp);
    }

    Binary_tree b(a);
    a.print();
    cout << "=============" << endl;
    b.print();
    cout << "=============" << endl;
    b.clear();
    a.print();
    cout << "=============" << endl;
    b.print();
    /*
    //sort(s.begin(), s.end());
    for (auto i : s) {
      cout << i << " ";
    }
    reverse(s.begin(), s.end());

    cout << endl;
    cout << endl;
    a.print();
    cout << endl;


    for (int i = 0; i < v; ++i) {
      tmp = s.back();
      s.pop_back();
      cout << endl << "remove " << tmp << endl;
      a.remove(tmp);
      a.print();
    }
    
  }

}


void test2() {
  Binary_tree a;
  a.add(5);
  a.add(6);
  a.add(9);
  a.add(7);
  a.add(8);
  a.add(4);
  a.add(2);
  a.add(3);
  a.add(1);
  a.add(0);
  a.print();

  Binary_tree::iterator it = a.begin();

  it = it.get_left();
  it.to_left();
  it.to_right();

  cout << *it << endl;
  cout << "----------------------------" << endl;
  //	a.remove_subtree(it);
  a.insert(it, 0, 10);
  a.print();

  it.to_right();

  cout << *it << endl;

  a.insert_sibling(it, 11); //not correct, will fix it later
  cout << "----------------------------" << endl;
  a.print();
}
*/


/*
class A
{
  public:
    bool operator>=(const A& rhs) { return true; }
};
*/

int main() {
  //test();
  //test1();
  //test2();	

  Map<string, int> m;
  m.set("a", 3);
  m.set("a", 4);
  //m.erase("a");
//  m.begin();
  //cout << m.find("a").second << endl;
  Binary_tree<string> tt;
  tt.add("HELLO");
  tt.add("HELLO1");
  tt.add("HELLO2");
  tt.add("HELLO3");

  tt.print();
	system("pause");
}