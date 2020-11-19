
#ifndef AVLTREE_H
#define AVLTREE_H

#include "ITree.h"
#include "AVLNode.h"



class AVLTree : public ITree {
private:
    AVLNode* root{};
    int32_t rotations = 0;

    void Destroy(AVLNode* node);
    void FixHeight(AVLNode* p);
    bool FindHelper(AVLNode* p, int k);
    AVLNode* RotateRight(AVLNode* p); // правый поворот вокруг p
    AVLNode* RotateLeft(AVLNode* q); // левый поворот вокруг q
    AVLNode* InsertHelper(AVLNode* p, int k); // вставка ключа k в дерево с корнем p
    void CopyHelper(AVLNode* node_copy, AVLNode* node);
    int32_t BFactor(AVLNode* p);
    AVLNode* Balance(AVLNode* p); // балансировка узла p
    AVLNode* FindMin(AVLNode* p); // поиск узла с минимальным ключом в дереве p
    AVLNode* RemoveMin(AVLNode* p); // удаление узла с минимальным ключом из дерева p
    AVLNode* DeleteHelper(AVLNode* p, int k); // удаление ключа k из дерева p
public:
    AVLTree() = default;
    AVLTree(const AVLTree &tree);
    AVLTree& operator=(const AVLTree &tree);
    ~AVLTree() override{ Destroy(root); }
    int32_t get_rotations();

    void null_rotations();
    unsigned char get_height(AVLNode* p);

    void Insert(const int& k) override; // вставка ключа k в дерево с корнем p
    bool Find(const int& k) override;
    void Delete(const int& k) override;
    void PreOrderTraversalHelper(AVLNode* p);
    void PreOrderTraversal();
};


#endif //UNTITLED20_AVLTREE_H
