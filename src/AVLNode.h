//
// Created by user on 19.11.2020.
//

#ifndef AVLNODE_H
#define AVLNODE_H
#include <cstdint>

struct AVLNode{
    int key{};
    int height{1};
    AVLNode* left{};
    AVLNode* right{};
    AVLNode() {}
    AVLNode(int k) { key = k; }

};


#endif //UNTITLED20_AVLNODE_H
