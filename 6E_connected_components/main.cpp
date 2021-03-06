#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <cassert>
#include <functional>
#include <numeric>
#include <utility>

using VertexId = int;
using AdjacencyList = std::vector<std::set<VertexId>>;

enum class Color {
    White, Gray, Black
};

struct Graph {
public:
    Graph() = delete;
    
    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {
        InitializeConnectedGroups();
    }
    
    const auto& GetConnectedGroups() const {
        return connected_groups_;
    }
    
private:
    template<typename Predicate>
    void DFS(VertexId start_id, std::vector<bool>& is_visited, Predicate predicate) {
        predicate(start_id);
        
        is_visited[start_id] = true;
        
        for (VertexId adjacent_vertex : adjacency_list_[start_id]) {
            if (!is_visited[adjacent_vertex]) {
                DFS(adjacent_vertex, is_visited, predicate);
            }
        }
    }
    
    void InitializeConnectedGroups() {
        std::vector<bool> is_visited(adjacency_list_.size(), false);
        
        for (int i = 1; i < adjacency_list_.size(); ++i) {
            if (!is_visited[i]) {
                auto& new_group = connected_groups_.emplace_back();
                
                DFS(i, is_visited, [&new_group](VertexId id) {
                    new_group.insert(id);
                });
            }
        }
    }
    
private:
    const AdjacencyList& adjacency_list_;
    std::vector<std::set<int>> connected_groups_;
};

int main() {
    int vertexes_count, edges_count;
    
    std::cin >> vertexes_count >> edges_count;
    
    AdjacencyList adjacency_list(vertexes_count + 1);
    
    std::string line;
    
    for (int i = 0; i < edges_count; ++i) {
        int from, to;
        
        std::cin >> from >> to;
        
        adjacency_list[from].insert(to);
        adjacency_list[to].insert(from);
    }
    
    Graph graph(adjacency_list);
    
    std::cout << graph.GetConnectedGroups().size() << '\n';
    
    for (const auto& connected_group : graph.GetConnectedGroups()) {
        for (VertexId vertex_id : connected_group) {
            std::cout << vertex_id << ' ';
        }
        
        std::cout << '\n';
    }
    
    return 0;
}
