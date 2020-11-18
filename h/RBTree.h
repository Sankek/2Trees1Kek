#ifndef RBTREE_H
#define RBTREE_H

#include <cstdint>
#include <string>

#include "ITree.h"
#include "RBNode.h"


class RBTree : public ITree {
private:
    using NodePtr = RBNode*;
    NodePtr root{};

    void Destroy(NodePtr node);
    void CopyHelper(NodePtr node_copy, NodePtr node);
    bool FindHelper(const Int_t& value, NodePtr start_node);

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

    void InsertHelper(const Int_t& value);
    void InsertCase1(NodePtr node);
    void InsertCase2(NodePtr node);
    void InsertCase3(NodePtr node);
    void InsertCase4(NodePtr node);
    void InsertCase5(NodePtr node);

    void DeleteHelper(const Int_t& value, NodePtr node);
    void DeleteFix(NodePtr node);
public:
    using Int_t = int_fast32_t;
    RBTree() = default;
    ~RBTree() override{
        Destroy(root);
    }
    RBTree(const RBTree &tree);
    RBTree& operator=(const RBTree &tree);

    bool Find(const Int_t& value) override{ return FindHelper(value, root); };
    void Insert(const Int_t& value) override{ InsertHelper(value); };
    void Delete(const Int_t& value) override{ DeleteHelper(value, root); };

    void PrettyPrint();
};


#endif // RBTREE_H
