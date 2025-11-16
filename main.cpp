#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>

class ArrayGenerator {
private:
    std::vector<int> rand_arr;
    std::vector<int> rev_arr;
    std::vector<int> almost_sorted_arr;

public:
    ArrayGenerator() {
        rand_arr.resize(100000);
        rev_arr.resize(100000);
        almost_sorted_arr.resize(100000);

        std::mt19937 rng(12345);
        std::uniform_int_distribution<int> dist(0, 10000);

        for (int i = 0; i < 100000; i++) {
            int v = dist(rng);
            rand_arr[i] = v;
            rev_arr[i] = v;
            almost_sorted_arr[i] = v;
        }

        std::sort(rev_arr.begin(), rev_arr.end());
        std::reverse(rev_arr.begin(), rev_arr.end());

        std::sort(almost_sorted_arr.begin(), almost_sorted_arr.end());
        for (int j = 0; j < 200; j++) {
            int a = rng() % 100000;
            int b = rng() % 100000;
            std::swap(almost_sorted_arr[a], almost_sorted_arr[b]);
        }
    }

    std::vector<int> getRandom(int n) {
        return std::vector<int>(rand_arr.begin(), rand_arr.begin() + n);
    }

    std::vector<int> getReversed(int n) {
        return std::vector<int>(rev_arr.begin(), rev_arr.begin() + n);
    }

    std::vector<int> getAlmostSorted(int n) {
        return std::vector<int>(almost_sorted_arr.begin(), almost_sorted_arr.begin() + n);
    }
};

class SortTester {
public:
    SortTester() = default;

    long long testMergeSort(const std::vector<int> &arr) {
        std::vector<int> a = arr;
        std::vector<int> tmp(a.size());

        auto s = std::chrono::high_resolution_clock::now();
        mergeSort(a, tmp, 0, (int)a.size());
        auto e = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
    }

    long long testHybridSort(const std::vector<int> &arr, int threshold) {
        std::vector<int> a = arr;
        std::vector<int> tmp(a.size());

        auto s = std::chrono::high_resolution_clock::now();
        mergeSortHybrid(a, tmp, 0, (int)a.size(), threshold);
        auto e = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
    }

private:
    void insertionSort(std::vector<int> &a, int l, int r) {
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

    void mergeRanges(std::vector<int> &a, std::vector<int> &tmp,
                     int l, int m, int r) {
        int i = l;
        int j = m;
        int k = l;

        while (i < m && j < r) {
            if (a[i] <= a[j]) {
                tmp[k++] = a[i++];
            } else {
                tmp[k++] = a[j++];
            }
        }

        while (i < m) {
            tmp[k++] = a[i++];
        }
        while (j < r) {
            tmp[k++] = a[j++];
        }

        for (int t = l; t < r; t++) {
            a[t] = tmp[t];
        }
    }

    void mergeSort(std::vector<int> &a, std::vector<int> &tmp,
                   int l, int r) {
        if (r - l <= 1) {
            return;
        }
        int m = l + (r - l) / 2;
        mergeSort(a, tmp, l, m);
        mergeSort(a, tmp, m, r);
        mergeRanges(a, tmp, l, m, r);
    }

    void mergeSortHybrid(std::vector<int> &a, std::vector<int> &tmp,
                         int l, int r, int threshold) {
        if (r - l <= threshold) {
            insertionSort(a, l, r);
            return;
        }
        int m = l + (r - l) / 2;
        mergeSortHybrid(a, tmp, l, m, threshold);
        mergeSortHybrid(a, tmp, m, r, threshold);
        mergeRanges(a, tmp, l, m, r);
    }
};

int main() {
    ArrayGenerator gen;
    SortTester tester;

    std::vector<int> sizes;
    for (int i = 500; i <= 100000; i += 100) {
        sizes.push_back(i);
    }

    int threshold = 15;

    auto run_tests = [&](const std::string &fname,
                         auto generator) {
        std::ofstream out(fname);
        out << "size,merge,hybrid\n";

        for (int n : sizes) {
            long long sum_m = 0;
            long long sum_h = 0;

            for (int t = 0; t < 5; t++) {
                std::vector<int> arr = generator(n);
                sum_m += tester.testMergeSort(arr);
                sum_h += tester.testHybridSort(arr, threshold);
            }

            long long avg_m = sum_m / 5;
            long long avg_h = sum_h / 5;
            out << n << "," << avg_m << "," << avg_h << "\n";
        }
    };

    run_tests("random_results.csv",
              [&](int n){ return gen.getRandom(n); });

    run_tests("reversed_results.csv",
              [&](int n){ return gen.getReversed(n); });

    run_tests("almost_sorted_results.csv",
              [&](int n){ return gen.getAlmostSorted(n); });
    return 0;
}
