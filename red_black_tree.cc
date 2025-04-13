#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;

template<typename T>
class RBT {
private:
    class Node {
        T element_;
        bool color; // Red = 1, Black = 0
        Node* left_;
        Node* right_;
        Node* parent_;
    public:
        Node() {
            element_ = T();
            left_ = nullptr;
            right_ = nullptr;
            parent_ = nullptr;
            color = 1;
        }

        Node(const T& data) {
            element_ = data;
            left_ = nullptr;
            right_ = nullptr;
            parent_ = nullptr;
            color = 1;
        }

        T getElement() const { return element_; }
        void setElement(const T& element) { element_ = element; }

        Node* getLeft() const { return left_; }
        void setLeft(Node* left) { left_ = left; }

        Node* getRight() const { return right_; }
        void setRight(Node* right) { right_ = right; }

        Node* getParent() const { return parent_; }
        void setParent(Node* parent) { parent_ = parent; }

        bool isRed() const { return color; }
        void setColor(bool c) { color = c; }
    };

    Node* root_;
    unsigned int size_ = 0;

    void leftRotate(Node* x) {
        Node* y = x->getRight();
        x->setRight(y->getLeft());
        if (y->getLeft() != nullptr) {
            y->getLeft()->setParent(x);
        }
        y->setParent(x->getParent());
        if (x->getParent() == nullptr) {
            root_ = y;
        } else if (x == x->getParent()->getLeft()) {
            x->getParent()->setLeft(y);
        } else {
            x->getParent()->setRight(y);
        }
        y->setLeft(x);
        x->setParent(y);
    }

    void rightRotate(Node* x) {
        Node* y = x->getLeft();
        x->setLeft(y->getRight());
        if (y->getRight() != nullptr) {
            y->getRight()->setParent(x);
        }
        y->setParent(x->getParent());
        if (x->getParent() == nullptr) {
            root_ = y;
        } else if (x == x->getParent()->getRight()) {
            x->getParent()->setRight(y);
        } else {
            x->getParent()->setLeft(y);
        }
        y->setRight(x);
        x->setParent(y);
    }

    void fixInsert(Node* z) {
        while (z->getParent() != nullptr && z->getParent()->isRed()) {
            Node* parent = z->getParent();
            Node* grandparent = parent->getParent();

            if (parent == grandparent->getLeft()) {
                Node* uncle = grandparent->getRight();
                if (uncle != nullptr && uncle->isRed()) {
                    parent->setColor(0);
                    uncle->setColor(0);
                    grandparent->setColor(1);
                    z = grandparent;
                } else {
                    if (z == parent->getRight()) {
                        z = parent;
                        leftRotate(z);
                    }
                    z->getParent()->setColor(0);
                    grandparent->setColor(1);
                    rightRotate(grandparent);
                }
            } else {
                Node* uncle = grandparent->getLeft();
                if (uncle != nullptr && uncle->isRed()) {
                    parent->setColor(0);
                    uncle->setColor(0);
                    grandparent->setColor(1);
                    z = grandparent;
                } else {
                    if (z == parent->getLeft()) {
                        z = parent;
                        rightRotate(z);
                    }
                    z->getParent()->setColor(0);
                    grandparent->setColor(1);
                    leftRotate(grandparent);
                }
            }
        }
        root_->setColor(0);
    }

    void transplant(Node* u, Node* v) {
        if (u->getParent() == nullptr) {
            root_ = v;
        } else if (u == u->getParent()->getLeft()) {
            u->getParent()->setLeft(v);
        } else {
            u->getParent()->setRight(v);
        }
        if (v != nullptr) {
            v->setParent(u->getParent());
        }
    }

    Node* minimum(Node* node) const {
        while (node->getLeft() != nullptr) {
            node = node->getLeft();
        }
        return node;
    }

    void fixDelete(Node* x) {
        while (x != root_ && (x == nullptr || !x->isRed())) {
            Node* parent = x ? x->getParent() : nullptr;
            if (parent == nullptr) break;

            if (x == parent->getLeft()) {
                Node* w = parent->getRight();
                if (w && w->isRed()) {
                    w->setColor(0);
                    parent->setColor(1);
                    leftRotate(parent);
                    w = parent->getRight();
                }

                if ((w->getLeft() == nullptr || !w->getLeft()->isRed()) &&
                    (w->getRight() == nullptr || !w->getRight()->isRed())) {
                    w->setColor(1);
                    x = parent;
                } else {
                    if (w->getRight() == nullptr || !w->getRight()->isRed()) {
                        if (w->getLeft()) w->getLeft()->setColor(0);
                        w->setColor(1);
                        rightRotate(w);
                        w = parent->getRight();
                    }
                    w->setColor(parent->isRed());
                    parent->setColor(0);
                    if (w->getRight()) w->getRight()->setColor(0);
                    leftRotate(parent);
                    x = root_;
                }
            } else {
                Node* w = parent->getLeft();
                if (w && w->isRed()) {
                    w->setColor(0);
                    parent->setColor(1);
                    rightRotate(parent);
                    w = parent->getLeft();
                }

                if ((w->getLeft() == nullptr || !w->getLeft()->isRed()) &&
                    (w->getRight() == nullptr || !w->getRight()->isRed())) {
                    w->setColor(1);
                    x = parent;
                } else {
                    if (w->getLeft() == nullptr || !w->getLeft()->isRed()) {
                        if (w->getRight()) w->getRight()->setColor(0);
                        w->setColor(1);
                        leftRotate(w);
                        w = parent->getLeft();
                    }
                    w->setColor(parent->isRed());
                    parent->setColor(0);
                    if (w->getLeft()) w->getLeft()->setColor(0);
                    rightRotate(parent);
                    x = root_;
                }
            }
        }

        if (x != nullptr)
            x->setColor(0);
    }

    void deleteNode(Node* z) {
        Node* y = z;
        bool yOriginalColor = y->isRed();
        Node* x;

        if (z->getLeft() == nullptr) {
            x = z->getRight();
            transplant(z, z->getRight());
        } else if (z->getRight() == nullptr) {
            x = z->getLeft();
            transplant(z, z->getLeft());
        } else {
            y = minimum(z->getRight());
            yOriginalColor = y->isRed();
            x = y->getRight();
            if (y->getParent() == z) {
                if (x != nullptr)
                    x->setParent(y);
            } else {
                transplant(y, y->getRight());
                y->setRight(z->getRight());
                if (y->getRight())
                    y->getRight()->setParent(y);
            }
            transplant(z, y);
            y->setLeft(z->getLeft());
            if (y->getLeft())
                y->getLeft()->setParent(y);
            y->setColor(z->isRed());
        }

        delete z;

        if (!yOriginalColor && x != nullptr) {
            fixDelete(x);
        }
    }

    void inorder(Node* node) const {
        assert(root_ != nullptr);
        if (node != nullptr) {
            inorder(node->getLeft());
            cout << node->getElement() << " ";
            inorder(node->getRight());
        }
    }

    void preorder(Node* node) const {
        assert(root_ != nullptr);
        if (node != nullptr) {
            cout << node->getElement() << " ";
            preorder(node->getLeft());
            preorder(node->getRight());
        }
    }

    void postorder(Node* node) const {
        assert(root_ != nullptr);
        if (node != nullptr) {
            postorder(node->getLeft());
            postorder(node->getRight());
            cout << node->getElement() << " ";
        }
    }

    bool find(Node* node, const T& element) {
        if (!node) return false;
        if (element == node->getElement()) return true;
        return element < node->getElement() ? find(node->getLeft(), element) : find(node->getRight(), element);
    }

    void delete_node(const T& value){
        Node* z = root_;
        while (z != nullptr) {
            if (value == z->getElement()) {
                break;
            } else if (value < z->getElement()) {
                z = z->getLeft();
            } else {
                z = z->getRight();
            }
        }

        if (z == nullptr) return;
        deleteNode(z);
        size_--;
    }

    void add_node(const T& data){
        Node* z = new Node(data);
        Node* y = nullptr;
        Node* x = root_;

        while (x != nullptr) {
            y = x;
            if (z->getElement() < x->getElement()) {
                x = x->getLeft();
            } else {
                x = x->getRight();
            }
        }

        z->setParent(y);
        if (y == nullptr) {
            root_ = z;
        } else if (z->getElement() < y->getElement()) {
            y->setLeft(z);
        } else {
            y->setRight(z);
        }

        fixInsert(z);
        size_++;
    }

public:
    RBT() { root_ = nullptr; size_ = 0; }

    RBT(const T& element) {
        root_ = new Node(element);
        root_->setColor(0);
        size_ = 1;
    }

    Node* root() const { return root_; }

    void insert(const T& data) {
        if (find(data)) return; // If the element exists, don't add it
        add_node(data);
    }

    bool find(const T& value) {
        return find(root_, value);
    }

    void remove(const T& value) {
        assert(find(value)); // If the element exists, remove it
        delete_node(value);
    }

    void inorder() const { inorder(root_); }
    void preorder() const { preorder(root_); }
    void postorder() const { postorder(root_); }

    unsigned int size() const { return size_; }
};

void testRBT() {
    RBT<int> tree;
    srand(time(nullptr));
    for (int i = 1; i <= 10; i++) {
        tree.insert(rand() % 50);
        tree.insert(i);
    }

    cout << "Root: " << tree.root()->getElement() << endl;
    cout << "Inorder:" << endl;
    tree.inorder();
    cout << endl;
    cout << "Preorder:" << endl;
    tree.preorder();
    cout << endl;
    cout << "Postorder:" << endl;
    tree.postorder();
    cout << endl;
    cout << "Size:" << endl;
    cout << tree.size() << endl;

    tree.remove(2);
    cout << "Delete number 2" << endl;
    cout << "Inorder:" << endl;
    tree.inorder();
    cout << endl;
    cout << "Size:" << endl;
    cout << tree.size() << endl;
}

int main() {
    testRBT();
    return 0;
}
