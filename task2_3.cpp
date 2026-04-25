#include <iostream>
#include <stack>


template<typename T, typename C>
class BinaryTree {
public:
    BinaryTree(const C& _cmp) : cmp(_cmp), root(nullptr) {}
    ~BinaryTree();

    bool Has(const T& key) const;
    void Add(const T& key);

    void Dfs(void (*visit)(const T& key)) const;

private:
    struct Node {
        T key;
        Node* left;
        Node* right;

        Node(const T& value) : key(value), left(nullptr), right(nullptr) {}
    };
    C cmp;
    Node* root;

    void deleteNode(Node* node);
    bool has(Node* node, const T& key) const;
    void add(Node*& node, const T& key);
    void dfs(Node* node, void (*visit)(const T& key)) const;
};

template<typename T, typename C>
BinaryTree<T, C>::~BinaryTree() {
    deleteNode(root);
}

template<typename T, typename C>
void BinaryTree<T, C>::deleteNode(Node* node) {
    if (!node) return;
    std::stack<Node*> nodeStack;
    Node* current = node;
    Node* lastVisited = nullptr;
    while (!nodeStack.empty() || current) {
        if (current) {
            nodeStack.push(current);
            current = current->left;
        } else {
            Node* topNode = nodeStack.top();
            if (topNode->right != nullptr && topNode->right != lastVisited) {
                current = topNode->right;
            } else {
                delete topNode;
                lastVisited = topNode;
                nodeStack.pop();
            }
        }
    }
}

template<typename T, typename C>
bool BinaryTree<T, C>::Has(const T& key) const {
    return has(root, key);
}

template<typename T, typename C>
bool BinaryTree<T, C>::has(Node* node, const T& key) const {
    Node* current = node;
    while(current) {
        if (current->key == key) {
            return true;
        }
        if (cmp(key, current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

template<typename T, typename C>
void BinaryTree<T, C>::Add(const T& key) {
    add(root, key);
}

template<typename T, typename C>
void BinaryTree<T, C>::add(Node*& node, const T& key) {
    if (!node) {
        node = new Node(key);
        return;
    }
    Node* current = node;
    Node* parent = nullptr;
    while (current) {
        parent = current;
        if (cmp(key, current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (cmp(key, parent->key)) {
        parent->left = new Node(key);
    } else {
        parent->right = new Node(key);
    }
}

template<typename T, typename C>
void BinaryTree<T, C>::Dfs(void (*visit)(const T& key)) const {
    dfs(root, visit);
}

template<typename T, typename C>
void BinaryTree<T, C>::dfs(Node* node, void (*visit)(const T& key)) const {
    if (node == nullptr) {
        return;
    }
    std::stack<Node*> nodeStack;
    Node* lastVisited = nullptr;
    Node* current = node;
    while(!nodeStack.empty() || current) {
        if (current) {
            nodeStack.push(current);
            current = current->left;
        } else {
            Node* topNode = nodeStack.top();
            if (topNode->right != nullptr && topNode->right != lastVisited) {
                current = topNode->right;
            } else {
                visit(topNode->key);
                lastVisited = topNode;
                nodeStack.pop();
            }
        }
    }
}

struct Comparator {
    bool operator()(const int& a, const int& b) const {
        return a < b;
    }
};

int main() {
    int n;
    std::cin >> n;
    Comparator cmp;
    BinaryTree<int, Comparator> tree(cmp);
    for (int i = 0; i < n; i++) {
        int elem;
        std::cin >> elem;
        tree.Add(elem);
    }

    tree.Dfs([](const int& key) { std::cout << key << " "; });
    return 0;
}
