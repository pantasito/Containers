#pragma once
#include "BinaryTree.h"

template <typename Key, typename Val>
class Map {
  struct key_val_pair {
    Key key;
    Val val;

    key_val_pair(Key key, Val val) :key(key), val(val) {}

    bool operator>=(const key_val_pair& rhs) {
      if (key >= rhs.key) return true;
      return false;
    }
  };

  Binary_tree<key_val_pair> tree;

  public:
    Map() {}
    Map(const Map& rhs) {}
    ~Map() {}

    void set(Key key, Val val) {}
    Val get(Key key) {}
    
    //Val operator[](Key key) {}

    // Удаляет из мапы элемент с ключом key, если он есть
    void erase(Key key) {}

    void clear() {}
    int size() {}
    bool empty() {}

    class iterator;

    // Ищет в мапе ключик key, Возвращает итератор на элемент, и итератор end, если элемент не надйен
    iterator find(Key key) {}

    iterator begin() {}
    iterator end() {}

    class iterator
    {
      public:
        void operator++() {}
        Val operator*() {}

        Key first()  {}
        Val second() {}       

       // bool operator==() {}
       // bool operator!=() {}
    };
};

// map<string, int> m;
// cout << m["Hello"];
// m["sds"] = 4;
// m.set("Hello", 1);
// m.get("Hello");

/*
int tt;

int& f()
{
  return tt;
}

int main()
{
  f() = 4;
}
*/

/*
int& max(int& a, int& b)
{
  return a > b ? a : b;
}

int aa = 3;
int bb = 4;

max(aa, bb) = 4;
*/