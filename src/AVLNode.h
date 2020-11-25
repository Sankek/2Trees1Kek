#ifndef AVLNODE_H
#define AVLNODE_H

template <class T>
struct AVLNode{
    T data{};
    int height{1};
    AVLNode* left{};
    AVLNode* right{};
    
    AVLNode() = default;
    explicit AVLNode(const T& k) { data = k; }
    ~AVLNode();
    AVLNode(const AVLNode<T> &node);
    AVLNode& operator=(const AVLNode &node);
    void CopyHelper(AVLNode<T>* node_copy, const AVLNode<T>* node);
};


#endif //AVLNODE_H
