#ifndef AVLTREE_H
#define AVLTREE_H

#include "ITree.h"
#include "AVLNode.h"


template <class T>
class AVLTree : public ITree<T> {
public:
    AVLTree() = default;
    AVLTree(const AVLTree &tree);
    AVLTree& operator=(const AVLTree &tree);
    ~AVLTree() override{ Destroy(root); }
    int32_t get_rotations();

    void null_rotations();
    unsigned char get_height(AVLNode<T>* p);

    void Insert(const T& k) override; // вставка ключа k в дерево с корнем p
    bool Find(const T& k) override;
    void Delete(const T& k) override;
    void PreOrderTraversalHelper(AVLNode<T>* p);
    void PreOrderTraversal();
private:
    AVLNode<T>* root{};
    int32_t rotations = 0;

    void Destroy(AVLNode<T>* node);
    void FixHeight(AVLNode<T>* p);
    bool FindHelper(AVLNode<T>* p, const T& k);
    AVLNode<T>* RotateRight(AVLNode<T>* p); // правый поворот вокруг p
    AVLNode<T>* RotateLeft(AVLNode<T>* q); // левый поворот вокруг q
    AVLNode<T>* InsertHelper(AVLNode<T>* p, const T& k); // вставка ключа k в дерево с корнем p
    void CopyHelper(AVLNode<T>* node_copy, AVLNode<T>* node);
    int32_t BFactor(AVLNode<T>* p);
    AVLNode<T>* Balance(AVLNode<T>* p); // балансировка узла p
    AVLNode<T>* FindMin(AVLNode<T>* p); // поиск узла с минимальным ключом в дереве p
    AVLNode<T>* RemoveMin(AVLNode<T>* p); // удаление узла с минимальным ключом из дерева p
    AVLNode<T>* DeleteHelper(AVLNode<T>* p, const T& k); // удаление ключа k из дерева p
};

#endif //AVLTREE_H
