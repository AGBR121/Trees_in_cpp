#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;

template<typename T>
class Treap {
    private:
    class Node {
        private:
        T element_;
        int priority_;
        Node* left_;
        Node* right_;

        public:
        Node() {
            element_ = T();
            priority_ = rand();
            left_ = nullptr;
            right_ = nullptr;
        }

        Node(const T& data) {
            element_ = data;
            priority_ = rand();
            left_ = nullptr;
            right_ = nullptr;
        }

        T getElement() const { return element_; }
        void setElement(const T& element) { element_ = element; }

        int getPriority() const { return priority_; }
        void setPriority(int priority) { priority_ = priority; }

        Node* getLeft() const { return left_; }
        void setLeft(Node* left) { left_ = left; }

        Node* getRight() const { return right_; }
        void setRight(Node* right) { right_ = right; }
    };

    Node* root_;
    unsigned int size_;

    void rotateRight(Node*& node) {
        Node* leftChild = node->getLeft();
        node->setLeft(leftChild->getRight());
        leftChild->setRight(node);
        node = leftChild;
    }

    void rotateLeft(Node*& node) {
        Node* rightChild = node->getRight();
        node->setRight(rightChild->getLeft());
        rightChild->setLeft(node);
        node = rightChild;
    }

    void preorder(Node* node) {
        if (node) {
            cout << node->getElement() << " ";
            preorder(node->getLeft());
            preorder(node->getRight());
        }
    }

    void postorder(Node* node) {
        if (node) {
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

    

};