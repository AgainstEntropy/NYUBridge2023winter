/*
INSTRUCTIONS
In this assignment, it is required that you fill out areas under comments labeled as "TODO" appropriately based on the accompanying directions. 
You are also required to follow any directions accompanying comments such as "NOTE".
You can add/modify code anywhere, with the exception of the provided "main" (which we will use for testing).
You can use the constants RED and BLACK, instead of the ints 0 and 1, when appropriate.
*/

#include <iostream>
#include <math.h> // for asserting height
#include <cassert>
// #include <queue>

using namespace std;

#define RED 0
#define BLACK 1

template <class T>
class RBT;

// swapColor swaps the color from red to black and vice versa
int swapColor(int c) {
    return 1 - c;
}

template <class T>
class RBTNode {
    RBTNode<T> *parent, *left, *right;
    T data;
    int color;

public:
    RBTNode(T data)
        : data(data),
          color(RED),
          parent(nullptr),
          left(nullptr),
          right(nullptr) {}
    friend class RBT<T>;
    void prettyPrint(int indent) const;

    template <class T1>
    friend void swapColor(RBTNode<T1> *);
    template <class T1>
    friend int getColor(RBTNode<T1> *);

    int height() const;
};

template <class T>
int RBTNode<T>::height() const {
    int left_h = 0;
    if (left != nullptr) {
        left_h = left->height();
    }
    int right_h = 0;
    if (right != nullptr) {
        right_h = right->height();
    }
    return 1 + max(left_h, right_h);
}

template <class T>
void RBTNode<T>::prettyPrint(int indent) const {
    if (right != nullptr) {
        right->prettyPrint(indent + 1);
    }
    int margin = indent * 2;
    for (int i = 0; i < margin; ++i) {
        cout << '\t';
    }
    cout << "DATA: " << data << endl;
    for (int i = 0; i < margin; ++i) {
        cout << '\t';
    }
    cout << "COLOR: " << (color == RED ? "RED" : "BLACK") << endl;
    if (left != nullptr) {
        left->prettyPrint(indent + 1);
    }
}

template <class T>
void swapColor(RBTNode<T> *node) {
    if (node != nullptr) {
        node->color = swapColor(node->color);
    }
}

// getColor handles null nodes
template <class T>
int getColor(RBTNode<T> *node) {
    if (node != nullptr) {
        return node->color;
    }
    return BLACK;
}

template <class T>
class RBT {
    RBTNode<T> *root;
    void singleCCR(RBTNode<T> *&node); // Counter Clock-wise Rotation
    void doubleCR(RBTNode<T> *&node);
    void singleCR(RBTNode<T> *&node);  // Clock-wise Rotation
    void doubleCCR(RBTNode<T> *&node);

public:
    RBT() : root(nullptr) {}

    void insert(const T &);
    void insert(const T &, RBTNode<T> *&node, RBTNode<T> *parent);
    void prettyPrint() const { 
        root->prettyPrint(0); 
        // cout << "----------------------------------------------------------------------------------\n"; 
    }

    int height() const { return root->height(); }

    bool isBlack(RBTNode<T> *node) const { return node == nullptr || node->color == BLACK; }
    bool isLeft(RBTNode<T> *node) const { return node == node->parent->left; }

    void fix(RBTNode<T> *curr);
};

template <class T>
void RBT<T>::doubleCCR(RBTNode<T> *&node) {
    singleCR(node->right);
    singleCCR(node);
}

template <class T>
void RBT<T>::doubleCR(RBTNode<T> *&node) {
    singleCCR(node->left);
    singleCR(node);
}

template <class T>
void RBT<T>::singleCR(RBTNode<T> *&node) {
    RBTNode<T> *child = node->left;
    // TODO: ADD ROTATION CODE HERE
    if (child->right != nullptr) {
        child->right->parent = node;
    }
    node->left = child->right;

    child->parent = node->parent;
    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    node->parent = child;
    child->right = node;
}

template <class T>
void RBT<T>::singleCCR(RBTNode<T> *&node) {
    RBTNode<T> *child = node->right;
    // TODO: ADD ROTATION CODE HERE
    if (child->left != nullptr) {
        child->left->parent = node;
    }
    node->right = child->left;

    child->parent = node->parent;
    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->right) {
        node->parent->right = child;
    } else {
        node->parent->left = child;
    }

    node->parent = child;
    child->left = node;
}

template <class T>
void RBT<T>::fix(RBTNode<T> *curr) {
    RBTNode<T> *parent = curr->parent;

    // trivial case, nothing to fix
    if (isBlack(parent)) { return; }

    RBTNode<T> *grandparent = parent->parent;
    RBTNode<T> *uncle = isLeft(parent) ? grandparent->right : grandparent->left; 

    if (isBlack(uncle)) {
        if (isLeft(curr)) {  // case 1: uncle is black and current node is the leftchild (turn it into case 2 and fix)
            curr = parent;
            singleCR(curr);
            fix(curr);
        } else {  // case 2: uncle is black and current node is the rightchild
            swapColor(parent);
            swapColor(grandparent);
            singleCCR(grandparent);
        }
    } else {  // case 3: uncle is red, transfer the conflict to grandparent and fix recursively
        swapColor(parent);
        swapColor(uncle);
        swapColor(grandparent);
        fix(grandparent); 
    }
}

template <class T>
void RBT<T>::insert(const T &toInsert, RBTNode<T> *&node, RBTNode<T> *parent) {
    if (node == nullptr) {               // leaf location is found so insert node
        node = new RBTNode<T>(toInsert); // modifies the pointer itself since *node
                                          // is passed by reference
        node->parent = parent;

        RBTNode<T> *curr_node = node; // curr_node will be set appropriately when walking up the tree
        // TODO: ADD RBT RULES HERE
        fix(curr_node);
        if (!isBlack(root)) {
            swapColor(root);
        }

    } else if (toInsert < node->data) { // recurse down the tree to left to find correct leaf location
        insert(toInsert, node->left, node);
    } else { // recurse down the tree to right to find correct leaf location
        insert(toInsert, node->right, node);
    }
}

template <class T>
void RBT<T>::insert(const T &toInsert) {
    insert(toInsert, root, nullptr);
}

// NOTE: DO NOT MODIFY THE MAIN FUNCTION BELOW
int main() {
    RBT<int> b;
    int count = 10;
    for (int i = 0; i < count; i++) {
        b.insert(i);
        // b.prettyPrint();
    }

    b.prettyPrint();
    /* EXPECTED OUTPUT:
                                                                    Data: 9
                                                                    COLOR: RED
                                                    Data: 8
                                                    COLOR: BLACK
                                    Data: 7
                                    COLOR: RED
                                                    Data: 6
                                                    COLOR: BLACK
                    Data: 5
                    COLOR: BLACK
                                    Data: 4
                                    COLOR: BLACK
    Data: 3
    COLOR: BLACK
                                    Data: 2
                                    COLOR: BLACK
                    Data: 1
                    COLOR: BLACK
                                    Data: 0
                                    COLOR: BLACK
    */

    // TEST
    // the below tests the validity of the height of the RBT
    // if the assertion fails, then your tree does not properly self-balance
    int height = b.height();
    assert(height <= 2 * log2(count));
}