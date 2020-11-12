#include <iostream>
#include "RBTree.h"


int main() {
    RBTree tree;

    tree.Insert(1);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(2);

    std::cout << "---\tTree 1\t\n";
    tree.PrettyPrint();

    tree.Delete(1);
    tree.Delete(5);
    std::cout << "---\tTree 1 after deleting\t\n";
    tree.PrettyPrint();

    return 0;
}
