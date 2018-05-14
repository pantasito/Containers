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
  //get set конструктор копирования
  public:
    Map() {
      tree.clear();     //как сделать лучше? //например скажу, что map - друг для binare_tree;
    }

    Map(const Map& rhs) : Map() {
//      tree = Binary_tree <key_val_pair> tree(const Binary_tree& rhs.tree); //протестировать
    }

    ~Map() {
      clear();
    }

    /*
    void set(Key key, Val val) {
      key_val_pair elem(key, val);
      if (!tree.is_in(elem)) tree.add(elem);   //нужно что-то сделать с методом is_in
    }
    */

    Val get(Key key) {  
    
    }
    
    //Val operator[](Key key) {}

    // Удаляет из мапы элемент с ключом key, если он есть
    void erase(Key key) {
      key_val_pair elem(key, get(Key key));
      tree.remove(elem);
    }

    void clear() {
      tree.clear();
    }

    int size() {
      return tree.size();
    }

    bool empty() {
      return tree.empty();
    }

    class iterator;

    // Ищет в мапе ключик key, Возвращает итератор на элемент, и итератор end, если элемент не надйен
    iterator find(Key key) {
      key_val_pair elem(key, get(Key key));
      return iterator(tree.search(elem));
    }

    iterator begin() {
      return tree.begin();
    }
    
    iterator end() {
    
    }

    class iterator
    {

      public:
        void operator++() {
        
        }
        
        Val operator*() {            //наверное нужно переопределеить оператор для звездочки для структуры, чт мешает?
          return value.val;
        }

        Key first()  {
          return *(tree.begin()).key;
        }

        Val second() {
          return (tree.begin()++).val;
        }       

       // bool operator==(const iterator& rhs) const { return elem.val == rhs.elem.val; }
       // bool operator!=(const iterator& rhs) const { return elem.val != rhs.elem.val;}
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