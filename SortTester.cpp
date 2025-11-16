#include "SortTester.h"
#include <chrono>
#include <fstream>

SortTester::SortTester() = default;
void SortTester::insertionSort(std::vector<int> &a, int l, int r) {
    for (int i = l + 1; i < r; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= l && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
void SortTester::mergeRanges(std::vector<int> &a, std::vector<int> &tmp,
                             int l, int m, int r) {
    int i = l;
    int j = m;
    int k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) {
            tmp[k] = a[i];
            i++;
        } else {
            tmp[k] = a[j];
            j++;
        }
        k++;
    }
    while (i < m) {
        tmp[k] = a[i];
        i++;
        k++;
    }
    while (j < r) {
        tmp[k] = a[j];
        j++;
        k++;
    }
    for (int t = l; t < r; t++) {
        a[t] = tmp[t];
    }
}
void SortTester::mergeSort(std::vector<int> &a, std::vector<int> &tmp,
                           int l, int r) {
    int len = r - l;
    if (len <= 1) {
        return;
    }
    int m = l + len / 2;
    mergeSort(a, tmp, l, m);
    mergeSort(a, tmp, m, r);
    mergeRanges(a, tmp, l, m, r);
}
void SortTester::mergeSortHybrid(std::vector<int> &a, std::vector<int> &tmp,
                                 int l, int r, int threshold) {
    int len = r - l;
    if (len <= threshold) {
        insertionSort(a, l, r);
        return;
    }

    int m = l + len / 2;

    mergeSortHybrid(a, tmp, l, m, threshold);
    mergeSortHybrid(a, tmp, m, r, threshold);

    mergeRanges(a, tmp, l, m, r);
}
long long SortTester::testMergeSort(const std::vector<int> &arr) {
    std::vector<int> a = arr;
    std::vector<int> tmp(a.size());

    auto start = std::chrono::high_resolution_clock::now();

    mergeSort(a, tmp, 0, (int)a.size());

    auto end = std::chrono::high_resolution_clock::now();
    long long mcs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return mcs;
}
long long SortTester::testHybridSort(const std::vector<int> &arr, int threshold) {
    std::vector<int> a = arr;
    std::vector<int> tmp(a.size());

    auto start = std::chrono::high_resolution_clock::now();

    mergeSortHybrid(a, tmp, 0, (int)a.size(), threshold);

    auto end = std::chrono::high_resolution_clock::now();
    long long mcs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return mcs;
}
void SortTester::runAllTests(const std::string &filename,
                             const std::vector<int> &sizes,
                             int threshold) {
    std::ofstream out(filename);
    out << "size,merge,hybrid\n";

    for (int n : sizes) {
        long long sum_m = 0;
        long long sum_h = 0;

        for (int i = 0; i < 5; i++) {
        }
    }

    out.close();
}
