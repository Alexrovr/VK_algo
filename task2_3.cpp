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

    // Выделяем массив для узлов
    Node* tree = new Node[n];
    int root = 0;

    // Читаем корень
    cin >> tree[0].key;
    tree[0].left = -1;
    tree[0].right = -1;

    // Вставляем остальные элементы
    for (int i = 1; i < n; i++) {
        int key;
        cin >> key;

        int current = root;
        while (true) {
            if (tree[current].key <= key) {
                // Вставляем в правое поддерево
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
                // Вставляем в левое поддерево
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

    // Обход post-order без рекурсии
    // Используем два массива как стеки
    int* stack1 = new int[n];  // для обхода
    int* stack2 = new int[n];  // для сохранения результата
    int top1 = 0, top2 = 0;

    // Обратный pre-order: узел -> правый -> левый
    // При развороте получим post-order: левый -> правый -> узел
    stack1[top1++] = root;

    while (top1 > 0) {
        int node = stack1[--top1];
        stack2[top2++] = node;

        // Пушим левого потомка, потом правого
        // (чтобы в stack1 они обрабатывались в нужном порядке)
        if (tree[node].left != -1) {
            stack1[top1++] = tree[node].left;
        }
        if (tree[node].right != -1) {
            stack1[top1++] = tree[node].right;
        }
    }

    // Выводим элементы в обратном порядке из stack2
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
