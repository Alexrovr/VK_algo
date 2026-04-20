#include <iostream>
using namespace std;

struct Node {
    int key;
    int left;
    int right;
};

int main() {
    int n;
    cin >> n;

    if (n == 0) return 0;

    Node* tree = new Node[n];
    int root = 0;

    cin >> tree[0].key;
    tree[0].left = -1;
    tree[0].right = -1;

    for (int i = 1; i < n; i++) {
        int key;
        cin >> key;

        int current = root;
        while (true) {
            if (tree[current].key <= key) {
                if (tree[current].right == -1) {
                    tree[current].right = i;
                    tree[i].key = key;
                    tree[i].left = -1;
                    tree[i].right = -1;
                    break;
                } else {
                    current = tree[current].right;
                }
            } else {
                if (tree[current].left == -1) {
                    tree[current].left = i;
                    tree[i].key = key;
                    tree[i].left = -1;
                    tree[i].right = -1;
                    break;
                } else {
                    current = tree[current].left;
                }
            }
        }
    }

    int* stack1 = new int[n];
    int* stack2 = new int[n];
    int top1 = 0, top2 = 0;

    stack1[top1++] = root;

    while (top1 > 0) {
        int node = stack1[--top1];
        stack2[top2++] = node;

        if (tree[node].left != -1) {
            stack1[top1++] = tree[node].left;
        }
        if (tree[node].right != -1) {
            stack1[top1++] = tree[node].right;
        }
    }

    bool first = true;
    for (int i = top2 - 1; i >= 0; i--) {
        if (!first) cout << " ";
        cout << tree[stack2[i]].key;
        first = false;
    }
    cout << "\n";

    delete[] tree;
    delete[] stack1;
    delete[] stack2;

    return 0;
}
