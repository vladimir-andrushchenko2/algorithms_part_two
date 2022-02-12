#include <cassert>
#include "solution.h"

#include <vector>
#include <algorithm>

int siftUp(std::vector<int>& heap, int idx) {
    static constexpr int kHeadIndex = 1;

    if (idx == kHeadIndex) {
        return kHeadIndex;
    }

    int parent_idx = idx / 2;

    if (heap[parent_idx] < heap[idx]) {
        std::swap(heap[parent_idx], heap[idx]);
        return siftUp(heap, parent_idx);
    }

    return idx;
}

void test() {
    std::vector<int> sample = {-1, 12, 6, 8, 3, 15, 7};
    assert(siftUp(sample, 5) == 1);
}
