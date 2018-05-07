#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>

using namespace std;

class Binary_tree {

	struct tree_elem {
		tree_elem* parent;
		tree_elem* left;
		tree_elem* right;
		int value_;
	};
	
	tree_elem* root;
	int size_;
	
	void print(tree_elem* a, int k) {
		if (a != NULL) {
			print(a->right, k+3);
			cout << setw(k) << a->value_<< endl;
			print(a->left, k+3);
		}
	}

	int count(tree_elem* tmp, int value) {
		int k = 0;
		if (tmp != NULL) {
			if (tmp->value_ == value) k++;
			k += count(tmp->right, value);
			k += count(tmp->left, value);
		}
		return k;
	}

	void clear(tree_elem* tmp) {
		if (tmp != NULL) {
			clear(tmp->right);
			clear(tmp->left);
			delete tmp;
		}
	}

	/*
	tree_elem* get_data(tree_elem* tmp) {
		if (tmp != NULL) {
			tree_elem* hops = new tree_elem;
			hops->value_ = tmp->value_;
			
		}
	}
	*/


public:
	/*
	Binary_tree(const Binary_tree& rhs) {
		if (rhs.root == NULL) {
			root = NULL;
			size_ = 0;
			return;
		}

		



	}
	*/

	Binary_tree() {
		root = NULL;
		size_ = 0;
	}

	~Binary_tree() {
		clear();
	}

	void add(int value) {

		if (root == NULL) {
			root = new tree_elem;
			size_ = 1;
			root->parent = NULL;
			root->left = NULL;
			root->right = NULL;
			root->value_ = value;
			return;
		}
		/*	этот вариант пока не работает
		if (root == NULL) {
			root = new tree_elem(NULL, NULL, NULL, value);
			size_ = 1;
			return;
		}
		*/
		tree_elem* leaf = new tree_elem;
		tree_elem* tmp = root;
		while (tmp != NULL) {
			if (value >= tmp->value_) {
				if (tmp->right == NULL) {
					tmp->right = leaf;
					leaf->parent = tmp;
					break;
				} 
				else tmp = tmp->right;
			}
			else {
				if (tmp->left == NULL) {
					tmp->left = leaf;
					leaf->parent = tmp;
					break;
				}
				else tmp = tmp->left;
			}
		}
		leaf->value_ = value;
		leaf->right = leaf->left = NULL;
		size_++;
	}

	void remove(int value) {
		tree_elem* tmp = search(value);
		if (tmp != NULL) {
			if (tmp->left == NULL && tmp->right == NULL) {
				if (tmp->parent == NULL) {
					root = NULL;
					delete tmp;
					return;
				}
				if (tmp->parent->left == tmp) {
					tmp->parent->left = NULL;
				}
				else {
					tmp->parent->right = NULL;
				}
				delete tmp;
				return;
			}
			
			if (tmp->left == NULL && tmp->right != NULL) {
				if (tmp->parent->left == tmp) {
					tmp->parent->left = tmp->right;
					tmp->right->parent = tmp->parent;
				}
				else {
					tmp->parent->right = tmp->right;
					tmp->right->parent = tmp->parent;
				}
				delete tmp;
				return;
			}
			
			if (tmp->left != NULL && tmp->right == NULL) {
				if (tmp->parent->left == tmp) {
					tmp->parent->left = tmp->left;
					tmp->left->parent = tmp->parent;
				}
				else {
					tmp->parent->right = tmp->left;
					tmp->left->parent = tmp->parent;
				}
				delete tmp;
				return;
			}

			//есть левый и правый потомок
			if (tmp->parent->left == tmp) {
			

			}
	}

	
	tree_elem* search(int value) {
		tree_elem* tmp = root;
		while (tmp != NULL) {
			if (value == tmp->value_) return tmp;
			if (value > tmp->value_) tmp = tmp->right;
			else tmp = tmp->left;
		}
		return NULL;
	}

	bool is_in(int value) {
		tree_elem* tmp = root;
		while (tmp != NULL) {
			if (value == tmp->value_) return true;
			if (value > tmp->value_) tmp = tmp->right;
			else tmp = tmp->left;
		}
		return false;
	}

	int count(int value) {		
		return count(root, value);
	}

	void clear(){
		clear(root);
		root = NULL;
		size_ = 0;
	}

	int size() {
		return size_;
	}

	void print() {
		print(root, 0);
	}

	bool empty() {
		if (root == NULL) {
			assert(size_ == 0);
			return true;
		}
		else return false;
	}
};

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

void test1() {
	Binary_tree tree;

	tree.add(5);
	tree.add(4);
	tree.add(6);
	tree.add(7);
	tree.add(7);
	tree.add(7);


	tree.print();
	cout << endl;

	while (tree.count(7) != 0) {
		tree.remove(7);
		tree.print();
		cout << endl;
	}
}


void test2() {
	Binary_tree b;
	b.add(10);
	b.print();
	cout << endl;
	b.remove(0);
	b.print();
	cout << endl;

	b.remove(10);
	b.print();
	cout << endl;
}

int main() {
	test();
	test1();
	test2();
	system("pause");
}


