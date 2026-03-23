#include <iostream>

struct Point {
    int coord_;
    int point_;

    Point() : coord_(0), point_(0) {}

    Point(int coord, int point) : coord_(coord), point_(point) {}
};

struct PointComparator {
    bool operator()(const Point& a, const Point& b) {
        if (a.coord_ != b.coord_) return a.coord_ < b.coord_;
        return a.point_ > b.point_;
    }
};

template <typename T, typename C>
void merge_sort(T* array, int first, int last, C compare) {
    int len = last - first;
    if (len <= 1) {
        return;
    } else if (len == 2) {
        if (compare(array[first], array[first + 1])) return;
        std::swap(array[first], array[first + 1]);
        return;
    } else {
        int middle = first + len / 2;
        merge_sort(array, first, middle, compare);
        merge_sort(array, middle, last, compare);
        merge(array, first, middle, last, compare);
    }

}

template <typename T, typename C>
void merge(T* array, int first, int middle, int last, C compare) {
    int len = last - first;
    T* arr = new T[len];
    int left = first;
    int right = middle;
    int k = 0;
    while (left < middle && right < last) {
        if (compare(array[left], array[right])) {
            arr[k] = array[left];
            ++left;
        } else {
            arr[k] = array[right];
            ++right;
        }
        ++k;
    }
    while (left < middle) {
        arr[k] = array[left];
        ++left;
        ++k;
    }
    while (right < last) {
        arr[k] = array[right];
        ++right;
        ++k;
    }
    for (int i = 0; i < len; ++i) {
        array[first + i] = arr[i];
    }
    delete[] arr;
}

int main() {
    int n;
    std::cin >> n;
    Point* points = new Point[2 * n];
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        points[2 * i] = Point(l, 1);
        points[2 * i + 1] = Point(r, -1);
    }
    merge_sort(points, 0, 2 * n, PointComparator());
    int line = 0;
    int result = 0;
    for (int i = 0; i < 2 * n; ++i) {
        line += points[i].point_;
        if (line == 1) {
            result += points[i + 1].coord_ - points[i].coord_;
        }
    }
    std::cout << result << std::endl;
    return 0;
}
