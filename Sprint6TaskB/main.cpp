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
#include <deque>

using VertexId = int;

static constexpr VertexId kFirstId = 1;

using AdjacencyList = std::vector<std::set<VertexId>>;

AdjacencyList MakeAdjacencyList(int vertex_count) {
    return AdjacencyList(kFirstId + vertex_count);
}

struct City {
    std::unordered_map<VertexId, char> from;
};

class Graph {
public:
    Graph() = delete;
    
    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}
    
    template <typename Predicate>
    void DFS(VertexId starting_vertex, Predicate predicate) const {
        auto is_visited = GetVisitedStatus();
        
        std::deque<VertexId> previous;
        
        DFS(starting_vertex, is_visited, previous, predicate);
    }
    
    int AdjacencyListSize() const {
        return static_cast<int>(adjacency_list_.size());
    }
    
private:
    std::vector<bool> GetVisitedStatus() const {
        return std::vector(adjacency_list_.size(), false);
    }
    
    template<typename Predicate>
    void DFS(VertexId start_id, std::vector<bool>& is_visited, std::deque<VertexId>& previous, Predicate predicate) const {
        predicate(start_id, previous);
        
        previous.push_back(start_id);
        
        is_visited[start_id] = true;
        
        for (VertexId adjacent_vertex : adjacency_list_[start_id]) {
            if (!is_visited[adjacent_vertex]) {
                DFS(adjacent_vertex, is_visited, previous, predicate);
            }
        }
        
        previous.pop_back();
    }
    
private:
    AdjacencyList adjacency_list_;
};

void ConnectCitiesAccordingToGraphWithRoadsOfType(std::vector<City>& cities, const Graph& graph, char type) {
    std::vector<bool> is_visited(graph.AdjacencyListSize(), false);
    
    for (VertexId starting_city_id = kFirstId; starting_city_id < cities.size(); ++starting_city_id) {
        if (!is_visited[starting_city_id]) {
            graph.DFS(starting_city_id, [&](VertexId current_city, const std::deque<VertexId>& previous){
                is_visited[current_city] = true;
                    
                for (VertexId previously_visited : previous) {
                    if (cities[current_city].from.count(previously_visited) > 0 && cities[current_city].from[previously_visited] != type) {
                        throw std::logic_error("duplicate connection of different road types");
                    }
                    
                    cities[current_city].from[previously_visited] = type;
                }
            });
        }
    }
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


// TODO: try first reading and connecting one by one


int main(int argc, const char * argv[]) {
    auto [red_graph, blue_graph] = ReadDirectedGraphs(std::cin);
    
    std::vector<City> cities(red_graph.AdjacencyListSize());
    
    try {
        ConnectCitiesAccordingToGraphWithRoadsOfType(cities, red_graph, 'R');
        
        ConnectCitiesAccordingToGraphWithRoadsOfType(cities, blue_graph, 'B');
    
        std::cout << "YES\n";
        
    } catch (std::logic_error error) {
        std::cout << "NO\n";
    }
    
    return 0;
}
