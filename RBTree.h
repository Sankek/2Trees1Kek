#ifndef RBTREE_H
#define RBTREE_H

#include <cstdint>
#include "Node.h"
#include "ITree.h"

enum class Color;
struct RBNode;

class RBTree : public ITree {
private:
    using NodePtr = RBNode*;
    NodePtr root;

public:
    using Int_t = int_fast32_t;
    RBTree();
    ~RBTree();
    RBTree(const RBTree &tree);
    RBTree& operator=(const RBTree &tree);

    bool Find(const Int_t& value);
    void Insert(const Int_t& value);
    void Delete(const Int_t& value);
};


#endif // RBTREE_H
