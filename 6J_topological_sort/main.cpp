#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <cassert>
#include <functional>
#include <numeric>

using VertexId = int;
using AdjacencyList = std::vector<std::set<VertexId>>;

enum class Color {
    White, Gray, Black
};

struct Graph {
    Graph() = delete;
    
    Graph(const AdjacencyList& adjacency_list) :
    adjacency_list(adjacency_list),
    vertex_color(adjacency_list.size(), Color::White) {}
    
    Color& GetVertexColor(VertexId id) {
        return vertex_color[id];
    }
    
    const AdjacencyList& adjacency_list;
    std::vector<Color> vertex_color;
    std::deque<VertexId> order;
};

void TopSort(Graph& graph, VertexId vertex_id) {
    graph.GetVertexColor(vertex_id) = Color::Gray;
    
    for (auto adjacent_vertex : graph.adjacency_list[vertex_id]) {
        if (graph.GetVertexColor(vertex_id) == Color::White) {
            TopSort(graph, adjacent_vertex);
        }
    }
    
    graph.GetVertexColor(vertex_id) = Color::Black;
    
    graph.order.push_back(vertex_id);
}

auto MainTopSort(const AdjacencyList& adjacency_list) {
    if (adjacency_list.begin() == adjacency_list.end()) {
        return std::deque<VertexId>{};
    }
    
    Graph graph(adjacency_list);
    
    for (int i = 1; i < adjacency_list.size(); ++i) {
        if (graph.GetVertexColor(i) == Color::White) {
            TopSort(graph, i);
        }
    }
    
    return std::move(graph.order);
}

int main() {
    int vertexes_count, edges_count;
    
    std::cin >> vertexes_count >> edges_count;
    
    AdjacencyList adjacency_list(vertexes_count + 1);
    
    std::string line;
    
    for (int i = 0; i < edges_count; ++i) {
        int from, to;
        
        std::cin >> from >> to;
        
        adjacency_list[from].insert(to);
    }
    
    for (VertexId vertex_id : MainTopSort(adjacency_list)) {
        std::cout << vertex_id << ' ';
    }
    
    std::cout << '\n';
    
    return 0;
}
