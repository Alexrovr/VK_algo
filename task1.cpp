#include <iostream>
#include <string>

enum State {
    Empty,
    Full,
    Deleted
};

struct Node {
    std::string value;
    State state = Empty;
};

class HashTable {
private:
    Node* table;
    size_t capacity;
    size_t size;

    size_t hash(const std::string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = hash_value * 31 + ch;
        }
        return hash_value % capacity;
    }

    void resize() {
        size_t old_capacity = capacity;
        Node *old_table = table;

        capacity *= 2;
        table = new Node[capacity];
        size_t old_size = size;
        size = 0;

        for (size_t i = 0; i < old_capacity; ++i) {
            if (old_table[i].state == Full) {
                size_t index = hash(old_table[i].value);
                for (size_t j = 0; j < capacity; ++j) {
                    if (table[index].state != Full) {
                        table[index].value = old_table[i].value;
                        table[index].state = Full;
                        size++;
                        break;
                    }
                    index = (index + j + 1) % capacity;
                }
            }
        }
        delete[] old_table;
    }

public:
    HashTable(size_t cap = 8) : capacity(cap), size(0) {
        table = new Node[capacity];
    }

    ~HashTable() {
        delete[] table;
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    bool contains(const std::string& key) const {
        size_t index = hash(key);
        for (size_t i = 0; i < capacity; ++i) {
            if (table[index].state == Empty) {
                return false;
            }
            if (table[index].state == Full && table[index].value == key) {
                return true;
            }
            index = (index + i + 1) % capacity;
        }
        return false;
    }

    void remove(const std::string& key) {
        size_t index = hash(key);
        for (size_t i = 0; i < capacity; ++i) {
            if (table[index].state == Empty) {
                return;
            }
            if (table[index].state == Full && table[index].value == key) {
                table[index].state = Deleted;
                --size;
                return;
            }
            index = (index + i + 1) % capacity;
        }
    }

    bool add(const std::string& key) {
        if (size >= capacity * 0.75) {
            resize();
        }
        size_t h = hash(key);
        int first_deleted_index = -1;
        for (size_t i = 0; i < capacity; ++i) {
            size_t index = (h + i * (i + 1) / 2) % capacity;
            if (table[index].state == Full) {
                if (table[index].value == key) {
                    return false;
                }
            }
            else if (table[index].state == Deleted) {
                if (first_deleted_index == -1) {
                    first_deleted_index = static_cast<int>(index);
                }
            }
            else if (table[index].state == Empty) {
                size_t insert_index = (first_deleted_index != -1) ? first_deleted_index : index;
                table[insert_index].value = key;
                table[insert_index].state = Full;
                ++size;
                return true;
            }
        }
        if (first_deleted_index != -1) {
            table[first_deleted_index].value = key;
            table[first_deleted_index].state = Full;
            ++size;
            return true;
        }

        return false;
    }
};

int main() {
    HashTable hashtable;
    char command;
    std::string s;
    while (std::cin >> command >> s) {
        if (command == '+') {
            std::cout << (hashtable.add(s) ? "OK" : "FAIL") << std::endl;
        } else if (command == '-') {
            if (!hashtable.contains(s)) {
                std::cout << "FAIL" << std::endl;
                continue;
            }
            hashtable.remove(s);
            std::cout << "OK" << std::endl;
        } else if (command == '?') {
            std::cout << (hashtable.contains(s) ? "OK" : "FAIL") << std::endl;
        }
    }

    return 0;
}
