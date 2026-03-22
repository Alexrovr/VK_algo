#include <iostream>

template <typename T, typename IsLess = std::less<T>>
class Heap {
public:
    explicit Heap(const IsLess& comp = IsLess()) : buffer_(nullptr), size_(0), capacity_(0), compare_(comp) {
        capacity_ = 1;
        buffer_ = new T[capacity_];
    }

    ~Heap() {
        delete[] buffer_;
    }

    Heap(const Heap&) = delete;
    Heap& operator=(const Heap&) = delete;

    void push(const T& value) {
        if (size_ == capacity_) {
            capacity_ *= 2;
            T* new_buffer = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                new_buffer[i] = buffer_[i];
            }
            delete[] buffer_;
            buffer_ = new_buffer;
        }
        buffer_[size_] = value;
        ++size_;
        sift_up(size_ - 1);
    }

    void pop() {
        if (size_ == 0) return;
        buffer_[0] = buffer_[size_ - 1];
        --size_;
        if (size_ > 0) {
            sift_down(0);
        }
    }

    const T& top() const {
        return buffer_[0];
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }
private:
    T* buffer_;
    size_t size_;
    size_t capacity_;
    IsLess compare_;

    void sift_up(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (compare_(buffer_[idx], buffer_[parent])) {
                std::swap(buffer_[idx], buffer_[parent]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    void sift_down(size_t idx) {
        while (true) {
            size_t left = 2 * idx + 1;
            size_t right = 2 * idx + 2;
            size_t smallest = idx;
            if (left < size_ && compare_(buffer_[left], buffer_[smallest])) {
                smallest = left;
            }
            if (right < size_ && compare_(buffer_[right], buffer_[smallest])) {
                smallest = right;
            }
            if (smallest != idx) {
                std::swap(buffer_[idx], buffer_[smallest]);
                idx = smallest;
            } else {
                break;
            }
        }
    }
};

struct Process {
    int P;
    int t;
    int T;

    Process() : P(0), T(0), t(0) {}

    Process(int p, int t_total, int t_worked) : P(p), T(t_total), t(t_worked) {}
};

struct CompareProcess {
    bool operator()(const Process& a, const Process& b) const {
        long long key_a = static_cast<long long>(a.P) * (a.t + 1);
        long long key_b = static_cast<long long>(b.P) * (b.t + 1);
        return key_a < key_b;   // min-heap
    }
};

int main() {
    int n;
    std::cin >> n;

    Heap<Process, CompareProcess> heap;

    for (int i = 0; i < n; ++i) {
        int P, T;
        std::cin >> P >> T;
        heap.push(Process(P, T, 0));
    }

    long long switches = 0;

    while (!heap.empty()) {
        Process proc = heap.top();
        heap.pop();
        proc.t += proc.P;
        ++switches;
        if (proc.t < proc.T) {
            heap.push(proc);
        }
    }
    std::cout << switches << std::endl;
    return 0;
}
