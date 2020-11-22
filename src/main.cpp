#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <cstdlib>

#include "RBTree.h"
#include "AVLTree.h"
#include "Timer.h"


int GetRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

template <class Tree>
double AverageTime(Tree &tree, int64_t max, bool (*func) (Tree&, int), bool copy= false) {
    const int num_executions = 99;
    Timer time_it;
    Tree temp_tree;
    int64_t current_index;
    double time, average_time = 0;
    int64_t first_index;
    bool enough_size = false;
    if (max >= num_executions - 2) {
        first_index = max / 2 - (num_executions / 2) + 2;
        enough_size = true;
    }
    else {
        first_index = 1;
    }

    temp_tree = tree;
    for (int i = 0; i < 1000; ++i) {
        if (i % 100 == 0) { std::cout << '#'; }
//        current_index = GetRandomNumber(1, max);
        if (copy){ temp_tree = tree; }
        current_index = first_index;
        time_it.reset();
        for (int j = 0; j < num_executions; ++j) {
//            temp_tree.prettyPrint();
            func(temp_tree, current_index);
            if (enough_size) {current_index ++;}
//            else {current_index = GetRandomNumber(1, max);}
//            else if (i % (num_executions/max + 1) == 0) { current_index += 1;}
//            temp_tree.prettyPrint();
        }
        time = time_it.elapsed();
        average_time += (time - average_time) / (i + 1);

//        if (max >= 10*num_executions) {first_index += 9;}
    }

    std::cout << '\n';
    return average_time;
}

template <class Tree>
bool findNode (Tree &tree, int k) {
    return tree.Find(k);
}

template <class Tree>
bool insertNode (Tree &tree, int k) {
//    std::cout << "node for inserting: " << k << '\n';
//    tree.prettyPrint();
    tree.Insert(k);
    return {};
}

template <class Tree>
bool deleteNode (Tree &tree, int k) {
//    std::cout << "node for deleting: " << k << '\n';
//    tree.prettyPrint();
    tree.Delete(k);
    return {};
}

template <class Tree>
void TestTime(const std::string& name, bool make_graphs = true){
    const int MAX_DEGREE = 20;
    Tree tree;
    Timer time_it;
    std::fstream file;
    file.open("data/" + name + ".csv", std::fstream::out);
    file << "N" << ',' << "elapsed_find_time" << ',' << "elapsed_insert_time" << ',' << "elapsed_delete_time" << '\n';

    double average_find_time, average_insert_time, average_delete_time;

    uint64_t k = 1;
    for (int degree = 1; degree < MAX_DEGREE; ++degree) {
        std::cout << "Degree = " << degree+1 << '\n';
        for (int64_t i = k; i < k*2; ++i) {
            tree.Insert(i);
        }

        k *= 2;

        std::cout << "Calculating find_time:    ";
        average_find_time = AverageTime(tree, k - 1, findNode);
//        tree.PrettyPrint();
        std::cout << "Calculating insert_time:  ";
        average_insert_time = AverageTime(tree, k - 1, insertNode);
//        tree.PrettyPrint();
        std::cout << "Calculating delete_time:  ";
        average_delete_time = AverageTime(tree, k - 1, deleteNode, false);
        std::cout << "____________________________________________________" << '\n';

        file << k << ',' << average_find_time << ',' << average_insert_time << ',' << average_delete_time << '\n';
//        file << k << ',' << average_find_time << ',' << average_insert_time << '\n';
    }
    file.close();

    if (make_graphs){
        std::string str = "python scripts/graph_maker.py " + name;
        const char* command = str.c_str();
        system(command);
    }
}

[[maybe_unused]] void TestRBTree(){
    RBTree tree;

    std::cout << "Tree:\n";
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
    tree.PrettyPrint();
    std::cout << "Rotations while insert: " << tree.GetRotationsCount() << '\n';

    std::cout << "Tree after Deletions:\n";
    tree.ResetRotationsCount();
    tree.Delete(1);
    tree.Delete(5);
    tree.Delete(4);
    tree.Delete(6);
    tree.Delete(9);
    tree.PrettyPrint();
    std::cout << "Rotations: " << tree.GetRotationsCount() << '\n';

    std::cout << "Tree after Delete(3):\n";
    tree.ResetRotationsCount();
    tree.Delete(3);
    tree.PrettyPrint();
    std::cout << "Rotations: " << tree.GetRotationsCount() << '\n';
}

[[maybe_unused]] void TestAVLTree(){
    AVLTree tree;
    tree.Insert(12);
    tree.Insert(11);
    tree.Insert( 9);
    tree.Insert(35);
    tree.Insert(7);
    tree.Insert( 60);
    tree.Insert(5);
    tree.Insert(5);
    //std::cout<<tree.Find(12);
    //tree.Delete(12);
    //std::cout<<tree.Find(12);
    std::cout<<tree.get_rotations();
    //tree.PreOrderTraversal();
}



int main() {
//    TestRBTree();
//    TestAVLTree();
    std::cout << '\n' << "TESTING RBTree." << '\n';
    TestTime<RBTree>("RBTree_timings", true);
    std::cout << '\n' << "TESTING AVLTree."  << '\n';
    TestTime<AVLTree>("AVLTree_timings", true);

    return 0;
}
