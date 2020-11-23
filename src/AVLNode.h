#ifndef AVLNODE_H
#define AVLNODE_H

template <class T>
struct AVLNode{
    T key{};
    int height{1};
    AVLNode* left{};
    AVLNode* right{};
    AVLNode() = default;
    explicit AVLNode(const T& k) { key = k; }

};


#endif //AVLNODE_H
