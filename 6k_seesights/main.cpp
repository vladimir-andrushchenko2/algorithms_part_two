#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <cassert>
#include <functional>
#include <numeric>
#include <utility>
#include <queue>
#include <optional>
#include <limits>
#include <unordered_map>

using VertexId = int;

using Weight = int;

static constexpr int kInfinity = std::numeric_limits<int>::max();

static constexpr VertexId kNoneVertexId = -1;

static constexpr VertexId kFirstVertexId = 1;

using AdjacencyList = std::vector<std::unordered_map<VertexId, Weight>>;

using Matrix = std::vector<std::vector<int>>;

struct Graph {
public:
    Graph() = delete;

    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}

    VertexId GetMinDistanceUnvisitedVertex() {
        int current_minimum = kInfinity;
        VertexId current_minimum_vertex = kNoneVertexId;
        
        for (auto vertex_id = kFirstVertexId; vertex_id < adjacency_list_.size(); ++vertex_id) {
            if (!is_visited_[vertex_id] && distance_[vertex_id]  < current_minimum) {
                current_minimum = distance_[vertex_id];
                current_minimum_vertex = vertex_id;
            }
        }
        
        return current_minimum_vertex;
    }
    
    bool ContainsReachableButUnvisitedVertexes() {
        static constexpr VertexId first_vertex_id = kFirstVertexId;

        for (auto vertex_id = first_vertex_id; vertex_id < adjacency_list_.size(); ++vertex_id) {
            if (!is_visited_[vertex_id] && distance_[vertex_id] != kInfinity) {
                return true;
            }
        }
        
        return false;
    }

    Weight Weight(VertexId from, VertexId to) {
        return adjacency_list_.at(from).at(to);
    }

    void Relax(VertexId from, VertexId to) {
        if (distance_[to] > distance_[from] + Weight(from, to)) {
            distance_[to] = distance_[from] + Weight(from, to);
            previous_[to] = from;
        }
    }

    void ResetData() {
        distance_ = std::vector<Weight>(adjacency_list_.size(), kInfinity);

        previous_ = std::vector<VertexId>(adjacency_list_.size(), kNoneVertexId);

        is_visited_ = std::vector<bool>(adjacency_list_.size(), false);
    }

    std::pair<std::vector<Weight>, std::vector<bool>> Dijkstra(VertexId starting_vertex) {
        ResetData();

        distance_[starting_vertex] = 0;

        while (ContainsReachableButUnvisitedVertexes()) {
            VertexId min_distance_univisited_vertex = GetMinDistanceUnvisitedVertex();

            is_visited_[min_distance_univisited_vertex] = true;

            const auto neigbours = adjacency_list_.at(min_distance_univisited_vertex);

            for (auto [neighbour_vertex_id, weight] : neigbours) {
                Relax(min_distance_univisited_vertex, neighbour_vertex_id);
            }
        }

        return {std::move(distance_), std::move(is_visited_)};
    }

    int VertexCount() {
        return static_cast<int>(adjacency_list_.size());
    }

private:
    const AdjacencyList adjacency_list_;
    std::vector<Weight> distance_;
    std::vector<VertexId> previous_;
    std::vector<bool> is_visited_;
};

Graph ReadUndirectedGraph(std::istream& input) {
    int vertexes_count, edges_count;

    std::cin >> vertexes_count >> edges_count;

    AdjacencyList adjacency_list(vertexes_count + 1);

    std::string line;

    for (int i = 0; i < edges_count; ++i) {
        int from, to, weight;

        std::cin >> from >> to >> weight;

        // if two edges between vertexes save only one with smaller weight
        if (adjacency_list[from].count(to) == 0 || adjacency_list[from][to] > weight) {
            adjacency_list[from][to] = weight;
            adjacency_list[to][from] = weight;
        }
    }

    return Graph{std::move(adjacency_list)};
}

int main() {
    auto graph = ReadUndirectedGraph(std::cin);

    for (int i = 1; i < graph.VertexCount(); ++i) {
        auto [distances, is_visited] = graph.Dijkstra(i);

        for (int j = 1; j < graph.VertexCount(); ++j) {
            if (is_visited[j]) {
                std::cout << distances[j] << ' ';
            } else {
                std::cout << -1 << ' ';
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
