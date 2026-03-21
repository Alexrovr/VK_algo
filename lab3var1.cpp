#include <iostream>
#include <cassert>

class Queue {
public:
    Queue() : capacity_(2), size_(0), head_(0), tail_(0) {
        buffer_ = new int[capacity_];
    }

    ~Queue() {
        delete[] buffer_;
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void push_back(int value) {
        if (size_ == capacity_) expand();
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    int pop_front() {
        if (size_ == 0) return -1;
        int result = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return result;
    }

private:
    int* buffer_;
    int capacity_;
    int size_;
    int head_;
    int tail_;

    void expand() {
        int new_capacity = capacity_ * 2;
        int* new_buffer = new int[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i] = buffer_[(head_ + i) % capacity_];
        }
        delete[] buffer_;
        buffer_ = new_buffer;
        head_ = 0;
        tail_ = size_;
        capacity_ = new_capacity;
    }
};

int main() {
    int n;
    std::cin >> n;
    Queue queue;
    bool result = true;
    for (int i = 0; i < n; ++i) {
        int command;
        std::cin >> command;
        int value;
        std::cin >> value;
        if (command == 3) {
            queue.push_back(value);
        } else if (command ==2) {
            if (queue.pop_front() != value) result = false;
        } else {
            assert(false);
        }
    }
    if (result) std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;
    return 0;
}
