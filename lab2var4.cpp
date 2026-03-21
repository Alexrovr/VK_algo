/*
Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.
Время работы поиска для каждого элемента B[i]: O(log(k)).
*/

#include <iostream>
#include <cassert>

class IntArray {
public:
    IntArray() : data_(nullptr), size_(0) {}

    explicit IntArray(size_t n) : data_(new int[n]()), size_(n) {}

    ~IntArray() {
        delete[] data_;
    }

    IntArray(const IntArray&) = delete;
    IntArray& operator=(const IntArray&) = delete;

    int& operator[](size_t idx) {
        assert(idx < size_);
        return data_[idx];
    }

    const int& operator[](size_t idx) const {
        assert(idx < size_);
        return data_[idx];
    }

    size_t size() const {
        return size_;
    }

    void read(std::istream& in, size_t n) {
        assert(data_ != nullptr && size_ == n);
        for (size_t i = 0; i < n; ++i) {
            in >> data_[i];
        }
    }

    void write(std::ostream& out, char delimiter = ' ') const {
        for (size_t i = 0; i < size_; ++i) {
            if (i > 0) out << delimiter;
            out << data_[i];
        }
    }

private:
    int* data_;
    size_t size_;
};

int lower_bound(const IntArray& arr, int left, int right, int value) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int find_closest(const IntArray& A, int x) {
    int n = static_cast<int>(A.size());

    if (x <= A[0]) return 0;
    if (x >= A[n - 1]) return n - 1;

    int i = 1;
    while (i < n && A[i] < x) {
        i *= 2;
    }
    int left = i / 2;
    int right = (i < n) ? i : n - 1;
    assert(left <= right);

    int pos = lower_bound(A, left, right, x);

    if (x - A[pos - 1] <= A[pos] - x) {
        return pos - 1;
    } else {
        return pos;
    }
}

void find_all_closest(const IntArray& A, const IntArray& B, IntArray& result) {
    int m = static_cast<int>(B.size());
    assert(result.size() == static_cast<size_t>(m));
    for (int i = 0; i < m; ++i) {
        result[i] = find_closest(A, B[i]);
    }
}

int main() {
    int n;
    std::cin >> n;
    assert(n > 0);
    IntArray A(n);
    A.read(std::cin, n);

    int m;
    std::cin >> m;
    assert(m >= 0);
    IntArray B(m);
    B.read(std::cin, m);

    IntArray result(m);
    find_all_closest(A, B, result);

    result.write(std::cout);
    std::cout << std::endl;

    return 0;
}
