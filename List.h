#include <iostream>
#include <assert.h>
//using namespace std;

class List {

  class list_elem {

  public:
    int value;
    list_elem* prev;
    list_elem* next;
  };

  int len;
  list_elem* first;
  list_elem* last;

  void del_single() {
    if (first != NULL && first == last) {
      delete first;
      first = NULL;
      last = NULL;
      len--;
    }
  }

public:
  List() {
    first = NULL;
    last = NULL;
    len = 0;
  }

  List(const List& rhs):List() {
      list_elem* tmp = rhs.first;
      while (tmp != NULL) {
        push_end(tmp->value);
        tmp = tmp->next;
    }
  }

  ~List() {
    clear();
  }

  void push_start(int t) {
	  list_elem* elem = new list_elem;
    if (first == NULL && last == NULL) {				//пустой список
      len = 1;
      first = last = elem;
      elem->next = NULL;
      elem->prev = NULL;
      elem->value = t;
    }
    else {
      elem->next = first;
      first->prev = elem;
      elem->prev = NULL;
      first = elem;
      elem->value = t;
	  len++;
    }
  }


  void push_end(int t) {
    if (first == NULL && last == NULL) {
      list_elem* l1 = new list_elem;
      len = 1;
      first = l1;
      last = l1;
      l1->next = NULL;
      l1->prev = NULL;
      l1->value = t;
    }
    else {
      list_elem* elem = new list_elem;
      len++;
      elem->next = NULL;
      elem->prev = last;
      last->next = elem;
      last = elem;
      elem->value = t;
    }
  }

  int size() const {
    return len;
  }

  void pop_start() {
    if (first != NULL && first != last) {
      first = first->next;
      delete first->prev;
      first->prev = NULL;
      len--;
    }
    else {
      del_single();
    }
  }

  void pop_end() {
    if (last != NULL && last != first) {
      last = last->prev;
      delete last->next;
      last->next = NULL;
      len--;
    }
    else {
      del_single();
    }
  }

  int get_start() const {
    return first->value;
  }

  int get_end() const {
    return last->value;
  }

  bool empty() const {
    if (first == NULL) return true;
    else return false;
  }

  void clear() {
    if (first != NULL) {
      list_elem* tmp = first->next;
      while (tmp != NULL) {
        delete tmp->prev;
        tmp = tmp->next;
      }
      delete last;
      last = NULL;
      first = NULL;
      len = 0;
    }
  }

  void print() const {
    list_elem* tmp = first;
    while (tmp != NULL) {
      std::cout << tmp->value << " ";
      tmp = tmp->next;
    }
    std::cout << std::endl;
  }

  class iterator;

  // Вставляет в список элемент после элемента it
  void insert(iterator& it, int t) {
	  if (first == it.elem && first == NULL) {
		  push_start(t);
	  } 
	  if (first == it.elem && first != NULL) {
		  push_end(t);
	  } else {
		  list_elem* elem = new list_elem;
		  (it.elem->next)->prev = elem;
		  elem->next = it.elem->next;
		  it.elem->next = elem;
		  elem->prev = it.elem;
		  len++;
	  }
  }

 //  Принимает на вход число и возвращает итератор на первый встретившийся элемент в списке,
 //  который равен этому числу. Возвращает end - если такого нету
  iterator find(int a) {
	  iterator it(first);
	  while (it.elem != NULL || it.elem->value != a)
	  {
		  it.elem = it.elem->next;
	  }
	  return it;
  }

//  2) Принимает на вход 2 итератора и меняет местами элементы, на которые указывают итераторы
  void swap(iterator& lhs, iterator& rhs) {
	  if (lhs.elem != NULL && rhs.elem != NULL) {
		  int tmp = lhs.elem->value;
		  lhs.elem->value = rhs.elem->value;
		  rhs.elem->value = tmp;
	  }
}

  // Удаляет из списка элемент it
  void erase(iterator& it) {			//удаляет элемент который за итератором и переставляет итератор на следующий
	  if (first == last && first == NULL) return;
	  if (it.elem == first) {
		  pop_start();
		  it.elem = it.elem->next;
	  }
	  if (it.elem == last) {
		  pop_end(); 
		  it.elem = it.elem->prev;      //по условию должен был перевести итератор в NULL, не стал
	  }
	  else {
		  (it.elem->prev)->next = it.elem->next;
		  (it.elem->next)->prev = it.elem->prev;
		  delete it.elem;
		  len--;
		  it.elem = it.elem->next;
	  }
  }
  
  iterator begin() {
    iterator it(first);
    return it;
    //return iterator(first);
  }
    
  iterator end() {
    return iterator(NULL);
  }
  
  
  class iterator {
    friend List; // Мы говорим, что отныне класс List - наш друг. Это значит что у этого класса есть доступ
                 // к приватным полям класса iterator;

    List::list_elem* elem;    
    // Если elem == NULL - то это итератор end

    iterator(list_elem* p):elem(p) {}

  public:
    void operator ++() {
      if (elem != NULL) elem = elem->next;
    }

    void set(int a) {
      elem->value = a;
    }

    int operator *() const {
      if (elem != NULL) return elem->value;
    }

    bool operator == (iterator& rhs) const { 
      if (elem == rhs.elem) return true;
      else false;
    }

    bool operator != (iterator& rhs) const {
      if (elem == rhs.elem) return false;
      else true;
    }
  };
};