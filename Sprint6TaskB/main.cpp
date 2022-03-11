#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>
#include <deque>
#include <cassert>
#include <stdexcept>
#include <stack>

using VertexId = int;

using Matrix = std::vector<std::string>;

struct City {
    std::unordered_map<VertexId, char> from;
};

class Graph {
public:
    Graph() = delete;
    
    Graph(Matrix matrix) :
    matrix_(std::move(matrix)), cities_(matrix_.size() + 1) {}
    
    void ConnectCities(VertexId current_id, std::pair<std::stack<VertexId>, char> previous) {
        for (int i = 0; i < matrix_[current_id].size(); ++i) {
            VertexId to_id = current_id + i + 1;
            
            if (matrix_[current_id][to_id - current_id - 1] != previous.second) {
                // assign new type
                previous.second = matrix_[current_id][to_id - 1];
                
                // clear stack
                std::stack<VertexId> empty_temp;
                std::swap(previous.first, empty_temp);
            }

            previous.first.push(current_id);

            ConnectCities(to_id, previous);

            previous.first.pop();
        }
        
        while (!previous.first.empty()) {
            VertexId previous_city = previous.first.top();
            previous.first.pop();
            
            if (cities_[current_id].from.count(previous_city) > 0 && cities_[current_id].from[previous_city] != previous.second) {
                throw std::logic_error("duplicate route");
            } else {
                cities_[current_id].from[previous_city] = previous.second;
            }
        }
    }
    
private:
    Matrix matrix_;
    std::vector<City> cities_;
};

Graph ReadMatrix(std::istream& input) {
    int vertexes_count;
    
    input >> vertexes_count >> std::ws;
    
    Matrix matrix;
    
    std::string roads_from_city;
    
    for (int i = 1; i < vertexes_count; ++i) {
        std::getline(input, roads_from_city);
        
        matrix.push_back(std::move(roads_from_city));
    }
    
    return {std::move(matrix)};
}

int main(int argc, const char * argv[]) {
    auto matrix = ReadMatrix(std::cin);

    try {
        matrix.ConnectCities(0, {{}, '\0'});

        std::cout << "YES\n";
    } catch (std::logic_error& e) {
        std::cout << "NO\n";
    }


    return 0;
}
