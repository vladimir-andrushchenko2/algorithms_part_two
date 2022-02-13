#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <cassert>
#include <sstream>
#include <iterator>
#include <optional>

const std::string test_input = R"d(5
alla 4 100
gena 6 1000
gosha 2 90
rita 2 90
timofey 4 80)d";

namespace Heap {

int GetParent(int child_index) {
    return child_index / 2;
}

int IndexOfLeftChild(int parent_index) {
    return parent_index * 2;
}

int IndexOfRightChild(int parent_index) {
    return parent_index * 2 + 1;
}

template<typename It>
bool IsInsideHeap(It before_begin, It end, int index) {
    return index < std::distance(before_begin, end);
}

template<typename It>
int IndexOfMax(It before_begin, int index_left, int index_right) {
    return *(before_begin + index_left) < *(before_begin + index_right) ? index_right : index_left;
}

template<typename It>
void MaxHeapify(It before_begin, It end, const int index) {
    // if no children
    if (!IsInsideHeap(before_begin, end, IndexOfLeftChild(index))) {
        return;
    }
    
    // initialize with left child because we don't know if right child exists
    int index_of_larger_child = IndexOfLeftChild(index);
    
    // if both children exist
    if (IsInsideHeap(before_begin, end, IndexOfRightChild(index))) {
        index_of_larger_child = IndexOfMax(before_begin, IndexOfLeftChild(index), IndexOfRightChild(index));
    }
    
    if (IndexOfMax(before_begin, index, index_of_larger_child) != index) {
        std::swap(*(before_begin + index), *(before_begin + index_of_larger_child));
        MaxHeapify(before_begin, end, index_of_larger_child);
    }
}

template<typename It>
void BuildMaxHeap(It before_begin, It end) {
    for (int i = std::distance(before_begin, end) / 2; i > 0; --i) {
        MaxHeapify(before_begin, end, i);
    }
}

void Test() {
    {
        std::vector<int> test_heap = {-1, 1, 2, 3};
        MaxHeapify(test_heap.begin(), test_heap.end(), 1);
        
        std::vector<int> desired_output = {-1, 3, 2, 1};
        
        assert(test_heap == desired_output);
        std::cout << "Test MaxHeapify OK\n";
    }
    
    {
        std::vector<int> test_heap = {-1, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        BuildMaxHeap(test_heap.begin(), test_heap.end());
        
        std::vector<int> desired_output = {-1, 16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
        
        assert(test_heap == desired_output);
        std::cout << "Test BuildMaxHeap OK\n";
    }
}

}

template<typename It, typename Predicate>
void Heapsort(It begin, It end, Predicate predicate) {
    assert(false);
}

struct CompetitiveProgrammer {
    int score{};
    int penalty{};
    std::string name;
};

void RunProgram(std::istream& input) {
    int n_contestants{};
    
    input >> n_contestants;
    
    std::vector<CompetitiveProgrammer> data(n_contestants + 1);
    
    for (int i = 1; i < n_contestants; ++i) {
        input >> data[i].name;
        input >> data[i].score;
        input >> data[i].penalty;
    }
    
    Heapsort(data.begin(), data.end(), [](const CompetitiveProgrammer& left, const CompetitiveProgrammer& right) {
        int left_score_negative = -left.score;
        int right_score_negative = -right.score;
        return std::tie(left_score_negative, left.penalty, left.name) < std::tie(right_score_negative, right.penalty, right.name);
    });
    
    for (const auto& x : data) {
        std::cout << x.name << '\n';
    }
}

int main(int argc, const char * argv[]) {
//    std::stringstream test_input_stream{test_input};
//    RunProgram(test_input_stream);
    
    Heap::Test();
    return 0;
}
