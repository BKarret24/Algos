#ifndef SET1_ARRAYGENERATOR_H
#define SET1_ARRAYGENERATOR_H

#include <vector>

class ArrayGenerator {
    std::vector<int> rand_arr;
    std::vector<int> rev_arr;
    std::vector<int> almost_sorted_arr;

public:
    ArrayGenerator();

    std::vector<int> getRandom(int n);
    std::vector<int> getReversed(int n);
    std::vector<int> getAlmostSorted(int n);
};

#endif //SET1_ARRAYGENERATOR_H