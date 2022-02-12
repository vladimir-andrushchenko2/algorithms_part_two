#include <vector>
#include <cassert>
//#include "solution.h"

#include <algorithm>

int siftDown(std::vector<int>& heap, int idx) {
    int index_left_child = idx * 2;
    int index_right_child = idx * 2 + 1;

    // if no children return
    if (index_left_child >= heap.size()) {
        return idx;
    }

    int index_of_larger_element = index_left_child;

    // if both children
    if (index_right_child < heap.size()) {
        if (heap[index_left_child] < heap[index_right_child]) {
            index_of_larger_element = index_right_child;
        } else {
            index_of_larger_element = index_left_child;
        }
    }

    if (heap[idx] < heap[index_of_larger_element]) {
        std::swap(heap[idx], heap[index_of_larger_element]);
        return siftDown(heap, index_of_larger_element);
    }

    return idx;
}

void test() {
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    int result = siftDown(sample, 2);
    assert(result == 5);
}


int main() {
    test();

    return 0;
}
