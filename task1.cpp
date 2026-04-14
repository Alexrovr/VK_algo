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
        size_t new_capacity = capacity * 2;
        Node *new_table = new Node[new_capacity];
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].state == Full) {
                new_table[i] = table[i];
            }
        }
        delete[] table;
        table = new_table;
        capacity = new_capacity;
    }
public:
    HashTable(size_t cap = 8) : capacity(cap), size(0) {
        table = new Node[capacity];
    }

    ~HashTable() {
        delete[] table;
    }

    bool contains(const std::string& key) const {
        size_t index = hash(key);
        while (table[index].state != Empty) {
            if (table[index].state == Full && table[index].value == key) {
                return true;
            }
            index = (index + 1) % capacity;
        }
        return false;
    }

    void remove(const std::string& key) {
        size_t index = hash(key);
        while (table[index].state != Empty) {
            if (table[index].state == Full && table[index].value == key) {
                table[index].state = Deleted;
                --size;
                return;
            }
            index = (index + 1) % capacity;
        }
    }

    bool add(const std::string& key) {  
        if (contains(key)) {
            return false;
        }

        if (size >= capacity * 0.75) {
            resize();
        }
        size_t index = hash(key);
        while (table[index].state == Full) {
            if (table[index].value == key) {
                return false;
            }
            index = (index + 1) % capacity;
        }
        table[index].value = key;
        table[index].state = Full;
        ++size;
        return true;
    }
};
