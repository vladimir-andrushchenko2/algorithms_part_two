#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <cassert>
#include <functional>
#include <numeric>
#include <utility>

using VertexId = int;
using AdjacencyList = std::vector<std::set<VertexId>>;

enum class Color {
    White, Gray, Black
};

struct Graph {
public:
    Graph() = delete;
    
    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}
    
    static Graph ReadUndirectedGraph(std::istream& input) {
        int vertexes_count, edges_count;
        
        std::cin >> vertexes_count >> edges_count;
        
        AdjacencyList adjacency_list(vertexes_count + 1);
        
        std::string line;
        
        for (int i = 0; i < edges_count; ++i) {
            int from, to;
            
            std::cin >> from >> to;
            
            adjacency_list[from].insert(to);
            adjacency_list[to].insert(from);
        }
        
        return Graph{std::move(adjacency_list)};
    }
    
    void PrintDFS(std::ostream& output_stream, VertexId starting_vertex) const {
        auto colors = GetArrayOfColor(Color::White);
        
        DFS(starting_vertex, colors, [&output_stream](VertexId vertex){
            output_stream << vertex << ' ';
        });
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
    }
    
private:
    AdjacencyList adjacency_list_;
};

int main() {
    auto graph = Graph::ReadUndirectedGraph(std::cin);
    
    VertexId starting_vertex;
    
    std::cin >> starting_vertex;
    
    graph.PrintDFS(std::cout, starting_vertex);
    
    return 0;
}
