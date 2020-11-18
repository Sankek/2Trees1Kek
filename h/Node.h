#ifndef NODE_H
#define NODE_H

#include <cstdint>

struct Node {
    int_fast32_t data{};
    Node *parent{nullptr};
    Node *left{nullptr};
    Node *right{nullptr};
};


#endif //NODE_H