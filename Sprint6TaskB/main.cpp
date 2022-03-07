#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>

// Changed railroad types from R and B to Red and Blue to distinguish better
enum class RailroadType {
    Red, Blue
};

using VertexId = int;

using AdjacencyList = std::vector<std::set<VertexId>>;

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

std::pair<Graph, Graph> ReadDirectedGraphs(std::istream& input) {
    int vertexes_count;
    
    input >> vertexes_count >> std::ws;
    
    AdjacencyList adjacency_list_red(vertexes_count + 1);

    AdjacencyList adjacency_list_blue(vertexes_count + 1);
    
    std::string connections_to_other_cities;
    
    for (VertexId from_vertex_id = 1; from_vertex_id < vertexes_count; ++from_vertex_id) {
        std::getline(input, connections_to_other_cities);
        
        for (int i = 0; i < connections_to_other_cities.size(); ++i) {
            char road_type = connections_to_other_cities[i];

            // + 1 because first cities first road leads to second city
            VertexId to_vertex_id = from_vertex_id + i + 1;

            if (road_type == 'R') {
                adjacency_list_red[from_vertex_id].insert(to_vertex_id);
            } else if (road_type == 'B') {
                adjacency_list_blue[from_vertex_id].insert(to_vertex_id);
            } else {
                assert(false && "Roadtype must be R for Red or B for Blue");
            }
        }
    }
    
    return {adjacency_list_red, adjacency_list_blue};
}

const std::string test_string = R"d(5
RRRB
BRR
BR
R
)d";

int main(int argc, const char * argv[]) {
    std::stringstream test_stream{test_string};
    
    auto [red_graph, blue_graph] = ReadDirectedGraphs(test_stream);
    
    blue_graph.PrintDFS(std::cout, 2);
    
    return 0;
}
