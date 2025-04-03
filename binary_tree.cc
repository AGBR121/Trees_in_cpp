#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;

template<typename T>
class BST {
    private:
    class Node{
        private:
        T element_;
        Node* left_;
        Node* right_;

        public:
        Node(){
            element_ = T();
            left_ = nullptr;
            right_ = nullptr;
        }

        Node(const T& data){
            element_ = data;
            left_ = nullptr;
            right_ = nullptr;
        }

        //Getter and setter of the Node class
        T getElement() const { return element_; }
        void setElement(const T& element) { element_ = element; }

        Node* getLeft() const { return left_; }
        void setLeft(Node* left) { left_ = left; }

        Node* getRight() const { return right_; }
        void setRight(Node* right) { right_ = right; }
    };

    Node* root;


    Node* insert(Node* node, T value){
        if(!node){ return new Node(value); } //If the value isn't in the tree, we add it

        if(node->getElement() == value){return node;} //Else, we don't add it

        if (value < node->getElement()) {
            node->setLeft(insert(node->getLeft(), value));
        } else if (value > node->getElement()) {
            node->setRight(insert(node->getRight(), value));
        }
        return node; //Return the node and we don't change the tree
    }

    //Left-Root-Right
    void inorder(Node* node){
        if(node != nullptr){
            inorder(node->getLeft());
            cout << node->getElement()<< " ";
            inorder(node->getRight());
        }
    }

    //Root-Left-Right
    void preorder(Node* node){
        if(node != nullptr){
            cout << node->getElement() <<" ";
            preorder(node->getLeft());
            preorder(node->getRight());
        }
    }

    //Left-Right-Root
    void postorder(Node* node){
        if(node != nullptr){
            postorder(node->getLeft());
            postorder(node->getRight());
            cout << node->getElement() << " ";
        }
    }

    //Return true or false if the element is in the tree
    bool find(Node* node, const T& element) {
        if (node == nullptr){return false;}

        if (element == node->getElement()){ return true; }
        else if (element < node->getElement()) {
            return find(node->getLeft(), element);
        }
        else {
            return find(node->getRight(), element);
        } 
    }

    public:

    //Constructors
    BST(){ root = nullptr; }
    BST(const T& element){ root = new Node(element);}

    void insert(const T& element){ root = insert(root, element);}

    void inorder() { inorder(root); }

    void preorder() { preorder(root); }

    void postorder() { postorder(root); }

    bool find(const T& element){ find(root, element); }

};

void Prueba() {
    BST<int> tree;
    for (int i = 1; i <= 10; i++) {
        tree.insert(rand() % 100);
    }
    tree.inorder();
    cout << endl;
    tree.preorder();
    cout << endl;
    tree.postorder();
    cout << endl;
}

int main() {
    Prueba();
    return 0;
}