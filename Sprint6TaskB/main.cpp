#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>
#include <deque>

// Changed railroad types from R and B to Red and Blue to distinguish better
enum class RailroadType {
    Red, Blue
};

using VertexId = int;

using AdjacencyList = std::vector<std::set<VertexId>>;

AdjacencyList MakeAdjacencyList(int vertex_count) {
    return AdjacencyList(vertex_count + 1);
}

struct City {
    std::deque<VertexId> roads_to_cities;
};

class Graph {
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
    
    void PrintDFS(std::ostream& output_stream) const {
        auto is_visited = GetVisitedStatus();
        
        for (int i = 1; i < adjacency_list_.size(); ++i) {
            if (!is_visited[i]) {
                DFS(i, is_visited, [&output_stream](VertexId vertex){
                    output_stream << vertex << ' ';
                });
            }
        }
    }
    
    void DFS(std::vector<City>& cities) const {
        for (VertexId starting_city_id = 1; starting_city_id < adjacency_list_.size(); ++starting_city_id) {
            auto is_visited = GetVisitedStatus();
            
            std::deque<VertexId> visited_vertexes;
            
            DFS(starting_city_id, is_visited, [&cities, starting_city_id](VertexId vertex){
                cities[starting_city_id].roads_to_cities.push_back(vertex);
            });
        }
    }
    
    int AdjacencyListSize() const {
        return static_cast<int>(adjacency_list_.size());
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

void PrintCitiesConnections(const std::vector<City>& cities) {
    for (VertexId city_id = 1; city_id < cities.size(); ++ city_id) {
        std::cout << "city_id: " << city_id << " has roads leading to ";
        
        for (VertexId connected_city : cities[city_id].roads_to_cities) {
            std::cout << connected_city << ' ';
        }
        
        std::cout << '\n';
    }
}

int main(int argc, const char * argv[]) {
    std::stringstream test_stream{test_string};
    
    auto [red_graph, blue_graph] = ReadDirectedGraphs(test_stream);
    
    std::vector<City> cities_on_red_network(red_graph.AdjacencyListSize());
    
    red_graph.DFS(cities_on_red_network);
    
    PrintCitiesConnections(cities_on_red_network);
    
    std::cout << '\n';
    
    std::vector<City> cities_on_blue_network(blue_graph.AdjacencyListSize());
    
    blue_graph.DFS(cities_on_blue_network);
    
    PrintCitiesConnections(cities_on_blue_network);
    
//    for (VertexId city_id = 1; city_id < cities_on_red_network.size(); ++ city_id) {
//        std::cout << "city_id: " << city_id << " has roads leading to ";
//
//        for (VertexId connected_city : cities_on_red_network[city_id].roads_to_cities) {
//            std::cout << connected_city << ' ';
//        }
//
//        std::cout << '\n';
//    }
    
    
    
    return 0;
}
