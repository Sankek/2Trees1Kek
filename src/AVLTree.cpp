#include <iostream>

#include "AVLTree.h"
#include "AVLNode.h"


int32_t AVLTree::get_rotations(){
    return rotations;
}

void AVLTree::null_rotations(){
    rotations = 0;
}

void AVLTree::CopyHelper(AVLNode* node_copy, AVLNode* node) {
    if (node != nullptr) {
        node_copy->key = node->key;
        node_copy->height = node->height;

        if (node->left != nullptr) {
            AVLNode* node_copy_left = new AVLNode;
            node_copy->left = node_copy_left;
        }

        if (node->right != nullptr) {
            AVLNode* node_copy_right = new AVLNode;
            node_copy->right = node_copy_right;
        }

        CopyHelper(node_copy->left, node->left);
        CopyHelper(node_copy->right, node->right);
    }
}

AVLTree::AVLTree(const AVLTree &tree){
    root = new AVLNode;
    CopyHelper(root, tree.root);
}

AVLTree& AVLTree::operator=(const AVLTree &tree){
    // self-assignment guard
    if (this == &tree)
        return *this;

    // do the copy
    Destroy(root);
    root = new AVLNode;
    CopyHelper(root, tree.root);

    return *this;
}


void AVLTree::Destroy(AVLNode* node){
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




unsigned char AVLTree::get_height(AVLNode* p){
    return p ? p->height : 0;
}



int32_t AVLTree::BFactor(AVLNode* p){
    return get_height(p->right)-get_height(p->left); // разница высот левого и правого поддеревьев (Balance factor)
}

void AVLTree::FixHeight(AVLNode* p)
{
    unsigned char hl = get_height(p->left);
    unsigned char hr = get_height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}
AVLNode* AVLTree::RotateRight(AVLNode* p) // правый поворот вокруг p
{   rotations++;
    if (p==root){
        AVLNode* q = p->left;
        p->left = q->right;
        q->right = p;
        FixHeight(p);
        FixHeight(q);
        return root=q;
    } else {
        AVLNode* q = p->left;
        p->left = q->right;
        q->right = p;
        FixHeight(p);
        FixHeight(q);
        return q;
    }

}

AVLNode* AVLTree::RotateLeft(AVLNode* q) // левый поворот вокруг q
{   rotations++;
    if(q==root){
        AVLNode* p = q->right;
        q->right = p->left;
        p->left = q;
        FixHeight(q);
        FixHeight(p);
        return root = p;
    } else {
        AVLNode* p = q->right;
        q->right = p->left;
        p->left = q;
        FixHeight(q);
        FixHeight(p);
        return p;
    }
}

AVLNode* AVLTree::Balance(AVLNode* p) // балансировка узла p
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

AVLNode* AVLTree::InsertHelper(AVLNode* p, int k) // вставка ключа k в дерево с корнем p
{
    if( !p ) {
        AVLNode* temp_node = new AVLNode(k);
        if(root == nullptr){root = temp_node;}
        return temp_node;
    }
    if( k<p->key )
        p->left = InsertHelper(p->left,k);
    else if (k>p->key)
        p->right = InsertHelper(p->right,k);
    return Balance(p);
}

void AVLTree::Insert(const int& k) // вставка ключа k в дерево с корнем p
{
    InsertHelper(root, k);
}

bool AVLTree::FindHelper(AVLNode* p, int k){
    if( !p ) return 0;
    if( k<p->key )
        return FindHelper(p->left, k);
    else if (k>p->key)
        return FindHelper(p->right, k);
    else return 1;
}

bool AVLTree::Find(const int& k){
    return FindHelper(root, k);
}

AVLNode* AVLTree::FindMin(AVLNode* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?FindMin(p->left):p;
}

AVLNode* AVLTree::RemoveMin(AVLNode* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==0 )
        return p->right;
    p->left = RemoveMin(p->left);
    return Balance(p);
}

AVLNode* AVLTree::DeleteHelper(AVLNode* p, int k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = DeleteHelper(p->left, k);
    else if( k > p->key )
        p->right = DeleteHelper(p->right, k);
    else //  k == p->key
    {
        AVLNode* q = p->left;
        AVLNode* r = p->right;
        if (p==root) {
            if( !r ) {
                delete p;
                return root = q;
            }
            delete p;
            AVLNode* min = FindMin(r);
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
            AVLNode* min = FindMin(r);
            min->right = RemoveMin(r);
            min->left = q;
            return Balance(min);
        }
    }
    return Balance(p);
}
void AVLTree::Delete(const int& k){
    DeleteHelper(root, k);
}

void AVLTree::PreOrderTraversalHelper(AVLNode* p) {
    if (p) {
        std::cout<<p->key<<' ';
        PreOrderTraversalHelper(p->left);
        PreOrderTraversalHelper(p->right);
    }
}
void AVLTree::PreOrderTraversal(){
    PreOrderTraversalHelper(root);
}
