// 65132675
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <cassert>
#include <sstream>
#include <iterator>
#include <deque>

namespace HeapUtility {

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

template<typename It, typename Predicate>
int IndexOfMax(It before_begin, int index_left, int index_right, Predicate is_less) {
    return is_less(*(before_begin + index_left), *(before_begin + index_right)) ? index_right : index_left;
}

template<typename It, typename Predicate>
void MaxHeapify(It before_begin, It end, const int index, Predicate is_less) {
    // if no children
    if (!IsInsideHeap(before_begin, end, IndexOfLeftChild(index))) {
        return;
    }
    
    // initialize with left child because we don't know if right child exists
    int index_of_larger_child = IndexOfLeftChild(index);
    
    // if both children exist
    if (IsInsideHeap(before_begin, end, IndexOfRightChild(index))) {
        index_of_larger_child = IndexOfMax(before_begin, IndexOfLeftChild(index), IndexOfRightChild(index), is_less);
    }
    
    if (IndexOfMax(before_begin, index, index_of_larger_child, is_less) != index) {
        std::swap(*(before_begin + index), *(before_begin + index_of_larger_child));
        MaxHeapify(before_begin, end, index_of_larger_child, is_less);
    }
}

template<typename It, typename Predicate>
void BuildMaxHeap(It before_begin, It end, Predicate is_less) {
    for (int i = static_cast<int>(std::distance(before_begin, end)) / 2; i > 0; --i) {
        MaxHeapify(before_begin, end, i, is_less);
    }
}

}

template<typename It, typename Predicate>
void Heapsort(It before_begin, It end, Predicate is_less) {
    HeapUtility::BuildMaxHeap(before_begin, end, is_less);
    
    for (int i = static_cast<int>(std::distance(before_begin, end)) - 1; i > 1; --i) {
        std::swap(*(before_begin + 1), *(before_begin + i));
        --end;
        HeapUtility::MaxHeapify(before_begin, end, 1, is_less);
    }
}

struct CompetitiveProgrammer {
    int score{};
    int penalty{};
    std::string name;
};

void RunProgram(std::istream& input) {
    int n_contestants{};
    
    input >> n_contestants;
    
    std::deque<CompetitiveProgrammer> data(n_contestants + 1);
    
    for (int i = 1; i < data.size(); ++i) {
        input >> data[i].name;
        input >> data[i].score;
        input >> data[i].penalty;
    }
    
    Heapsort(data.begin(), data.end(), [](const CompetitiveProgrammer& left, const CompetitiveProgrammer& right) {
        int left_score_negative = -left.score;
        int right_score_negative = -right.score;
        return std::tie(left_score_negative, left.penalty, left.name) < std::tie(right_score_negative, right.penalty, right.name);
    });
    
    // remove ficticious element
    data.pop_front();
    
    for (const auto& x : data) {
        std::cout << x.name << '\n';
    }
}

int main(int argc, const char * argv[]) {
    RunProgram(std::cin);
    return 0;
}
