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
    bool operator>(const key_val_pair& rhs) {
      if (key > rhs.key) return true;
      return false;
    }
    bool operator==(const key_val_pair& rhs) {
      if (key == rhs.key) return true;
      return false;
    }
  };

  Binary_tree<key_val_pair> tree;
  //get set конструктор копирования
  public:
    class map_iterator;
    friend map_iterator;
    Map() {}

    Map(const Map& rhs) :tree(rhs.tree)  {}

    ~Map() {
      clear();
    }

    
    void set(Key key, Val val) {
      key_val_pair elem(key, val);        
      Binary_tree<key_val_pair>::tree_iterator it = tree.begin();
      if (!tree.is_in(elem,&it)) {
        tree.add(elem);   // Элемент с ключём key не существует
      }
      else {
        it.set_value(elem);       
      }
    }
    

    Val get(Key key) {  
      
    }
    
    //Val operator[](Key key) {}

    // Удаляет из мапы элемент с ключом key, если он есть
    void erase(Key key) {      
      key_val_pair elem(key, get(key));
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

   

    // Ищет в мапе ключик key, Возвращает итератор на элемент, и итератор end, если элемент не надйен
    /*
    map_iterator find(Key key) {     
    }

    map_iterator begin() {
    //  return tree.begin();
    }
    
    map_iterator end() {
    
    }

    class map_iterator
    {
      friend Map;
      Binary_tree<key_val_pair>::tree_iterator* elem;

      public:      
        void operator++() {
        
        }
        
        Val operator*() {            //наверное нужно переопределеить оператор для звездочки для структуры, чт мешает?
          return value.val;
        }

        Key first()  {
         // return *(tree.begin()).key;
        }

        Val second() {
         // return (tree.begin()++).val;
        }       

       // bool operator==(const map_iterator& rhs) const { return elem.val == rhs.elem.val; }
       // bool operator!=(const map_iterator& rhs) const { return elem.val != rhs.elem.val;}
    };
    */
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