#include <iostream>
#include <fstream>
#include <functional>
#include "RBTree.h"
#include <chrono>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now()) {}
    void reset() {
        m_beg = clock_t::now();
    }

    double elapsed() const {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

//int getRandomNumber(int min, int max)
//{
//    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
//    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
//}

template <class T>
double time_1000_iterations(RBTree &tree, uint64_t max, T func, bool copy=false) {
    const int num_executions = 999;
    Timer time_it;
    RBTree temp_tree;
    bool out;
    uint64_t inp_num;
    double time, average_time = 0;
    int first_input;
    bool enough_size = false;
    if (max >= num_executions - 2) {
        first_input = max / 2 - (num_executions / 2) + 2;
        enough_size = true;
    }
    else {
        first_input = 1;
    }

    temp_tree = tree;
    for (int i = 0; i < 1000; ++i) {
        if (i % 100 == 0) { std::cout << '#'; }
//        inp_num = getRandomNumber(1, max);
        if (copy){ temp_tree = tree; }
        inp_num = first_input;
        time_it.reset();
        for (int j = 0; j < num_executions; ++j) {
//            temp_tree.prettyPrint();
            out = func(temp_tree, inp_num);
            if (enough_size) {inp_num ++;}
//            temp_tree.prettyPrint();
        }
        time = time_it.elapsed();
        average_time += (time - average_time) / (i + 1);

//        if (max >= 10*num_executions) {first_input += 9;}
    }

    std::cout << '\n' << '\n' ;
    return average_time;
}


bool findNode (RBTree &tree, int k) {
    return tree.Find(k);
}

bool insertNode (RBTree &tree, int k) {
//    std::cout << "node for inserting: " << k << '\n';
//    tree.prettyPrint();
    tree.Insert(k);
    return {};
}

bool deleteNode (RBTree &tree, int k) {
//    std::cout << "node for deleting: " << k << '\n';
//    tree.prettyPrint();
    tree.Delete(k);
    return {};
}



int main() {
    RBTree tree;
    Timer time_it;
    std::fstream file;
    file.open("data.csv", std::fstream::out);
    file << "N" << ',' << "elapsed_find_time" << ',' << "elapsed_insert_time" << ',' << "elapsed_delete_time" << '\n';

    double average_find_time = 0, average_insert_time = 0, average_delete_time = 0;

    uint64_t k = 1;
    for (int degree = 1; degree < 24; ++degree) {
        std::cout << '\n' << "Degree = " << degree+1 << '\n';
        for (int64_t i = k; i < k*2; ++i) {
            tree.Insert(i);
        }

        k *= 2;

        std::cout << "Calculating find_time..." << '\n';
        average_find_time = time_1000_iterations(tree, k-1, findNode);
//        tree.PrettyPrint();
        std::cout << "Calculating insert_time..." << '\n';
        average_insert_time = time_1000_iterations(tree, k-1, insertNode);
//        tree.PrettyPrint();
//        std::cout << "Calculating delete_time..." << '\n';
//        average_delete_time = time_1000_iterations(tree, k-1, deleteNode);

//        file << k << ',' << average_find_time << ',' << average_insert_time << ',' << average_delete_time << '\n';
        file << k << ',' << average_find_time << ',' << average_insert_time << '\n';
    }
    file.close();
    return 0;
}
