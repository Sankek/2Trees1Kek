// Copyright 2020 Alexander Izyurov, Semen Matrenok, Michael Pavlov

#ifndef SRC_RBTREE_H_
#define SRC_RBTREE_H_

#include <cstdint>
#include <string>

#include "ITree.h"
#include "RBNode.h"

template<class T>
class RBTree : public ITree<T> {
 public:
  RBTree() = default;
  ~RBTree() override { delete root; }
  RBTree(const RBTree &tree);
  RBTree &operator=(const RBTree &tree);

  bool Find(const T &value) override { return FindHelper(value, root); }
  void Insert(const T &value) override { InsertHelper(value); }
  void Delete(const T &value) override { DeleteHelper(value, root); }

  void ResetRotationsCount() { rotations_count = 0; }
  int_fast32_t get_rotations_count() { return rotations_count; }
  void PrettyPrint();

 private:
  using NodePtr = RBNode<T> *;
  NodePtr root{};
  int_fast32_t rotations_count{};

  bool FindHelper(const T &value, RBNode<T> *node);

  NodePtr left(NodePtr n);
  NodePtr right(NodePtr n);
  bool is_red(NodePtr n);
  bool is_black(NodePtr n);
  Color color(NodePtr n);
  NodePtr parent(NodePtr n);
  NodePtr grandparent(NodePtr n);
  NodePtr brother(NodePtr n);
  NodePtr uncle(NodePtr n);
  NodePtr leftmost(NodePtr n);
  NodePtr rightmost(NodePtr n);

  void RotateLeft(NodePtr node);
  void RotateRight(NodePtr node);
  void PrintHelper(NodePtr start_node, std::string indent, bool last);

  void InsertHelper(const T &value);
  void InsertCase1(NodePtr node);
  void InsertCase2(NodePtr node);
  void InsertCase3(NodePtr node);
  void InsertCase4(NodePtr node);
  void InsertCase5(NodePtr node);

  void DeleteHelper(const T &value, RBNode<T> *node);
  void DeleteFix(NodePtr node);
};

#endif  // SRC_RBTREE_H_
