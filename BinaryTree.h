#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <vector>

#include <string>

using namespace std;

template <typename T>
class Binary_tree {
  class iterator;
  friend iterator;

  struct tree_elem {
    tree_elem* parent;
    tree_elem* left;
    tree_elem* right;
    T value_;

    tree_elem(T value_, tree_elem* parent, tree_elem* left, tree_elem* right) :
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
      size_--;
    }
  }

  tree_elem* search(T value) {
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

  void add(T value) {
    if (root == NULL) {
      root = new tree_elem(value, NULL, NULL, NULL);
      size_ = 1;
      return;
    }

    tree_elem* leaf = new tree_elem(value, NULL, NULL, NULL);
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

  void remove(T value) {
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
  }

  bool is_in(T value) {
    tree_elem* tmp = root;
    while (tmp != NULL) {
      if (value == tmp->value_) return true;
      if (value > tmp->value_) tmp = tmp->right;
      else tmp = tmp->left;
    }
    return false;
  }

  int count(T value) {
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

  iterator begin() {
    return iterator(root);
  }

  void insert(iterator it, bool left, int value) {
    if (it.elem == NULL) return;

    if (left && it.elem->left == NULL) {
      it.elem->left = new tree_elem(value, it.elem, NULL, NULL);
      size_++;
    }
    if (!left && it.elem->right == NULL) {
      it.elem->right = new tree_elem(value, it.elem, NULL, NULL);
      size_++;
    }
  }

  bool insert_sibling(iterator it, int value) {
    if (it.elem == NULL || it.elem->parent == NULL) return false;
    if (it.elem->parent->left != NULL && it.elem->parent->right != NULL) return false;
    if (it.elem->parent->left == NULL) {
      it.elem->parent->left = new tree_elem(value, it.elem->parent, NULL, NULL);
    }
    else {
      it.elem->parent->right = new tree_elem(value, it.elem->parent, NULL, NULL);
    }
    size_++;
    return true;
  }

  // Для просто бинарного дерева
  void remove_subtree(iterator it) {
    if (it.elem == NULL) return;
    if (it.elem->parent == NULL) { clear(); return; }
    if (it.elem->parent->left == it.elem) it.elem->parent->left = NULL;
    if (it.elem->parent->right == it.elem) it.elem->parent->right = NULL;

    clear(it.elem);
  }

  class iterator
  {
    friend Binary_tree;

    tree_elem* elem;

    iterator(tree_elem* _elem) : elem(_elem) {}

  public:
    int operator*() const {
      if (elem != NULL) return elem->value_;
    }

    bool operator==(const iterator& rhs) const { return elem == rhs.elem; }
    bool operator!=(const iterator& rhs) const { return elem != rhs.elem; }

    iterator get_left()    const {
      iterator it(elem);
      if (elem != NULL && elem->left != NULL) it.elem = elem->left;
      return it;
    }

    iterator get_right()   const {
      iterator it(elem);
      if (elem != NULL && elem->right != NULL) it.elem = elem->right;
      return it;
    }

    iterator get_sibling()  const {
      iterator it(elem);
      if (elem == NULL) return it;
      if (elem->parent == NULL) return it;
      if (elem->parent->left == NULL || elem->parent->right == NULL) return it;
      if (elem == elem->parent->left)  it.elem = elem->parent->right;
      if (elem == elem->parent->right) it.elem = elem->parent->left;
      return it;
    }

    iterator get_parent() const {
      iterator it(elem);
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
      return false;
    }
  };
};