#include <iostream>
#include <vector>

int main() {
    int vertexes_count, edges_count;
    
    std::cin >> vertexes_count >> edges_count;
    
    std::vector<std::vector<int>> adjacency_list(vertexes_count);
    
    std::string line;
    
    for (int i = 0; i < edges_count; ++i) {
        int from, to;
        
        std::cin >> from >> to;
        
        adjacency_list[from - 1].push_back(to);
    }
    
    for (auto adjacent_nodes : adjacency_list) {
        std::cout << adjacent_nodes.size() << ' ';

        for (auto to : adjacent_nodes) {
            std::cout << to << ' ';
        }

        std::cout << '\n';
    }
    
    return 0;
}
