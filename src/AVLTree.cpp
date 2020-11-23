#include <iostream>

#include "AVLTree.h"


template <class T>
int32_t AVLTree<T>::get_rotations(){
    return rotations;
}

template <class T>
void AVLTree<T>::null_rotations(){
    rotations = 0;
}

template <class T>
void AVLTree<T>::CopyHelper(AVLNode<T>* node_copy, AVLNode<T>* node) {
    if (node != nullptr) {
        node_copy->key = node->key;
        node_copy->height = node->height;

        if (node->left != nullptr) {
            auto node_copy_left = new AVLNode<T>;
            node_copy->left = node_copy_left;
        }

        if (node->right != nullptr) {
            auto node_copy_right = new AVLNode<T>;
            node_copy->right = node_copy_right;
        }

        CopyHelper(node_copy->left, node->left);
        CopyHelper(node_copy->right, node->right);
    }
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T> &tree){
    root = new AVLNode<T>;
    CopyHelper(root, tree.root);
}

template <class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T> &tree){
    // self-assignment guard
    if (this == &tree)
        return *this;

    // do the copy
    Destroy(root);
    root = new AVLNode<T>;
    CopyHelper(root, tree.root);

    return *this;
}


template <class T>
void AVLTree<T>::Destroy(AVLNode<T>* node){
    if (node) {
        if (node->left) {
            Destroy(node->left);
        }
        if (node->right) {
            Destroy(node->right);
        }
    }
    delete node;
}


template <class T>
unsigned char AVLTree<T>::get_height(AVLNode<T>* p){
    return p ? p->height : 0;
}


template <class T>
int32_t AVLTree<T>::BFactor(AVLNode<T>* p){
    return get_height(p->right)-get_height(p->left); // разница высот левого и правого поддеревьев (Balance factor)
}

template <class T>
void AVLTree<T>::FixHeight(AVLNode<T>* p)
{
    unsigned char hl = get_height(p->left);
    unsigned char hr = get_height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

template <class T>
AVLNode<T>* AVLTree<T>::RotateRight(AVLNode<T>* p) // правый поворот вокруг p
{   rotations++;
    if (p==root){
        AVLNode<T>* q = p->left;
        p->left = q->right;
        q->right = p;
        FixHeight(p);
        FixHeight(q);
        return root=q;
    } else {
        AVLNode<T>* q = p->left;
        p->left = q->right;
        q->right = p;
        FixHeight(p);
        FixHeight(q);
        return q;
    }

}

template <class T>
AVLNode<T>* AVLTree<T>::RotateLeft(AVLNode<T>* q) // левый поворот вокруг q
{   rotations++;
    if(q==root){
        AVLNode<T>* p = q->right;
        q->right = p->left;
        p->left = q;
        FixHeight(q);
        FixHeight(p);
        return root = p;
    } else {
        AVLNode<T>* p = q->right;
        q->right = p->left;
        p->left = q;
        FixHeight(q);
        FixHeight(p);
        return p;
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::Balance(AVLNode<T>* p) // балансировка узла p
{
    FixHeight(p);
    if( BFactor(p) == 2 )
    {
        if( BFactor(p->right) < 0 ) {
            p->right = RotateRight(p->right);
        }
        return RotateLeft(p);
    }
    if( BFactor(p) == -2 )
    {
        if( BFactor(p->left) > 0  ){
            p->left = RotateLeft(p->left);
        }
        return RotateRight(p);
    }
    return p; // балансировка не нужна
}

template <class T>
AVLNode<T>* AVLTree<T>::InsertHelper(AVLNode<T>* p, const T& k){ // вставка ключа k в дерево с корнем p
    if( !p ) {
        auto temp_node = new AVLNode<T>(k);
        if(root == nullptr){root = temp_node;}
        return temp_node;
    }
    if( k<p->key )
        p->left = InsertHelper(p->left,k);
    else if (k>p->key)
        p->right = InsertHelper(p->right,k);
    return Balance(p);
}

template <class T>
void AVLTree<T>::Insert(const T& k){ // вставка ключа k в дерево с корнем p
    InsertHelper(root, k);
}

template <class T>
bool AVLTree<T>::FindHelper(AVLNode<T>* p, const T& k){
    if( !p ) return false;
    if( k<p->key )
        return FindHelper(p->left, k);
    else if (k>p->key)
        return FindHelper(p->right, k);
    else return true;
}

template <class T>
bool AVLTree<T>::Find(const T& k){
    return FindHelper(root, k);
}

template <class T>
AVLNode<T>* AVLTree<T>::FindMin(AVLNode<T>* p){ // поиск узла с минимальным ключом в дереве p
    return p->left?FindMin(p->left):p;
}

template <class T>
AVLNode<T>* AVLTree<T>::RemoveMin(AVLNode<T>* p){ // удаление узла с минимальным ключом из дерева p
    if( p->left == nullptr )
        return p->right;
    p->left = RemoveMin(p->left);
    return Balance(p);
}

template <class T>
AVLNode<T>* AVLTree<T>::DeleteHelper(AVLNode<T>* p, const T& k){ // удаление ключа k из дерева p{
    if( !p ) return nullptr;
    if( k < p->key )
        p->left = DeleteHelper(p->left, k);
    else if( k > p->key )
        p->right = DeleteHelper(p->right, k);
    else //  k == p->key
    {
        AVLNode<T>* q = p->left;
        AVLNode<T>* r = p->right;
        if (p==root) {
            if( !r ) {
                delete p;
                return root = q;
            }
            delete p;
            AVLNode<T>* min = FindMin(r);
            min->right = RemoveMin(r);
            min->left = q;
            root = min;
            return Balance(root);
        } else {
            if( !r ) {
                delete p;
                return q;
            }
            delete p;
            AVLNode<T>* min = FindMin(r);
            min->right = RemoveMin(r);
            min->left = q;
            return Balance(min);
        }
    }
    return Balance(p);
}

template <class T>
void AVLTree<T>::Delete(const T& k){
    DeleteHelper(root, k);
}

template <class T>
void AVLTree<T>::PreOrderTraversalHelper(AVLNode<T>* p) {
    if (p) {
        std::cout<<p->key<<' ';
        PreOrderTraversalHelper(p->left);
        PreOrderTraversalHelper(p->right);
    }
}

template <class T>
void AVLTree<T>::PreOrderTraversal(){
    PreOrderTraversalHelper(root);
}



template class AVLTree<int>;