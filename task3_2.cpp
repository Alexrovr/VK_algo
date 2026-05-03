#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

template<typename T, typename C>
class BTree {
public:
    BTree(size_t _t, const C& _cmp) : t(_t), cmp(_cmp), root(nullptr) {}

    ~BTree() {
        clear(root);
    }

    void Add(const T& key) {
        if (root == nullptr) {
            root = new Node(true);
            root->Keys.push_back(key);
            return;
        }

        if (isNodeFull(root)) {
            Node* newRoot = new Node(false);
            newRoot->Children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    void PrintLayers() const {
        if (!root) return;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            size_t levelSize = q.size();
            for (size_t i = 0; i < levelSize; ++i) {
                Node* current = q.front();
                q.pop();

                for (const auto& key : current->Keys) {
                    std::cout << key << " ";
                }

                if (!current->IsLeaf) {
                    for (Node* child : current->Children) {
                        q.push(child);
                    }
                }
            }
            std::cout << "\n";
        }
    }

private:
    struct Node {
        std::vector<T> Keys;
        std::vector<Node*> Children;
        bool IsLeaf;
        Node(bool isLeaf) : IsLeaf(isLeaf) {}
    };

    size_t t;
    C cmp;
    Node* root;

    bool isNodeFull(Node* node) {
        return node->Keys.size() == 2 * t - 1;
    }

    void splitChild(Node* parent, size_t index) {
        Node* fullNode = parent->Children[index];
        Node* newNode = new Node(fullNode->IsLeaf);

        T medianKey = fullNode->Keys[t - 1];

        for (size_t i = t; i < 2 * t - 1; ++i) {
            newNode->Keys.push_back(fullNode->Keys[i]);
        }

        if (!fullNode->IsLeaf) {
            for (size_t i = t; i < 2 * t; ++i) {
                newNode->Children.push_back(fullNode->Children[i]);
            }
            fullNode->Children.resize(t);
        }

        fullNode->Keys.resize(t - 1);

        parent->Children.insert(parent->Children.begin() + index + 1, newNode);
        parent->Keys.insert(parent->Keys.begin() + index, medianKey);
    }

    void insertNonFull(Node* node, const T& key) {
        int i = static_cast<int>(node->Keys.size()) - 1;

        if (node->IsLeaf) {
            node->Keys.push_back(key);
            while (i >= 0 && cmp(key, node->Keys[i])) {
                node->Keys[i + 1] = node->Keys[i];
                --i;
            }
            node->Keys[i + 1] = key;
        } else {
            while (i >= 0 && cmp(key, node->Keys[i])) {
                --i;
            }
            ++i;

            if (isNodeFull(node->Children[i])) {
                splitChild(node, i);
                if (cmp(node->Keys[i], key)) {
                    ++i;
                }
            }
            insertNonFull(node->Children[i], key);
        }
    }

    void clear(Node* node) {
        if (!node) return;
        for (Node* child : node->Children) {
            clear(child);
        }
        delete node;
    }
};

struct Less {
    bool operator()(uint32_t a, uint32_t b) const {
        return a < b;
    }
};

int main() {
    int t;
    if (!(std::cin >> t)) return 0;

    BTree<uint32_t, Less> tree(t, Less());

    uint32_t key;
    while (std::cin >> key) {
        tree.Add(key);
    }

    tree.PrintLayers();

    return 0;
}
