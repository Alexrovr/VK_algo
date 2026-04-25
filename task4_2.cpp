#include <iostream>

template<typename T, typename C>
class AVLTree {
private:
    struct Node {
        T key;
        int height;
        int count;
        Node *left;
        Node *right;
        Node(const T& k) : key(k), height(1), count(1), left(nullptr), right(nullptr) {}
    };
    C cmp;
    Node* root;

    int height(Node* n) {
        if (!n) return 0;
        return n->height;
    }

    int getBalance(Node* n) {
        if (!n) return 0;
        return height(n->right) - height(n->left);
    }

    void updateCount(Node* n) {
        if (!n) return;
        if (!n->left && !n->right) n->count = 1;
        else if (!n->right) n->count = 1 + n->left->count;
        else if (!n->left) n->count = 1 + n->right->count;
        else n->count = 1 + n->left->count + n->right->count;
    }

    void updateHeight(Node* n) {
        if (n) n->height = 1 + std::max(height(n->left), height(n->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateCount(y);
        updateHeight(x);
        updateCount(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateCount(x);
        updateHeight(y);
        updateCount(y);
        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);
        updateCount(n);
        int b = getBalance(n);
        if (b == 2) {
            if (getBalance(n->right) < 0) n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        if (b == -2) {
            if (getBalance(n->left) > 0) n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        return n;
    }

    Node* add(Node* n, const T& key) {
        if (!n) return new Node(key);
        if (cmp(key, n->key)) n->left = add(n->left, key);
        else if (cmp(n->key, key)) n->right = add(n->right, key);
        return balance(n);
    }

    Node* findMin(Node* n) {
        if (n->left) return findMin(n->left);
        return n;
    }

    Node* removeMin(Node* n) {
        if (!n->left) return n->right;
        n->left = removeMin(n->left);
        return balance(n);
    }

    Node* remove(Node* n, const T& key) {
        if (!n) return nullptr;
        if (cmp(key, n->key)) n->left = remove(n->left, key);
        else if (cmp(n->key, key)) n->right = remove(n->right, key);
        else {
            Node* l = n->left;
            Node* r = n->right;
            delete n;
            if (!r) return l;
            Node* minNode = findMin(r);
            minNode->right = removeMin(r);
            minNode->left = l;
            return balance(minNode);
        }
        return balance(n);
    }

    void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    int getS(Node* node, int stat) {
        if(!node) return -1;
        Node* curr = node;
        int leftCount = 0;
        if (curr->left) leftCount = curr->left->count;
        if (stat < leftCount) {
            return getS(curr->left, stat);
        } else if (stat > leftCount) {
            return getS(curr->right, stat - leftCount - 1);
        } else {
            return curr->key;
        }
    }

public:
    AVLTree(const C& c) : root(nullptr), cmp(c) {}
    ~AVLTree() { clear(root); }

    void Add(const T& key) { root = add(root, key); }
    void Remove(const T& key) { root = remove(root, key); }

    bool Has(const T& key) {
        Node* curr = root;
        while (curr) {
            if (curr->key == key) return true;
            if (cmp(key, curr->key)) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    int GetS(int stat) {
        return getS(root, stat);
    }
};

struct Comparator {
    bool operator()(const int& a, const int& b) const {
        return a < b;
    }
};

int main() {
    int n;
    std::cin >> n;
    Comparator cmp;
    AVLTree<int, Comparator> tree(cmp);
    for (int i = 0; i < n; i++) {
        int elem, stat;
        std::cin >> elem >> stat;
        if (elem < 0) {
            if (tree.Has(-elem)) tree.Remove(-elem);
        } else {
            if (!tree.Has(elem)) tree.Add(elem);
        }
        std::cout << tree.GetS(stat) << std::endl;
    }
    return 0;
}
