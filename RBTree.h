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
    NodePtr Grandparent(NodePtr node);
    NodePtr Uncle(NodePtr node);
    void RotateLeft(NodePtr node);
    void RotateRight(NodePtr node);
    NodePtr Minimum(NodePtr start_node);
    void PrintHelper(NodePtr start_node, std::string indent, bool last);

    void InsertHelper(const Int_t& value);
    void InsertCase1(NodePtr node);
    void InsertCase2(NodePtr node);
    void InsertCase3(NodePtr node);
    void InsertCase4(NodePtr node);
    void InsertCase5(NodePtr node);

    void DeleteHelper(const Int_t& value, NodePtr start_node);
    void DeleteCase1(NodePtr node);
    void DeleteCase2(NodePtr node);
    void DeleteCase3(NodePtr node);
    void DeleteCase4(NodePtr node);
    void DeleteCase5(NodePtr node);
    void DeleteCase6(NodePtr node);


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
    RBNode* GetRoot(){ return root; };
};


#endif // RBTREE_H
