#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <cassert>
#include <functional>
#include <numeric>
#include <utility>
#include <queue>

using VertexId = int;

using AdjacencyList = std::vector<std::vector<VertexId>>;

using Matrix = std::vector<std::string>;

enum class Color {
    White, Gray, Black
};

struct Graph {
public:
    Graph() = delete;
    
    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}
    
    bool ContainsLoop() const {
        auto colors = GetArrayOfColor(Color::White);
        
        bool found_loop = false;
        
        for (VertexId starting_vertex = 0; starting_vertex < colors.size(); ++starting_vertex) {
            if (colors[starting_vertex] == Color::White) {
                DFS(starting_vertex, colors, [&](VertexId current_vertex_id) {
                    for (VertexId adjacent_vertex_id : adjacency_list_[current_vertex_id]) {
                        if (colors[adjacent_vertex_id] == Color::Gray) {
                            found_loop = true;
                        }
                    }
                });
            }
        }
        
        return found_loop;
    }
    
private:
    std::vector<Color> GetArrayOfColor(Color color) const {
        return {adjacency_list_.size(), color};
    }
    
    template<typename Predicate>
    void DFS(VertexId start_id, std::vector<Color>& color_of, Predicate predicate) const {
        predicate(start_id);
        
        color_of[start_id] = Color::Gray;
        
        for (VertexId adjacent_vertex : adjacency_list_[start_id]) {
            if (color_of[adjacent_vertex] == Color::White) {
                DFS(adjacent_vertex, color_of, predicate);
            }
        }
        
        color_of[start_id] = Color::Black;
    }
    
private:
    AdjacencyList adjacency_list_;
};

Graph ReadGraph(std::istream& input) {
    int vertexes_count;
    
    input >> vertexes_count >> std::ws;
    
    AdjacencyList adjacency_list(vertexes_count);
    
    std::string row;
    
    const int rows_to_read = vertexes_count - 1;
    
    for (VertexId from_vertex_id = 0; from_vertex_id < rows_to_read; ++from_vertex_id) {
        std::getline(input, row);
        
        for (int j = 0; j < row.size(); ++j) {
            VertexId to_vertex_id = from_vertex_id + j + 1;
            
            if (row[j] == 'B') {
                adjacency_list[to_vertex_id].push_back(from_vertex_id);
            } else {
                adjacency_list[from_vertex_id].push_back(to_vertex_id);
            }
        }
    }
    
    return Graph{std::move(adjacency_list)};
}

int main() {
    if (ReadGraph(std::cin).ContainsLoop()) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }
    
    return 0;
}
