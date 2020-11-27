// Copyright 2020 Alexander Izyurov, Semen Matrenok, Michael Pavlov

#ifndef SRC_AVLTREE_H_
#define SRC_AVLTREE_H_

#include "ITree.h"
#include "AVLNode.h"

template<class T>
class AVLTree : public ITree<T> {
 public:
  AVLTree() = default;
  AVLTree(const AVLTree &tree);
  AVLTree &operator=(const AVLTree &tree);
  ~AVLTree() override { delete root; }
  int32_t get_rotations_count();

  void ResetRotationsCount();
  unsigned char get_height(AVLNode<T> *p);

  void Insert(const T &k) override;  // вставка ключа k в дерево с корнем p
  bool Find(const T &k) override;
  void Delete(const T &k) override;
  void PreOrderTraversalHelper(AVLNode<T> *p);
  void PreOrderTraversal();

 private:
  AVLNode<T> *root{};
  int32_t rotations_count = 0;

  void FixHeight(AVLNode<T> *p);
  bool FindHelper(AVLNode<T> *p, const T &k);
  AVLNode<T> *RotateRight(AVLNode<T> *p);  // правый поворот вокруг p
  AVLNode<T> *RotateLeft(AVLNode<T> *q);  // левый поворот вокруг q
  AVLNode<T> *InsertHelper(AVLNode<T> *p, const T &k);  // вставка ключа k в дерево с корнем p
  int32_t BFactor(AVLNode<T> *p);
  AVLNode<T> *Balance(AVLNode<T> *p);  // балансировка узла p
  AVLNode<T> *FindMin(AVLNode<T> *p);  // поиск узла с минимальным ключом в дереве p
  AVLNode<T> *RemoveMin(AVLNode<T> *p);  // удаление узла с минимальным ключом из дерева p
  AVLNode<T> *DeleteHelper(AVLNode<T> *p, const T &k);  // удаление ключа k из дерева p
};

#endif  // SRC_AVLTREE_H_
