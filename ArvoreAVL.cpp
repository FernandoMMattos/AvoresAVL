#include <iostream>
#include <algorithm>
#include <locale>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// Obter a altura de um nó
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Atualizar a altura de um nó
void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Obter o fator de balanceamento
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Rotação à direita
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Rotação à esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Inserir um nó na árvore AVL
Node* insertAVL(Node* node, int key) {
    if (!node)
        return new Node(key);
    
    if (key < node->data)
        node->left = insertAVL(node->left, key);
    else if (key > node->data)
        node->right = insertAVL(node->right, key);
    else // Não permitir duplicatas
        return node;

    updateHeight(node);
    int balance = getBalance(node);

    // Rotação LL
    if (balance > 1 && key < node->left->data)
        return rotateRight(node);

    // Rotação RR
    if (balance < -1 && key > node->right->data)
        return rotateLeft(node);

    // Rotação LR
    if (balance > 1 && key > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Rotação RL
    if (balance < -1 && key < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inserir um nó na árvore binária de busca
Node* insertBST(Node* node, int key) {
    if (!node)
        return new Node(key);
    
    if (key < node->data)
        node->left = insertBST(node->left, key);
    else if (key > node->data)
        node->right = insertBST(node->right, key);
    // Não permitir duplicatas em BST também

    return node;
}

// Busca em uma árvore
bool search(Node* root, int key) {
    if (!root)
        return false;
    if (root->data == key)
        return true;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Imprimir a árvore em ordem
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// Liberar a memória da árvore
void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    vector<int> values1 = {10, 20, 30, 40, 50};
    vector<int> values2 = {50, 40, 30, 20, 10};
    vector<int> values3 = {30, 10, 50, 20, 40, 70};

    Node* rootBST1 = nullptr;
    Node* rootAVL1 = nullptr;
    Node* rootBST2 = nullptr;
    Node* rootAVL2 = nullptr;
    Node* rootBST3 = nullptr;
    Node* rootAVL3 = nullptr;

    // Função para inserir e imprimir árvores
    auto insertAndPrint = [](vector<int>& values, Node*& rootBST, Node*& rootAVL, const string& title) {
        cout << "Inserindo valores na BST e AVL (" << title << "): ";
        for (int val : values) {
            rootBST = insertBST(rootBST, val);
            rootAVL = insertAVL(rootAVL, val);
            cout << val << " ";
        }
        cout << endl;

        // Imprimindo as árvores em ordem
        cout << "BST em ordem: ";
        inOrder(rootBST);
        cout << "\nAVL em ordem: ";
        inOrder(rootAVL);
        cout << endl;
    };

    // Inserir e imprimir cada conjunto de valores
    insertAndPrint(values1, rootBST1, rootAVL1, "Crescente");
    insertAndPrint(values2, rootBST2, rootAVL2, "Decrescente");
    insertAndPrint(values3, rootBST3, rootAVL3, "Aleatório");

    // Busca por elementos
    vector<int> searchKeys = {20, 60};
    for (int key : searchKeys) {
        cout << "Busca na BST 1 por " << key << ": " << (search(rootBST1, key) ? "Encontrado" : "Não encontrado") << endl;
        cout << "Busca na AVL 1 por " << key << ": " << (search(rootAVL1, key) ? "Encontrado" : "Não encontrado") << endl;

        cout << "Busca na BST 2 por " << key << ": " << (search(rootBST2, key) ? "Encontrado" : "Não encontrado") << endl;
        cout << "Busca na AVL 2 por " << key << ": " << (search(rootAVL2, key) ? "Encontrado" : "Não encontrado") << endl;

        cout << "Busca na BST 3 por " << key << ": " << (search(rootBST3, key) ? "Encontrado" : "Não encontrado") << endl;
        cout << "Busca na AVL 3 por " << key << ": " << (search(rootAVL3, key) ? "Encontrado" : "Não encontrado") << endl;
    }

    // Libera a memória alocada
    deleteTree(rootBST1);
    deleteTree(rootAVL1);
    deleteTree(rootBST2);
    deleteTree(rootAVL2);
    deleteTree(rootBST3);
    deleteTree(rootAVL3);

    return 0;
}
