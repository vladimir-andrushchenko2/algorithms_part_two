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

struct Edge {
    VertexId from = kNoneVertexId;
    VertexId to = kNoneVertexId;
    Weight weight{};
};

bool operator<(const Edge& left, const Edge& right) {
    return left.weight < right.weight;
}

struct Graph {
public:
    Graph() = delete;

    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}

    int VertexCount() const {
        return static_cast<int>(adjacency_list_.size());
    }

    std::optional<Weight> MaxSpanningTree() const {
        std::vector<bool> is_in_spanning_tree(VertexCount(), false);

        std::priority_queue<Edge, std::greater<>> 


    }

private:
    const AdjacencyList adjacency_list_;
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

    return 0;
}
