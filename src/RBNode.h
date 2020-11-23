#ifndef RBNODE_H
#define RBNODE_H

#include <cstdint>

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
};


#endif //RBNODE_H
