#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>
#include <deque>

using VertexId = int;

using AdjacencyList = std::vector<std::set<VertexId>>;

AdjacencyList MakeAdjacencyList(int vertex_count) {
    return AdjacencyList(vertex_count + 1);
}

struct City {
    std::unordered_set<VertexId> roads_to_cities;
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
    
    template <typename Predicate>
    void DFS(VertexId starting_vertex, Predicate predicate) const {
        auto is_visited = GetVisitedStatus();
        
        DFS(starting_vertex, is_visited, predicate);
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

auto RunDFSFromEachCity(Graph graph) {
    std::vector<City> cities(graph.AdjacencyListSize());
    
    for (VertexId starting_city_id = 1; starting_city_id < cities.size(); ++starting_city_id) {
        graph.DFS(starting_city_id, [&cities, starting_city_id](VertexId vertex){
            if (starting_city_id != vertex) {
                cities[starting_city_id].roads_to_cities.insert(vertex);
            }
        });
    }
    
    return cities;
}

std::pair<Graph, Graph> ReadDirectedGraphs(std::istream& input) {
    int vertexes_count;
    
    input >> vertexes_count >> std::ws;
    
    auto adjacency_list_red = MakeAdjacencyList(vertexes_count);
    
    auto adjacency_list_blue = MakeAdjacencyList(vertexes_count);
    
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

const std::string test_string = R"d(3
RB
R


)d";

void PrintCitiesConnections(const std::vector<City>& cities) {
    for (VertexId city_id = 1; city_id < cities.size(); ++ city_id) {
        if (!cities[city_id].roads_to_cities.empty()) {
            std::cout << "city_id: " << city_id << " has roads leading to ";
        }
        
        for (VertexId connected_city : cities[city_id].roads_to_cities) {
            std::cout << connected_city << ' ';
        }
        
        std::cout << '\n';
    }
}

bool IsRailwayNetworkOptimal(std::vector<City> red_network, std::vector<City> blue_network) {
    assert(red_network.size() == blue_network.size());
    
    for (VertexId from_city_id = 1; from_city_id < red_network.size(); ++from_city_id) {
        auto red_destinations = red_network[from_city_id].roads_to_cities;
        auto blue_destinations = blue_network[from_city_id].roads_to_cities;
        
        for (auto red_destination : red_destinations) {
            if (blue_destinations.count(red_destination)) {
                return false;
            }
        }
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    std::stringstream test_stream{test_string};
    
    auto [red_graph, blue_graph] = ReadDirectedGraphs(test_stream);
    
    bool is_optimal = IsRailwayNetworkOptimal(RunDFSFromEachCity(red_graph), RunDFSFromEachCity(blue_graph));
    
    if (is_optimal) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    
    return 0;
}
