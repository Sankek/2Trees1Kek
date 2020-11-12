#ifndef RBNODE_H
#define RBNODE_H

#include <cstdint>

enum class Color{
    BLACK,
    RED
};

struct RBNode{
    int_fast32_t data{};
    RBNode *parent{nullptr};
    RBNode *left{nullptr};
    RBNode *right{nullptr};
    Color color{};
};


#endif //RBNODE_H
