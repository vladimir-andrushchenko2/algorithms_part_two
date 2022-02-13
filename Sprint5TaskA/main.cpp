#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <cassert>
#include <sstream>

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

int GetLeftChild(int parent_index) {
    return parent_index * 2;
}

int GetRightChild(int parent_index) {
    return parent_index * 2 + 1;
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
    std::stringstream test_input_stream{test_input};
    RunProgram(test_input_stream);
    return 0;
}
