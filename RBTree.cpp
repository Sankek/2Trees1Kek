#include "RBTree.h"
#include "Node.h"

enum class Color{
    BLACK,
    RED
};

struct RBNode : public Node{
    Color color{};
};

using NodePtr = RBNode*;


