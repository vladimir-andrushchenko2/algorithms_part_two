#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Changed railroad types from R and B to Red and Blue to distinguish better
enum class RailroadType {
    Red, Blue
};

using VertexId = int;

using AdjacencyList = std::vector<std::unordered_set<VertexId>>;

AdjacencyList MakeAdjacencyList(int vertex_count) {
    return AdjacencyList(vertex_count + 1);
}

struct Graph {
public:
    Graph() = delete;
    
    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}
    
    void PrintDFS(std::ostream& output_stream, VertexId starting_vertex) const {
        auto is_visited = GetVisitedStatus();
        
        DFS(starting_vertex, is_visited, [&output_stream](VertexId vertex){
            output_stream << vertex << ' ';
        });
    }
    
    
private:
    std::vector<bool> GetVisitedStatus() const {
        return std::vector(adjacency_list_.size(), false);
    }
    
    template<typename Predicate>
    void DFS(VertexId start_id, std::vector<bool>& is_visited, Predicate predicate) const {
        predicate(start_id);
        
        is_visited[start_id] = true;
        
        for (VertexId adjacent_vertex : adjacency_list_[start_id]) {
            if (!is_visited[adjacent_vertex]) {
                DFS(adjacent_vertex, is_visited, predicate);
            }
        }
    }
    
private:
    AdjacencyList adjacency_list_;
};

std::vector<std::string> ReadRailwayMap(std::istream& input_stream) {
    int n_cities;
    
    input_stream >> n_cities;
    
    std::vector<std::string> output;
    
    for (int i = 0; i < n_cities; ++i) {
        auto& connections_to_other_cities = output.emplace_back();
        std::getline(input_stream, connections_to_other_cities);
    }
    
    return output;
}

Graph ReadDirectedGraph(std::istream& input) {
    int vertexes_count;
    
    std::cin >> vertexes_count;
    
    AdjacencyList adjacency_list_red(vertexes_count + 1);
    AdjacencyList adjacency_list_blue(vertexes_count + 1);
    
    std::string connections_to_other_cities;
    
    for (VertexId from_vertex_id = 1; from_vertex_id < vertexes_count; ++from_vertex_id) {
        std::getline(input, connections_to_other_cities);
        
        // WARNING: unfinished here
        for (int j = 0; j < connections_to_other_cities.size(); ++j) {
            char road_type = connections_to_other_cities[j];
            
            assert(false);
            VertexId to_vertex_id = from_vertex_id + j + 1;
            if (road_type == 'R') {
                adjacency_list_red[from_vertex_id].insert(<#value_type &&__x#>)
            }
        }
    }
    
    assert(false);
}

int main(int argc, const char * argv[]) {
    auto country = ReadRailwayMap(std::cin);
    
    for (auto& connections : country) {
        std::cout << connections << '\n';
    }
    
    return 0;
}
