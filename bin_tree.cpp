#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Binary_tree {
 
  class iterator;
  friend iterator;
 
  struct tree_elem {
    tree_elem* parent;
    tree_elem* left;
    tree_elem* right;
    int value_;
    
    tree_elem(int value_, tree_elem* parent, tree_elem* left, tree_elem* right) : 
      value_(value_), parent(parent), left(left), right(right) { }
  };

  tree_elem* root;
  int size_;

  void print(tree_elem* a, int k) {
    if (a != NULL) {
      print(a->right, k + 4);
      cout << setw(k) << a->value_ << endl;
      print(a->left, k + 4);
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

  tree_elem* search(int value) {
    tree_elem* tmp = root;
    while (tmp != NULL) {
      if (value == tmp->value_) return tmp;
      if (value > tmp->value_) tmp = tmp->right;
      else tmp = tmp->left;
    }
    return NULL;
  }

  // Сгенерировать копию дерева tmp и вернуть на корень нового дерева указатель.
  // Родителя у корня дублированного дерева не будет, т.е. он будет NULL
  tree_elem* duplicate_tree(tree_elem* tmp) {
    if (tmp == NULL) return NULL;
   
    tree_elem* new_elem = new tree_elem(tmp->value_, NULL, NULL, NULL);

    new_elem->right = duplicate_tree(tmp->right);
    if (new_elem->right != NULL)
      new_elem->right->parent = new_elem;

    new_elem->left = duplicate_tree(tmp->left);
    if (new_elem->left != NULL)
      new_elem->left->parent = new_elem;

    return new_elem;
  }

public:
  Binary_tree() {
    root = NULL;
    size_ = 0;
  }

  Binary_tree(const Binary_tree& rhs) {
      root = duplicate_tree(rhs.root);      
      size_ = rhs.size_;
  }

  ~Binary_tree() {
    clear();
  }

  void add(int value) {

    if (root == NULL) {
      root = new tree_elem(value, NULL, NULL, NULL);
      size_ = 1;    
      return;
    }

	tree_elem* leaf = new tree_elem(value,NULL,NULL,NULL);
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
    if (tmp == NULL) return;
    
    size_--;

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

    if (tmp->left == NULL && tmp->right != NULL ||
        tmp->left != NULL && tmp->right == NULL)
    {
      tree_elem* child = (tmp->left == NULL) ? tmp->right : tmp->left;

      if (tmp == root) {
        root = child;
        child->parent = NULL;
        delete tmp;
        return;
      }

      if (tmp->parent->left == tmp) {
        tmp->parent->left = child;
        child->parent = tmp->parent;
      }
      else {
        tmp->parent->right = child;
        child->parent = tmp->parent;
      }

      delete tmp;
      return;
    }

    //есть левый и правый потомок
    {
      tree_elem* ohoho = tmp;
      ohoho = ohoho->right;

      while (ohoho->left != NULL) {
        ohoho = ohoho->left;
      }

      if (ohoho != tmp->right) {
        if (ohoho->right != NULL) {
          ohoho->right->parent = ohoho->parent;
          ohoho->parent->left = ohoho->right;
        }
        else {
          ohoho->parent->left = NULL;
        }

        ohoho->right = tmp->right;
        if (tmp->right != NULL) tmp->right->parent = ohoho;
      }

      ohoho->left = tmp->left;
      tmp->left->parent = ohoho;
      ohoho->parent = tmp->parent;
      if (tmp != root) {
        if (tmp->parent->left == tmp) 
          tmp->parent->left = ohoho;
        else
          tmp->parent->right = ohoho;
      }
      else {
        root = ohoho;
      }

      delete tmp;
      return;    
    }


    /*
    //есть левый и правый потомок
    if (tmp == root || tmp->parent->right == tmp) {
      tree_elem* ohoho = tmp;
      ohoho = ohoho->right;

      while (ohoho->left != NULL) {
        ohoho = ohoho->left;
      }

      if (ohoho != tmp->right) {
        if (ohoho->right != NULL) {
          ohoho->right->parent = ohoho->parent;
          ohoho->parent->left = ohoho->right;
        }
        else {
          ohoho->parent->left = NULL;
        }

        ohoho->right = tmp->right;
        if (tmp->right != NULL) tmp->right->parent = ohoho;
        ohoho->left = tmp->left;
        if (tmp->left != NULL) tmp->left->parent = ohoho;
        ohoho->parent = tmp->parent;
        if (tmp != root) tmp->parent->right = ohoho;
        else root = ohoho;
        delete tmp;
        return;
      }
      else {
        ohoho->left = tmp->left;
        tmp->left->parent = ohoho;
        ohoho->parent = tmp->parent;
        if (tmp != root) tmp->parent->right = ohoho;
        else root = ohoho;
        delete tmp;
        return;
      }
    }

    if (tmp == root || tmp->parent->left == tmp) {
      tree_elem* ohoho = tmp;
      ohoho = ohoho->left;

      while (ohoho->right != NULL) {
        ohoho = ohoho->right;
      }

      if (ohoho != tmp->left) {
        if (ohoho->left != NULL) {
          ohoho->left->parent = ohoho->parent;
          ohoho->parent->right = ohoho->left;
        }
        else {
          ohoho->parent->right = NULL;
        }

        ohoho->right = tmp->right;
        if (tmp->right != NULL) tmp->right->parent = ohoho;
        ohoho->left = tmp->left;
        if (tmp->left != NULL) tmp->left->parent = ohoho;
        ohoho->parent = tmp->parent;
        if (tmp != root) tmp->parent->left = ohoho;
        else root = ohoho;
        delete tmp;
        return;
      }
      else {
        ohoho->right = tmp->right;
        tmp->right->parent = ohoho;
        ohoho->parent = tmp->parent;
        if (tmp != root) tmp->parent->left = ohoho;
        else root = ohoho;
        delete tmp;
        return;
      }
    }
    */
    
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

  void clear() {
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

  class iterotor;

  iterotor begin() {
	  return iterotor(root);
  }

  void insert(iterotor it, bool left, int value) {
	  if (it.elem == NULL) return;

	  if (left == 1 && it.elem->left == NULL) {
		  it.elem->left = new tree_elem(value, it.elem, NULL, NULL);
	  }
	  if (left == 0 && it.elem->right == NULL) {
		  it.elem->right = new tree_elem(value, it.elem, NULL, NULL);
	  }
  }

  bool insert_sibling(iterotor it, int value) {
    iterotor b(it.elem->parent);

      if (it.elem == NULL || it.elem->parent == NULL) return false;
      if (it.elem->parent->left != NULL && it.elem->parent->right != NULL) return false;
      if (it.elem->left == NULL) {
        insert(iterotor(it.elem->parent), 1, value);
      }
      else {
        insert(iterotor(it.elem->parent), 0, value);
      }
	  return true;
  }
 
  // Для просто бинарного дерева
  void remove_subtree(iterotor it) {
	  if (it.elem->parent == NULL) clear(root);
	  if (it.elem->parent->left == it.elem) it.elem->parent->left = NULL;
	  if (it.elem->parent->right == it.elem) it.elem->parent->right = NULL;

	  clear(it.elem); 
  }

  class iterotor
  {
	  friend Binary_tree;

	  tree_elem* elem;

	  iterotor(tree_elem* _elem) : elem (_elem){}
  
  public:
      int operator*() const {
		  if (elem != NULL) return elem->value_;
	  }

      bool operator==(const iterotor& rhs) const {
		  if (elem->value_ == rhs.elem->value_ && elem == rhs.elem) return true;
		  else return false;
	  }

      bool operator!=(const iterotor& rhs) const {
		  return !(elem == rhs.elem);
		  }

      iterotor get_left()    const {
		  iterotor it(elem);
		  if (elem != NULL && elem->left != NULL) it.elem = elem->left;
		  return it;
	  }

      iterotor get_right()   const {
			  iterotor it(elem);
			  if (elem != NULL && elem->right != NULL) it.elem = elem->right;
			  return it;
		  }

      iterotor get_parent()  const {
		  iterotor it(elem);
		  if (elem == NULL) return it;
		  if (elem->parent == NULL) return it;
		  if (elem->parent->left == NULL || elem->parent->right == NULL) return it;
		  if (elem == elem->parent->left)  it.elem = elem->parent->right;
		  if (elem == elem->parent->right) it.elem = elem->parent->left;
		  return it;
	  }
      
	  iterotor get_sibling() const {
		  iterotor it(elem);
		  if (elem != NULL && elem->parent != NULL) it.elem = elem->parent;
		  return it;
	  }

      void to_left() {
		  if (elem != NULL && elem->left != NULL) elem = elem->left;
	  }

      void to_right() {
		  if (elem != NULL && elem->right != NULL) elem = elem->right;
	  }

      void to_parent() {
		  if (elem == NULL || elem->parent == NULL) return;
		  elem = elem->parent;
	  }

      void to_sibling() {
		  if (elem == NULL) return;
		  if (elem->parent == NULL) return;
		  if (elem->parent->left == NULL || elem->parent->right == NULL) return;
		  if (elem == elem->parent->left)  elem = elem->parent->right;
		  if (elem == elem->parent->right) elem = elem->parent->left;
	  }

      bool have_left()    const {
		  if (elem != NULL && elem->left != NULL) return true;
		  else return false;
	  }

      bool have_right()   const {
		  if (elem != NULL && elem->right != NULL) return true;
		  else return false;
	  }

      bool have_parent()  const {
		  if (elem != NULL && elem->parent != NULL) return true;
		  else return false;
	  }
 
      bool have_sibling() const {
		  if (elem == NULL) return false;
		  if (elem->parent == NULL) return false;
		  if (elem->parent->left != NULL && elem->parent->right != NULL) return true;
		  else return false;
	  }
  };

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
    */
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

  Binary_tree::iterotor it = a.begin();

  it = it.get_left();
  it.to_left();
  it.to_right();

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

int main() {
//  test();
// test1();
// test2();	

	system("pause");
}


