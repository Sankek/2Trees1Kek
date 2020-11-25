#include <iostream>

#include "RBTree.h"

template <class T>
void RBTree<T>::PrettyPrint() {
    if (root) {
        PrintHelper(root, "", true);
    }
}

template <class T>
void RBTree<T>::PrintHelper(NodePtr start_node, std::string indent, bool last){
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

template <class T>
RBTree<T>::RBTree(const RBTree<T> &tree){
    if (tree.root != nullptr){
        root = new RBNode<T>;
        *root = *tree.root;
    }
    rotations_count = tree.rotations_count;
}

template <class T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T> &tree){
    // self-assignment guard
    if (this == &tree)
        return *this;

    // do the copy
    if (tree.root == nullptr){
        root->~RBNode();
        delete root;
    } else {
        if (root == nullptr){
            root = new RBNode<T>;
        }
        *root = *tree.root;
    }
    rotations_count = tree.rotations_count;

    return *this;
}

template <class T>
bool RBTree<T>::FindHelper(const T &value, NodePtr node) {
    while(node != nullptr) {
        if (value < node->data) {
            node = node->left;
        } else if (value > node->data) {
            node = node->right;
        } else {
            break;
        }
    }
    return node != nullptr;
}

template <class T>
RBNode<T>* RBTree<T>::left(NodePtr n){return        (n == nullptr) ? nullptr : n->left; }
template <class T>
RBNode<T>* RBTree<T>::right(NodePtr n){return       (n == nullptr) ? nullptr : n->right; }
template <class T>
Color RBTree<T>::color(NodePtr n){return         (n == nullptr) ? Color::BLACK : Color::RED; }
template <class T>
bool RBTree<T>::is_red(NodePtr n){return         (n != nullptr) && (n->color == Color::RED); }
template <class T>
bool RBTree<T>::is_black(NodePtr n){return       (n == nullptr) || (n->color == Color::BLACK); }
template <class T>
RBNode<T>* RBTree<T>::parent(NodePtr n){return      (n == nullptr) ? nullptr : n->parent; }
template <class T>
RBNode<T>* RBTree<T>::grandparent(NodePtr n){return parent(parent(n)); }
template <class T>
RBNode<T>* RBTree<T>::brother(NodePtr n){return     (n == left(parent(n))) ? right(parent(n)) : left(parent(n)); }
template <class T>
RBNode<T>* RBTree<T>::uncle(NodePtr n){return       (parent(n)) == left(grandparent(n)) ? right(grandparent(n)) : left(grandparent(n)); }
template <class T>
RBNode<T>* RBTree<T>::leftmost(NodePtr n) { return  (left(n) == nullptr) ? n : leftmost(left(n)); }
template <class T>
RBNode<T>* RBTree<T>::rightmost(NodePtr n) { return (right(n) == nullptr) ? n : rightmost(right(n)); }


template <class T>
void RBTree<T>::RotateLeft(NodePtr node) {
    ++rotations_count;

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

template <class T>
void RBTree<T>::RotateRight(NodePtr node) {
    ++rotations_count;

    NodePtr pivot = node->left;

    pivot->parent = node->parent;
    if (node->parent != nullptr) {
        if (node->parent->left == node)
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


template <class T>
void RBTree<T>::InsertHelper(const T &value) {
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
    auto node = new RBNode<T>;
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

template <class T>
void RBTree<T>::InsertCase1(NodePtr node) {
    if (node->parent == nullptr){
        node->color = Color::BLACK;
    } else {
        InsertCase2(node);
    }
}

template <class T>
void RBTree<T>::InsertCase2(NodePtr node) {
    if (node->parent->color == Color::BLACK){
        return;
    } else {
        InsertCase3(node);
    }
}

template <class T>
void RBTree<T>::InsertCase3(NodePtr node) {
    NodePtr u = uncle(node);
    NodePtr gparent{};

    if ((u != nullptr) && (u->color == Color::RED)) {
        node->parent->color = Color::BLACK;
        u->color = Color::BLACK;
        gparent = grandparent(node);
        gparent->color = Color::RED;
        InsertCase1(gparent);
    } else {
        InsertCase4(node);
    }
}

template <class T>
void RBTree<T>::InsertCase4(NodePtr node) {
    NodePtr parent = node->parent;
    NodePtr gparent = grandparent(node);

    if ((node == parent->right) && (parent == gparent->left)) {
        RotateLeft(parent);

        node = node->left;
    } else if ((node == parent->left) && (parent == gparent->right)) {
        RotateRight(parent);

        node = node->right;
    }
    InsertCase5(node);
}

template <class T>
void RBTree<T>::InsertCase5(NodePtr node) {
    NodePtr parent = node->parent;
    NodePtr gparent = grandparent(node);

    if (node == parent->left) {
        RotateRight(gparent);
    } else {
        RotateLeft(gparent);
    }
    parent->color = Color::BLACK;
    gparent->color = Color::RED;
}


template <class T>
void RBTree<T>::DeleteHelper(const T &value, NodePtr node) {
    while(node != nullptr) {
        if (value < node->data) {
            node = node->left;
        } else if (value > node->data) {
            node = node->right;
        } else {
            break;
        }
    }
    if (node == nullptr){
        return;
    }

//    if ((node->left != nullptr) && (node->right != nullptr)){
//        NodePtr lm = leftmost(node->right);
//        node->data = lm->data;
//        node = lm;
//    }

    if ((node->left != nullptr) && (node->right != nullptr)){
        NodePtr rm = rightmost(node->left);
        node->data = rm->data;
        node = rm;
    }

    // now node has 1 or 0 children
    NodePtr child = (node->left == nullptr) ? node->right : node->left;
    if (child != nullptr){
        // node is black and child is red with no children
        node->data = child->data;
        node->left = node->right = nullptr;
        delete child;
        return;
    } else {
        if (node == root){
            root = nullptr;
            delete node;
            return;
        }
        if (is_black(node)){
            DeleteFix(node);

            root = node;
            while(root->parent != nullptr){
                root = root->parent;
            }
        }

        if (node->parent->left == node){
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
        return;
    }
}

template <class T>
void RBTree<T>::DeleteFix(NodePtr node){
    // on the first iteration
    // node that will be deleted is black with no children
    // and parent is not null

    bool node_is_right_child = (node->parent->right == node);
    NodePtr bro = brother(node);

    if (is_red(node->parent)){
        // bro is black

        if (is_black(bro->left) && is_black(bro->right)){
            node->parent->color = Color::BLACK;
            bro->color = Color::RED;
            return;
        } else {
            if (node_is_right_child && is_black(bro->left)){
                bro->right->color = Color::BLACK;
                bro->color = Color::RED;
                RotateLeft(bro);
                bro = brother(node);
                // now is_red(bro->left) is true
            }

            if (!node_is_right_child && is_black(bro->right)){ // inverse of previous
                bro->left->color = Color::BLACK;
                bro->color = Color::RED;
                RotateRight(bro);
                bro = brother(node);
                // now is_red(bro->right) is true
            }

            if (node_is_right_child && is_red(bro->left)){
                bro->left->color = Color::BLACK;
                bro->color = Color::RED;
                node->parent->color = Color::BLACK;
                RotateRight(node->parent);
                return;
            }

            if (!node_is_right_child && is_red(bro->right)){ // inverse of previous
                bro->right->color = Color::BLACK;
                bro->color = Color::RED;
                node->parent->color = Color::BLACK;
                RotateLeft(node->parent);
                return;
            }


        }


    } else {  // parent is black
        if (is_red(bro)){
            if (node_is_right_child){
                if (is_black(bro->right->left) && is_black(bro->right->right)){
                    bro->color = Color::BLACK;
                    bro->right->color = Color::RED;
                    RotateRight(node->parent);
                    return;
                } else {
                    if (is_red(bro->right->left)){
                        bro->right->left->color = Color::BLACK;
                        RotateLeft(bro);
                        RotateRight(node->parent);
                        return;
                    } else { // bro->right->left is black and bro->right->right is red
                        bro->color = Color::BLACK;
                        node->parent->color = Color::RED;
                        RotateRight(node->parent);
                        // now:
                        // is_red(node->parent) is true
                        // is_black(bro->left) is true
                        // is_red(bro->right) is true
                        DeleteFix(node);
                    }
                }
            } else { // inverse of previous statements
                if (is_black(bro->left->left) && is_black(bro->left->right)){
                    bro->color = Color::BLACK;
                    bro->left->color = Color::RED;
                    RotateLeft(node->parent);
                    return;
                } else {
                    if (is_red(bro->left->right)){
                        bro->left->right->color = Color::BLACK;
                        RotateRight(bro);
                        RotateLeft(node->parent);
                        return;
                    } else { // bro->left->right is black and bro->left->left is red
                        bro->color = Color::BLACK;
                        node->parent->color = Color::RED;
                        RotateLeft(node->parent);
                        // now:
                        // is_red(node->parent) is true
                        // is_black(bro->right) is true
                        // is_red(bro->left) is true
                        DeleteFix(node);
                    }
                }
            }
        } else { // parent and bro are black
            if (is_black(bro->left) && is_black(bro->right)){
                bro->color = Color::RED;
                if (node->parent != root){
                    DeleteFix(node->parent);
                } else {
                    return;
                }
            } else {
                if (node_is_right_child && is_red(bro->right)){
                    bro->right->color = Color::BLACK;
                    RotateLeft(bro);
                    RotateRight(node->parent);
                    return;
                }
                if (!node_is_right_child && is_red(bro->left)){ // inverse of previous
                    bro->left->color = Color::BLACK;
                    RotateRight(bro);
                    RotateLeft(node->parent);
                    return;
                }

                if (node_is_right_child && is_black(bro->right)){
                    bro->left->color = Color::BLACK;
                    RotateRight(node->parent);
                    return;
                }
                if (!node_is_right_child && is_black(bro->left)){ // inverse of previous
                    bro->right->color = Color::BLACK;
                    RotateLeft(node->parent);
                    return;
                }
            }
        }
    }
}


template class RBTree<int>;