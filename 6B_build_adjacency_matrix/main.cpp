#include <iostream>
#include <vector>

int main(int argc, const char * argv[]) {
    int vertexes_count, edges_count;
    std::cin >> vertexes_count >> edges_count;
    
    std::vector<std::vector<int>> matrix(vertexes_count, std::vector<int>(vertexes_count));
    
    int from, to;
    
    for (int i = 0; i < edges_count; ++i) {
        std::cin >> from >> to;
        
        matrix[from - 1][to - 1] = 1;
    }
    
    for (auto& row : matrix) {
        for (auto& value : row) {
            std::cout << value << ' ';
        }
        
        std::cout << '\n';
    }
    
    return 0;
}
