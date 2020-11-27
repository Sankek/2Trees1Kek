// Copyright 2020 Alexander Izyurov, Semen Matrenok, Michael Pavlov

#include <iostream>
#include "RBNode.h"

template<class T>
RBNode<T>::~RBNode() {
  delete this->left;
  delete this->right;
}

template<class T>
void RBNode<T>::CopyHelper(RBNode<T> *node_copy, const RBNode<T> *node) {
  if (node != nullptr) {
    node_copy->data = node->data;
    node_copy->color = node->color;

    if (node->left != nullptr) {
      auto node_copy_left = new RBNode<T>;
      node_copy_left->parent = node_copy;
      node_copy->left = node_copy_left;
    }

    if (node->right != nullptr) {
      auto node_copy_right = new RBNode<T>;
      node_copy_right->parent = node_copy;
      node_copy->right = node_copy_right;
    }

    CopyHelper(node_copy->left, node->left);
    CopyHelper(node_copy->right, node->right);
  }
}

template<class T>
RBNode<T>::RBNode(const RBNode<T> &node) {
  CopyHelper(this, &node);
}

template<class T>
RBNode<T> &RBNode<T>::operator=(const RBNode<T> &node) {
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
struct RBNode<int>;
