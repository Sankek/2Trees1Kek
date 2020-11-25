#ifndef RBNODE_H
#define RBNODE_H

enum class Color{
    BLACK,
    RED
};

template <class T>
struct RBNode{
    T data{};
    RBNode *parent{nullptr};
    RBNode *left{nullptr};
    RBNode *right{nullptr};
    Color color{};

    RBNode() = default;
    ~RBNode();
    RBNode(const RBNode<T> &node);
    RBNode& operator=(const RBNode &node);
    void CopyHelper(RBNode<T>* node_copy, const RBNode<T>* node);
};


#endif //RBNODE_H
