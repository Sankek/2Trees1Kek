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

    tree.PrettyPrint();
    return 0;
}
