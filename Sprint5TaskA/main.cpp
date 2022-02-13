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
bool IsInsideHeap(It begin, It end, int index) {
    return index < std::distance(begin, end);
}

template<typename It>
int IndexOfMax(It begin, int index_left, int index_right) {
    return *(begin + index_left) < *(begin + index_right) ? index_right : index_left;
}

template<typename It>
void MaxHeapify(It begin, It end, const int index) {
    // if no children
    if (!IsInsideHeap(begin, end, IndexOfLeftChild(index))) {
        return;
    }
    
    // initialize with left child because we don't know if right child exists
    int index_of_larger_child = IndexOfLeftChild(index);
    
    // if both children exist
    if (IsInsideHeap(begin, end, IndexOfRightChild(index))) {
        index_of_larger_child = IndexOfMax(begin, IndexOfLeftChild(index), IndexOfRightChild(index));
    }
    
    if (IndexOfMax(begin, index, index_of_larger_child) != index) {
        std::swap(*(begin + index), *(begin + index_of_larger_child));
        MaxHeapify(begin, end, index_of_larger_child);
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
    
    std::vector<CompetitiveProgrammer> data(n_contestants);
    
    for (int i = 0; i < n_contestants; ++i) {
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
