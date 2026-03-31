#include <iostream>
#include <string>

void msd_sort(std::string* a, int lo, int hi, int d, std::string* temp_arr) {
    if (hi <= lo + 1) return;

    int count[256 + 2] = {0};

    for (int i = lo; i < hi; i++) {
        int c = (d < a[i].length()) ? (unsigned char)a[i][d] : -1;
        count[c + 2]++;
    }

    for (int r = 0; r < 256 + 1; r++) {
        count[r + 1] += count[r];
    }

    for (int i = lo; i < hi; i++) {
        int c = (d < a[i].length()) ? (unsigned char)a[i][d] : -1;
        temp_arr[count[c + 1]++] = a[i];
    }

    for (int i = lo; i < hi; i++) {
        a[i] = temp_arr[i - lo];
    }

    for (int r = 0; r < 256; r++) {
        int start = lo + (r == 0 ? count[0] : count[r]);
        int end = lo + count[r + 1];
        if (end > start) {
            msd_sort(a, start, end, d + 1, temp_arr);
        }
    }
}

int main() {
    std::string* strings = new std::string[100000];
    std::string* temp_arr = new std::string[100000];

    int n = 0;
    while (n < 100000 && std::cin >> strings[n]) {
        n++;
    }

    if (n > 0) {
        msd_sort(strings, 0, n, 0, temp_arr);
    }

    for (int i = 0; i < n; i++) {
        std::cout << strings[i] << "\n";
    }

    delete[] strings;
    delete[] temp_arr;

    return 0;
}
