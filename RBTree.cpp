#include <iostream>

#include "RBTree.h"


using NodePtr = RBNode*;

void RBTree::PrettyPrint() {
    if (root) {
        PrintHelper(root, "", true);
    }
}

void RBTree::PrintHelper(NodePtr start_node, std::string indent, bool last){
    if (start_node != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "     ";
        } else {
            std::cout<<"L----";
            indent += "|    ";
        }

        std::string color_str;
        if (start_node->color == Color::RED){
            color_str = "RED";
        } else {
            color_str = "BLACK";
        }
        std::cout << start_node->data << "(" << color_str << ")" << '\n';
        PrintHelper(start_node->left, indent, false);
        PrintHelper(start_node->right, indent, true);
    }
}

void RBTree::CopyHelper(NodePtr node_copy, NodePtr node) {
    if (node != nullptr) {
        node_copy->data = node->data;
        node_copy->color = node->color;

        if (node->left != nullptr) {
            NodePtr node_copy_left = new RBNode;
            node_copy_left->parent = node_copy;
            node_copy->left = node_copy_left;
        }

        if (node->right != nullptr) {
            NodePtr node_copy_right = new RBNode;
            node_copy_right->parent = node_copy;
            node_copy->right = node_copy_right;
        }

        CopyHelper(node_copy->left, node->left);
        CopyHelper(node_copy->right, node->right);
    }
}

RBTree::RBTree(const RBTree &tree){
    root = new RBNode;
    CopyHelper(root, tree.root);
    }

RBTree& RBTree::operator=(const RBTree &tree){
    // self-assignment guard
    if (this == &tree)
        return *this;

    // do the copy
    Destroy(root);
    root = new RBNode;
    CopyHelper(root, tree.root);

    return *this;
}

void RBTree::Destroy(NodePtr node){
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

bool RBTree::FindHelper(const Int_t &value, NodePtr start_node) {
    if (start_node != nullptr){
        if(value == start_node->data){
            return true;
        }
        if(value < start_node->data){
            return FindHelper(value, start_node->left);
        } else {
            return FindHelper(value, start_node->right);
        }
    } else {
        return false;
    }
}

NodePtr RBTree::Grandparent(NodePtr node) {
    if ((node != nullptr) && (node->parent != nullptr))
        return node->parent->parent;
    else
        return nullptr;
}

NodePtr RBTree::Uncle(NodePtr node) {
    NodePtr gparent = Grandparent(node);
    if (gparent == nullptr){
        return nullptr;
    }
    if (node->parent == gparent->left){
        return gparent->right;
    }
    else
        return gparent->left;
}

NodePtr RBTree::Sibling(NodePtr node){
    if (node == node->parent->left)
        return node->parent->right;
    else
        return node->parent->left;
}

void RBTree::RotateLeft(NodePtr node) {
    NodePtr pivot = node->right;

    pivot->parent = node->parent;
    if (node->parent != nullptr) {
        if (node->parent->left==node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    }

    node->right = pivot->left;
    if (pivot->left != nullptr)
        pivot->left->parent = node;

    node->parent = pivot;
    pivot->left = node;
}

void RBTree::RotateRight(NodePtr node) {
    NodePtr pivot = node->left;

    pivot->parent = node->parent;
    if (node->parent != nullptr) {
        if (node->parent->left==node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    }

    node->left = pivot->right;
    if (pivot->right != nullptr)
        pivot->right->parent = node;

    node->parent = pivot;
    pivot->right = node;
}

NodePtr RBTree::Minimum(NodePtr start_node) {
    if (start_node->left){
        return Minimum(start_node->left);
    } else {
        return start_node;
    }
}

void RBTree::InsertHelper(const Int_t &value) {
    NodePtr node_parent{};
    NodePtr x = root;
    while (x != nullptr) {
        node_parent = x;
        if (value < x->data) {
            x = x->left;
        } else if (value > x->data){
            x = x->right;
        } else { // repetitions are skipped
            return;
        }
    }
    NodePtr node = new RBNode;
    node->data = value;
    node->color = Color::RED;

    node->parent = node_parent;
    if (node_parent == nullptr) {
        root = node;
    } else if (node->data < node_parent->data) {
        node_parent->left = node;
    } else {
        node_parent->right = node;
    }

    InsertCase1(node);

    root = node;
    while (root->parent != nullptr){
        root = root->parent;
    }
}

void RBTree::InsertCase1(NodePtr node) {
    if (node->parent == nullptr){
        node->color = Color::BLACK;
    } else {
        InsertCase2(node);
    }
}

void RBTree::InsertCase2(NodePtr node) {
    if (node->parent->color == Color::BLACK){
        return;
    } else {
        InsertCase3(node);
    }
}

void RBTree::InsertCase3(NodePtr node) {
    NodePtr uncle = Uncle(node);
    NodePtr gparent{};

    if ((uncle != nullptr) && (uncle->color == Color::RED)) {
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        gparent = Grandparent(node);
        gparent->color = Color::RED;
        InsertCase1(gparent);
    } else {
        InsertCase4(node);
    }
}

void RBTree::InsertCase4(NodePtr node) {
    NodePtr parent = node->parent;
    NodePtr gparent = Grandparent(node);

    if ((node == parent->right) && (parent == gparent->left)) {
        RotateLeft(parent);
        
        node = node->left;
    } else if ((node == parent->left) && (parent == gparent->right)) {
        RotateRight(parent);
        
        node = node->right;
    }
    InsertCase5(node);
}

void RBTree::InsertCase5(NodePtr node) {
    NodePtr parent = node->parent;
    NodePtr gparent = Grandparent(node);

    if (node == parent->left) {
        RotateRight(gparent);
    } else {
        RotateLeft(gparent);
    }
    parent->color = Color::BLACK;
    gparent->color = Color::RED;
}


void RBTree::DeleteHelper(const Int_t &value, NodePtr start_node) {
    if (start_node == nullptr){
        return;
    }

    if (value > start_node->data){
        if (start_node->right){
            DeleteHelper(value, start_node->right);
        } else {
            return;
        }
    } else if (value < start_node->data){
        if (start_node->left){
            DeleteHelper(value, start_node->left);
        } else {
            return;
        }
    } else { // value == data in start node
        if ((start_node->left == nullptr) && (start_node->right == nullptr)){
            if (start_node->parent){
                if (start_node->parent->data > value){
                    start_node->parent->left = nullptr;
                } else {
                    start_node->parent->right = nullptr;
                }
            }
            delete start_node;
        } else if (start_node->right == nullptr){
            NodePtr del_node = start_node->left;
            start_node->data = del_node->data;
            start_node->right = del_node->right;
            start_node->left = del_node->left;
            delete del_node;
        } else if (start_node->left == nullptr){
            NodePtr del_node = start_node->right;
            start_node->data = del_node->data;
            start_node->right = del_node->right;
            start_node->left = del_node->left;
            delete del_node;
        } else {
            // in this case start_node has 2 subtrees,
            // we find min element in the right subtree and
            // copy data from there to start_node, delete min element
            // and check the right subtree of the min element
            NodePtr r_min = Minimum(start_node->right);
            start_node->data = r_min->data;
            start_node->right = r_min->right;
            if (r_min->right){
                r_min->right->parent = start_node;
            }
            delete r_min;
        }
    }
}

void RBTree::DeleteCase1(NodePtr node) {
    if (node->parent != nullptr){
        DeleteCase2(node);
    }
}

void RBTree::DeleteCase2(NodePtr node) {
    NodePtr s = Sibling(node);

    if (s->color == Color::RED) {
        node->parent->color = Color::RED;
        s->color = Color::BLACK;
        if (node == node->parent->left)
            RotateLeft(node->parent);
        else
            RotateRight(node->parent);
    }
    DeleteCase3(node);
}

void RBTree::DeleteCase3(NodePtr node) {
    NodePtr s = Sibling(node);

    if ((node->parent->color == Color::BLACK) &&
        (s->color == Color::BLACK) &&
        (s->left->color == Color::BLACK) &&
        (s->right->color == Color::BLACK)) {
        s->color = Color::RED;
        DeleteCase1(node->parent);
    } else
        DeleteCase4(node);
}

void RBTree::DeleteCase4(NodePtr node) {
    NodePtr s = Sibling(node);

    if ((node->parent->color == Color::RED) &&
        (s->color == Color::BLACK) &&
        (s->left->color == Color::BLACK) &&
        (s->right->color == Color::BLACK)) {
        s->color = Color::RED;
        node->parent->color = Color::BLACK;
    } else
        DeleteCase5(node);
}

void RBTree::DeleteCase5(NodePtr node) {
    NodePtr s = Sibling(node);

    if  (s->color == Color::BLACK) {
        if ((node == node->parent->left) &&
            (s->right->color == Color::BLACK) &&
            (s->left->color == Color::RED)) {
            s->color = Color::RED;
            s->left->color = Color::BLACK;
            RotateRight(s);
        } else if ((node == node->parent->right) &&
                   (s->left->color == Color::BLACK) &&
                   (s->right->color == Color::RED)) {
            s->color = Color::RED;
            s->right->color = Color::BLACK;
            RotateLeft(s);
        }
    }
    DeleteCase6(node);
}

void RBTree::DeleteCase6(NodePtr node) {
    NodePtr s = Sibling(node);

    s->color = node->parent->color;
    node->parent->color = Color::BLACK;

    if (node == node->parent->left) {
        s->right->color = Color::BLACK;
        RotateLeft(node->parent);
    } else {
        s->left->color = Color::BLACK;
        RotateRight(node->parent);
    }
}

