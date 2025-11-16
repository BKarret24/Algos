#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <vector>
#include <string>

class SortTester {
public:
    SortTester();
    long long testMergeSort(const std::vector<int> &arr);
    long long testHybridSort(const std::vector<int> &arr, int threshold);

    void runAllTests(const std::string &filename,
                     const std::vector<int> &sizes,
                     int threshold);

private:
    void mergeSort(std::vector<int> &a, std::vector<int> &tmp, int l, int r);
    void mergeSortHybrid(std::vector<int> &a, std::vector<int> &tmp,
                         int l, int r, int threshold);

    void insertionSort(std::vector<int> &a, int l, int r);
    void mergeRanges(std::vector<int> &a, std::vector<int> &tmp,
                     int l, int m, int r);
};

#endif

