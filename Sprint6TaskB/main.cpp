#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <cassert>
#include <functional>
#include <numeric>
#include <utility>
#include <queue>

/*
 -- ПРИНЦИП РАБОТЫ --
 Создается граф в котором грани B будут обратными, если найден цикл, значит из города в А в город B существует альтернативный путь и система дорог не эффективна.
 
 -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 Для хранения матрицы используется список смежности, а для поиска цикла используется поиск в глубину.
 Временная сложность поиска O(V+E), где V это вершины, а E рёбра.

 -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 Для решения алгоритма нужно хранить список смежности O(|V|+|E|) и цвета вершин (|V|).
 */


using VertexId = int;

using AdjacencyList = std::vector<std::vector<VertexId>>;

using Matrix = std::vector<std::string>;

enum class Color {
    White, Gray, Black
};

struct Graph {
public:
    Graph() = delete;
    
    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}

    bool ContainsLoop() {
        auto vertex_color = GetArrayOfColor(Color::White);

        std::stack<VertexId> stack;

        for (VertexId starting_vertex = 0; starting_vertex < adjacency_list_.size(); ++starting_vertex) {
            if (vertex_color[starting_vertex] == Color::White) {
                stack.push(starting_vertex);

                while (!stack.empty()) {
                    auto vertex_id = stack.top();

                    if (vertex_color[vertex_id] == Color::White) {
                        // paint gray
                        vertex_color[vertex_id] = Color::Gray;

                        // add ajacent vertexes_to_the_stack
                        for (auto adjacent_vertex_id : adjacency_list_[vertex_id]) {
                            if (vertex_color[adjacent_vertex_id] == Color::Gray) {
                                return true;
                            }

                            if (vertex_color[adjacent_vertex_id] == Color::White) {
                                stack.push(adjacent_vertex_id);
                            }
                        }

                    } else {
                        stack.pop();

                        vertex_color[vertex_id] = Color::Black;
                    }
                }
            }
        }

        return false;
    }
    
private:
    std::vector<Color> GetArrayOfColor(Color color) const {
        return {adjacency_list_.size(), color};
    }
    
private:
    AdjacencyList adjacency_list_;
};

Graph ReadGraph(std::istream& input) {
    int vertexes_count;
    
    input >> vertexes_count >> std::ws;
    
    AdjacencyList adjacency_list(vertexes_count);
    
    std::string row;
    
    const int rows_to_read = vertexes_count - 1;
    
    for (VertexId from_vertex_id = 0; from_vertex_id < rows_to_read; ++from_vertex_id) {
        std::getline(input, row);
        
        for (int j = 0; j < row.size(); ++j) {
            VertexId to_vertex_id = from_vertex_id + j + 1;
            
            if (row[j] == 'B') {
                adjacency_list[to_vertex_id].push_back(from_vertex_id);
            } else {
                adjacency_list[from_vertex_id].push_back(to_vertex_id);
            }
        }
    }
    
    return Graph{std::move(adjacency_list)};
}

int main() {
    if (ReadGraph(std::cin).ContainsLoop()) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }
    
    return 0;
}
