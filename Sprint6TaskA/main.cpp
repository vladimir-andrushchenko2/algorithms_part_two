// 66251609
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
#include <queue>

/*
-- ПРИНЦИП РАБОТЫ --
Используется алгоритм Прима в котором из всех исходящих ребер из остова выбирается с наибольшим весом и добавляется к остову.
 
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 O(∣E∣⋅log∣V∣) для поиска максимального остова нужно посетить все верщины и из каждой вершины проверить соседние
 использование очереди приоритетов помогает улучшить асимптотическую сложность

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 Для решения алгоритма нужно хранить список смежности O(|V|+|E|).
*/

using VertexId = int;

using Weight = int;

static constexpr VertexId kNoneVertexId = -1;

static constexpr VertexId kFirstVertexId = 1;

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
    using AdjacencyList = std::vector<std::unordered_map<VertexId, Weight>>;

public:
    Graph() = delete;

    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}

    int VertexCount() const {
        // - 1 because vector is used as associative container and element under index of 0 is ficticious
        return static_cast<int>(adjacency_list_.size()) - 1;
    }

    std::optional<Weight> WeightOfMaxSpanningTree() const {
        std::vector<bool> is_in_spanning_tree(VertexCount() + 1, false);

        std::priority_queue<Edge> edges_going_out_of_spanning_tree;

        int unvisited_vertex_counter = VertexCount();
        
        auto AddVertexToSpanningTree = [&](VertexId vertex_id) {
            if (!is_in_spanning_tree[vertex_id]) {
                --unvisited_vertex_counter;
                
                is_in_spanning_tree[vertex_id] = true;
                
                for (auto [adjacent_vertex_id, weight] : adjacency_list_[vertex_id]) {
                    if (!is_in_spanning_tree[adjacent_vertex_id]) {
                        edges_going_out_of_spanning_tree.push(Edge{vertex_id, adjacent_vertex_id, weight});
                    }
                }
            }
        };
        
        AddVertexToSpanningTree(kFirstVertexId);
        
        Weight weight_of_spanning_tree{};
        
        while (unvisited_vertex_counter > 0 && !edges_going_out_of_spanning_tree.empty()) {
            auto max_edge = edges_going_out_of_spanning_tree.top();
            
            edges_going_out_of_spanning_tree.pop();
            
            if (!is_in_spanning_tree[max_edge.to]) {
                weight_of_spanning_tree += max_edge.weight;
                AddVertexToSpanningTree(max_edge.to);
            }
        }
        
        if (unvisited_vertex_counter > 0) {
            return {};
        }
        
        return weight_of_spanning_tree;
    }

private:
    const AdjacencyList adjacency_list_;
};

Graph ReadUndirectedGraph(std::istream& input) {
    int vertexes_count, edges_count;

    std::cin >> vertexes_count >> edges_count;

    Graph::AdjacencyList adjacency_list(vertexes_count + 1);

    std::string line;

    for (int i = 0; i < edges_count; ++i) {
        int from, to, weight;

        std::cin >> from >> to >> weight;

        // if two edges between vertexes save only one with bigger weight
        if (adjacency_list[from].count(to) == 0 || adjacency_list[from][to] < weight) {
            adjacency_list[from][to] = weight;
            adjacency_list[to][from] = weight;
        }
    }

    return Graph{std::move(adjacency_list)};
}

int main() {
    auto graph = ReadUndirectedGraph(std::cin);
    
    if (auto weight = graph.WeightOfMaxSpanningTree()) {
        std::cout << *weight << '\n';
    } else {
        std::cout << "Oops! I did it again\n";
    }

    return 0;
}
