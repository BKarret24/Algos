#include "ArrayGenerator.h"
#include <random>
#include <algorithm>

ArrayGenerator::ArrayGenerator() {
    rand_arr.resize(100000);
    rev_arr.resize(100000);
    almost_sorted_arr.resize(100000);

    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(0, 10000);

    for (int i = 0; i < 100000; i++) {
        int val = dist(rng);
        rand_arr[i] = val;
        rev_arr[i] = val;
        almost_sorted_arr[i] = val;
    }

    std::sort(rev_arr.begin(), rev_arr.end());
    std::reverse(rev_arr.begin(), rev_arr.end());

    std::sort(almost_sorted_arr.begin(), almost_sorted_arr.end());
    for (int j = 0; j < 200; j++) {
        int i1 = rng() % 100000;
        int i2 = rng() % 100000;
        std::swap(almost_sorted_arr[i1], almost_sorted_arr[i2]);
    }
}

std::vector<int> ArrayGenerator::getRandom(int n) {
    return std::vector<int>(rand_arr.begin(), rand_arr.begin() + n);
}

std::vector<int> ArrayGenerator::getReversed(int n) {
    return std::vector<int>(rev_arr.begin(), rev_arr.begin() + n);
}

std::vector<int> ArrayGenerator::getAlmostSorted(int n) {
    return std::vector<int>(almost_sorted_arr.begin(), almost_sorted_arr.begin() + n);
}
