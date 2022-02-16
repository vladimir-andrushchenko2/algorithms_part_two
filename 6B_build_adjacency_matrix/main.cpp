#include <iostream>
#include <vector>

int main(int argc, const char * argv[]) {
    int vertexes_count, edges_count;
    std::cin >> vertexes_count >> edges_count;
    
    std::vector<int> row(vertexes_count);
    std::vector<std::vector<int>> matrix(row.size(), row);
    
    for (int i = 0; i < edges_count; ++i) {
        
    }
    
    return 0;
}
