#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>
#include <deque>
#include <cassert>

using VertexId = int;

using AdjacencyList = std::vector<std::set<VertexId>>;

AdjacencyList MakeAdjacencyList(int vertex_count) {
    return AdjacencyList(vertex_count + 1);
}

struct City {
    std::unordered_map<VertexId, char> accessible_to_cities;
};

class Graph {
public:
    Graph() = delete;
    
    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}
    
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

bool ConnectCitiesAccordingToGraphWithRoadsOfType(std::vector<City>& cities, const Graph& graph, char type) {
    std::vector<bool> is_visited(graph.AdjacencyListSize(), false);
    
    bool is_duplicate_route_fount = false;
    
    // replace 1 with constant
    for (VertexId starting_city_id = 1; starting_city_id < cities.size(); ++starting_city_id) {
        if (!is_visited[starting_city_id]) {
            std::vector<VertexId> already_reached_cities;
            
            graph.DFS(starting_city_id, [&](VertexId current_city){
                is_visited[current_city] = true;
                
                for (VertexId previously_visited : already_reached_cities) {
                    auto& cities_have_access_to_current_city = cities[current_city].accessible_to_cities;
                    
                    if (cities_have_access_to_current_city.count(previously_visited) > 0 && cities_have_access_to_current_city[previously_visited] != type) {
                        is_duplicate_route_fount = true;
                    }
                    
                    cities_have_access_to_current_city[previously_visited] = type;
                }
                
                already_reached_cities.push_back(current_city);
            });
        }
        
        if (is_duplicate_route_fount) {
            return false;
        }
    }
    
    assert(false);
    return true;
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

int main(int argc, const char * argv[]) {
    auto [red_graph, blue_graph] = ReadDirectedGraphs(std::cin);
    
    bool is_optimal = IsRailwayNetworkOptimal(RunDFSFromEachCity(red_graph), RunDFSFromEachCity(blue_graph));
    
    if (is_optimal) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    
    return 0;
}
