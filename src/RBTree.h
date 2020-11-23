#ifndef RBTREE_H
#define RBTREE_H

#include <cstdint>
#include <string>

#include "ITree.h"
#include "RBNode.h"


template <class T>
class RBTree : public ITree<T> {
public:
    RBTree() = default;
    ~RBTree() override{
        Destroy(root);
    }
    RBTree(const RBTree &tree);
    RBTree& operator=(const RBTree &tree);

    bool Find(const T& value) override{ return FindHelper(value, root); };
    void Insert(const T& value) override{ InsertHelper(value); };
    void Delete(const T& value) override{ DeleteHelper(value, root); };

    void ResetRotationsCount() { rotations_count = 0; };
    T GetRotationsCount(){ return rotations_count; };
    void PrettyPrint();
private:
    using NodePtr = RBNode<T>*;
    NodePtr root{};
    T rotations_count{};

    void Destroy(NodePtr node);
    void CopyHelper(NodePtr node_copy, NodePtr node);
    bool FindHelper(const T& value, NodePtr node);

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

    void InsertHelper(const T& value);
    void InsertCase1(NodePtr node);
    void InsertCase2(NodePtr node);
    void InsertCase3(NodePtr node);
    void InsertCase4(NodePtr node);
    void InsertCase5(NodePtr node);

    void DeleteHelper(const T& value, NodePtr node);
    void DeleteFix(NodePtr node);

};


#endif // RBTREE_H
