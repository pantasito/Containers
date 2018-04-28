#include <iostream>
#include <assert.h>
using namespace std;

template <typename T>

class List {

	class list_elem {

	public:
		T value;
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

	List(const List<T>& rhs) {
		if (rhs.empty()) {
			List();
		} else {
			list_elem* tmp = rhs.first;
			while (tmp != NULL) {
				push_end(tmp->value);
				tmp = tmp->next;
			}
		}
	}


	~List() {
		clear();
	}

	void push_start(T t) {
		if (first == NULL && last == NULL) {				//пустой список
			list_elem* l1 = new list_elem;
			len = 1;
			first = l1;
			last = l1;
			l1->next = NULL;
			l1->prev = NULL;
			l1->value = t;
		} else {							
			list_elem* elem = new list_elem;
			len++;
			elem->next = first;
			first->prev = elem;
			elem->prev = NULL;
			first = elem;
			elem->value = t;
		}
	}


	void push_end(T t) {
		if (first == NULL && last == NULL) {
			list_elem* l1 = new list_elem;
			len = 1;
			first = l1;
			last = l1;
			l1->next = NULL;
			l1->prev = NULL;
			l1->value = t;
		} else {
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
		} else {
			del_single();
		}
	}

	void pop_end() {
		if (last != NULL && last != first) {
			last = last->prev;
			delete last->next;
			last->next = NULL;
			len--;
		} else {
			del_single();
		}
	}
	
	T get_start() const {
			return first->value;
	}
	
	T get_end() const {
			return last->value;
	}

	bool empty() const {
		if (first == NULL) return true;
		else return false;
	}
	
	void clear() {
		if (first != NULL){
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

	void print() const{ 
		list_elem* tmp = first;
		while (tmp != NULL) {
			cout << tmp->value << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}

	/*	void insert(iterator& it, T t) {

	}
	*/

	/*
	void erase(iterator& it) {			//удаляет элемент который за итератором и переставляет итератор на следующий

	}
	*/

	/*
	iterator begin() {

	}

	iterator end() {

	}

	class iterator {
	public:
		void operator ++(){}
		T operator *() const {}
		bool operator == (iterator& rhs) const {}
		bool operator != (iterator& rhs) const {}

	};
*/
};

/*
/*#include "List.h"
#include <iostream>
#include <time.h>
using namespace std;

void full_me(List <int>& l) {
	l.push_start(4);
	l.push_end(5);
	l.push_start(3);
	l.push_end(6);
	l.push_start(2);
	l.push_end(7);
	l.push_start(1);
	l.push_end(8);
	l.push_start(0);
	l.push_end(9);
}

void test(List <int>& l) {
	cout << l.empty() << endl;
	l.clear();
	cout << l.empty() << endl;

	full_me(l);
	l.print();
	cout << l.get_start() << " " << l.get_end() << endl;
	while (!l.empty()) {
		l.pop_start();
		l.print();
	}
	l.pop_start();
	l.print();

	full_me(l);
	l.print();
	while (!l.empty()) {
		l.pop_end();
		l.print();
	}
	l.pop_end();
	l.print();
	
	full_me(l);
	List <int> l1(l);

	l.clear();
	List <int> l2(l);

	cout << "list l1:" << endl;
	l1.print();
	cout << "l1.size() = " << l1.size() << " l1.empty() =" << l1.empty() << endl;

	cout << "list l2:" << endl;
	l2.print();
	cout << "l2.size() = " << l2.size() << " l1.empty() =" << l2.empty() << endl;

	
}
*/
