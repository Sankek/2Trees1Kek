// Copyright 2020 Alexander Izyurov, Semen Matrenok, Michael Pavlov

#include "AVLNode.h"

template<class T>
AVLNode<T>::~AVLNode() {
  delete this->left;
  delete this->right;
}

template<class T>
void AVLNode<T>::CopyHelper(AVLNode<T> *node_copy, const AVLNode<T> *node) {
  if (node != nullptr) {
    node_copy->data = node->data;
    node_copy->height = node->height;

    if (node->left != nullptr) {
      auto node_copy_left = new AVLNode<T>;
      node_copy->left = node_copy_left;
    }

    if (node->right != nullptr) {
      auto node_copy_right = new AVLNode<T>;
      node_copy->right = node_copy_right;
    }

    CopyHelper(node_copy->left, node->left);
    CopyHelper(node_copy->right, node->right);
  }
}

template<class T>
AVLNode<T>::AVLNode(const AVLNode<T> &node) {
  CopyHelper(this, &node);
}

template<class T>
AVLNode<T> &AVLNode<T>::operator=(const AVLNode<T> &node) {
  // self-assignment guard
  if (this == &node)
    return *this;

  // do the copy
  delete this->left;
  delete this->right;
  CopyHelper(this, &node);

  return *this;
}

template
struct AVLNode<int>;
