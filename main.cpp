#include <iostream>
#include "RBTree.h"

RBTree CreateTree(){
    RBTree bst;
    bst.Insert(8);
    bst.Insert(18);
    bst.Insert(5);
    bst.Insert(15);
    bst.Insert(17);
    bst.Insert(25);
    bst.Insert(40);
    bst.Insert(80);
    bst.Delete(25);

    return bst;
}


int main() {


//    std::cout << "---\tTree 1 before deleting nodes of tree 2\t---\n";
//    bst.PrettyPrint();
//
//    RBTree bst2 = bst;
//    std::cout << "---\tTree 2 before deleting nodes of tree 2\t---\n";
//    bst2.PrettyPrint();
//    std::cout << "---\tStarting deleting Nodes from tree 2\t---\n";
//
//    bst2.Delete(8);
//    bst2.Delete(18);
//    bst2.Delete(15);
//    bst2.Delete(17);
//    bst2.Delete(40);
//    std::cout << "---\tTree 1 after deleting nodes of tree 2\t---\n";
//    bst.PrettyPrint();
//    std::cout << "---\tTree 2 after deleting nodes of tree 2\t---\n";
//    bst2.PrettyPrint();
//    std::cout << "---\tTree 2 after returning to  tree 1 state\t---\n";
//    bst2 = bst;
//    bst2.PrettyPrint();
//

    RBTree tree = CreateTree();

    tree.PrettyPrint();
    std::cout << "---\n";

    tree.Delete(8);
    tree.Delete(19);
    tree.Delete(18);
    tree.Delete(25);

    tree.PrettyPrint();
    std::cout << "---\n";

    tree = CreateTree();
    tree.PrettyPrint();
    std::cout << "---\n";

    return 0;
}
