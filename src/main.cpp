// Copyright 2020 Alexander Izyurov, Semen Matrenok, Michael Pavlov

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <cstdlib>

#include "RBTree.h"
#include "AVLTree.h"
#include "Timer.h"

template<class Tree>
double AverageTime(const Tree &tree, int64_t max, bool (*func)(Tree *, int64_t), bool copy = false) {
  const int num_executions = 9999;
  Timer time_it;
  Tree temp_tree;
  int64_t current_index;
  double time, average_time = 0;
  int64_t first_index;
  bool enough_size =
      false;  // we want to insert/find/delete nonrepeating items; if enough_size=true wa can, else - we can't
  if (max >= num_executions - 2) {
    first_index = max / 2 - (num_executions / 2) + 2;
    enough_size = true;
  } else {
    first_index = max - 1;
  }

  temp_tree = tree;
  for (int i = 0; i < 1000; ++i) {
    if (i % 100 == 0) { std::cout << '#'; }
    if (copy) { temp_tree = tree; }
    current_index = first_index;
    time_it.reset();
    for (int j = 0; j < num_executions; ++j) {
      func(&temp_tree, current_index);
      if (enough_size) { current_index++; }
    }
    time = time_it.elapsed();
    average_time += (time - average_time) / (i + 1);
  }

  std::cout << '\n';
  return average_time;
}

template<class Tree>
bool findNode(Tree *tree, int64_t k) {
  return tree->Find(k);
}

template<class Tree>
bool insertNode(Tree *tree, int64_t k) {
  tree->Insert(k);
  return {};
}

template<class Tree>
bool deleteNode(Tree *tree, int64_t k) {
  tree->Delete(k);
  return {};
}

template<class Tree>
void TestTime(const std::string &name, bool make_graphs = true) {
  const int MAX_DEGREE = 24;
  Tree tree;
  Timer time_it;
  std::fstream file;

  std::string mkdir_str = "python scripts/create_directory.py data";
  const char *mkdir_cmd = mkdir_str.c_str();
  system(mkdir_cmd);

  file.open("data/" + name + ".csv", std::fstream::out);
  file << "N" << ',' << "elapsed_find_time" << ',' << "elapsed_insert_time" << ',' << "elapsed_delete_time" << '\n';

  double average_find_time, average_insert_time, average_delete_time;

  int64_t k = 1;
  for (int degree = 1; degree < MAX_DEGREE; ++degree) {
    std::cout << "Degree = " << degree + 1 << '\n';
    for (int64_t i = k; i < k * 2; ++i) {
      tree.Insert(i);
    }

    k *= 2;

    std::cout << "Calculating find_time:    ";
    average_find_time = AverageTime(tree, k - 1, findNode);
    std::cout << "Calculating insert_time:  ";
    average_insert_time = AverageTime(tree, k - 1, insertNode);
    std::cout << "Calculating delete_time:  ";
    average_delete_time = AverageTime(tree, k - 1, deleteNode, false);
    std::cout << "____________________________________________________" << '\n';

    file << k << ',' << average_find_time << ',' << average_insert_time << ',' << average_delete_time << '\n';
  }
  file.close();

  if (make_graphs) {
    std::string make_graph_str = "python scripts/graph_maker.py " + name;
    const char *make_graph_cmd = make_graph_str.c_str();
    system(make_graph_cmd);
  }
}

[[maybe_unused]] void TestRBTree() {
  RBTree<int> tree;
  RBTree<int> tree2;

  std::cout << "Tree and tree 2:\n";
  tree.Insert(1);
  tree.Insert(5);
  tree.Insert(4);
  tree.Insert(6);
  tree.Insert(7);
  tree.Insert(2);
  tree.Insert(9);
  tree.Insert(10);
  tree.Insert(11);
  tree.Insert(3);
  tree2 = tree;
  tree.PrettyPrint();
  std::cout << "Rotations while insert: " << tree.get_rotations_count() << '\n';

  std::cout << "Tree after Deletions:\n";
  tree.ResetRotationsCount();
  tree.Delete(1);
  tree.Delete(5);
  tree.Delete(4);
  tree.Delete(6);
  tree.Delete(9);
  tree.PrettyPrint();
  std::cout << "Rotations: " << tree.get_rotations_count() << '\n';

  std::cout << "Tree after Delete(3):\n";
  tree.ResetRotationsCount();
  tree.Delete(3);
  tree.PrettyPrint();
  std::cout << "Rotations: " << tree.get_rotations_count() << '\n';

  std::cout << "Tree2 after operations on tree1:\n";
  tree2.PrettyPrint();
}

[[maybe_unused]] void TestAVLTree() {
  AVLTree<int> tree1;
  tree1.Insert(1);
  tree1.Insert(3);
  tree1.Insert(5);
  tree1.Insert(4);
  tree1.Insert(2);
  tree1.Insert(7);
  tree1.Insert(7);
  tree1.Insert(8);
  // std::cout<<tree1.Find(12);
  // tree1.Delete(12);
  // std::cout<<tree1.Find(12);
  // std::cout<< tree1.get_rotations_count();
  std::cout << "tree1:\n";
  tree1.PreOrderTraversal();

  AVLTree<int> tree2 = tree1;
  std::cout << "tree1 after delete:\n";
  tree1.Delete(3);
  tree1.Delete(3);
  tree1.Delete(4);
  tree1.Delete(7);
  tree1.Delete(7);
  tree1.Delete(5);
  tree1.Delete(2);
  tree1.Delete(1);
  tree1.Delete(8);

  tree1.PreOrderTraversal();

  std::cout << "tree2 (should be the same as tree 1 at start):\n";
  tree2.PreOrderTraversal();
}

int main() {
//    TestRBTree();
//    TestAVLTree();
  std::cout << '\n' << "TESTING RBTree." << '\n';
  TestTime<RBTree<int>>("RBTree_timings", true);
  std::cout << '\n' << "TESTING AVLTree." << '\n';
  TestTime<AVLTree<int>>("AVLTree_timings", true);

  return 0;
}
