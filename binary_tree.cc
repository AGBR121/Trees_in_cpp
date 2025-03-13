#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;

template<typename T>
class BinaryTree {
public:
    //Clase nodo
    class Node {
    private:
        T element_; //Guarda el elemento
        //Apuntará a otros dos nodos
        Node* left_; 
        Node* right_;

    public:
    //Constructores
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
    // getter y setter
    T getElement() const { return element_; }
    void setElement(const T& element) { element_ = element; }

    Node* getLeft() const { return left_; }
    void setLeft(Node* left) { left_ = left; }

    Node* getRight() const { return right_; }
    void setRight(Node* right) { right_ = right; }
    };

private:
    Node* root;
    //Funcion recursiva para insertar un dato en el arbol
    Node* insertData(Node* node, const T& element) {
        if (node == nullptr) { return new Node(element); }
    
        if (element < node->getElement()) {
            node->setLeft(insertData(node->getLeft(), element));
        } else if (element > node->getElement()) {
            node->setRight(insertData(node->getRight(), element));
        }
        return node;
    }

    //Funcion Recursiva para revisar todo el arbol
    void inOrden(Node* node) {
        if (node != nullptr) {
            inOrden(node->getLeft());
            cout << node->getElement() << " ";
            inOrden(node->getRight());
        }
    }

public:
    //Constructores 
    BinaryTree(){ root = nullptr ; }

    BinaryTree(const T& element) {
        root = new Node(element);
    }

    //Inserta un elemento en el arbol
    void insert(const T& element) {
        root = insertData(root, element);
    }

    //Imprime el arbol ordenadamente
    void Orden() {
        inOrden(root);
        cout << endl;
    }
};

//Funcion de prueba
void Prueba() {
    BinaryTree<int> tree;
    for (int i = 1; i <= 100; i++) {
        tree.insert(rand() % 100);
    }
    tree.Orden();
}

int main() {
    Prueba();
    return 0;
}
