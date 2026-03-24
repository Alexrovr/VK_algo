#include <iostream>

template <typename T, typename C>
int partition(T* array, int left, int right, C compare) {
    int mid = left + (right - left) / 2;
    int pivot = right - 1;
    if (compare(array[left], array[mid])) {
        if (compare(array[pivot], array[left])) pivot = left;
        else if (compare(array[mid], array[pivot])) pivot = mid;
    } else {
        if (compare(array[pivot], array[mid])) pivot = mid;
        else if (compare(array[left], array[pivot])) pivot = left;
    }
    std::swap(array[pivot], array[right - 1]);
    pivot = right - 1;
    int i = left;
    int j = left;
    while (j < pivot) {
        if (compare(array[pivot], array[j])) {
            ++j;
        } else {
            std::swap(array[i], array[j]);
            ++i;
            ++j;
        }
    }
    std::swap(array[i], array[pivot]);
    return i;
}

template <typename T, typename C>
T quick_select(T* array, int n, int k, C compare) {
    int left = 0;
    int right = n;
    while (left < right) {
        int pivot = partition(array, left, right, compare);
        if (pivot == k) return array[pivot];
        else if (pivot > k) right = pivot;
        else left = pivot;
    }
    return T();
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) std::cin >> arr[i];
    int k10 = n * 10 / 100;
    int k50 = n * 50 / 100;
    int k90 = n * 90 / 100;
    auto less = [](int a, int b) { return a < b; };
    std::cout << quick_select(arr, n, k10, less) << std::endl;
    std::cout << quick_select(arr, n, k50, less) << std::endl;
    std::cout << quick_select(arr, n, k90, less) << std::endl;
    delete[] arr;
    return 0;
}
