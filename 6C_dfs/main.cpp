#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <cassert>
#include <functional>

using VertexId = int;
using AdjacencyList = std::vector<std::set<VertexId, std::greater<>>>;

enum class Color {
    White, Gray, Black
};

std::vector<VertexId> DFS(int start_vertex, const AdjacencyList& adjacency_list) {
    std::vector<Color> vertex_color(adjacency_list.size(), Color::White);

    std::vector<VertexId> output;

    std::stack<VertexId> stack;

    stack.push(start_vertex);

    while (!stack.empty()) {
        auto vertex_id = stack.top();

        if (vertex_color[vertex_id] == Color::White) {
            output.push_back(vertex_id);

            // paint gray
            vertex_color[vertex_id] = Color::Gray;

            // add ajacent vertexes_to_the_stack
            for (auto adjacent_vertex_id : adjacency_list[vertex_id]) {
                if (vertex_color[adjacent_vertex_id] == Color::White) {
                    stack.push(adjacent_vertex_id);
                }
            }

        } else {
            stack.pop();
            
            vertex_color[vertex_id] = Color::Black;
        }
    }

    return output;
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
        adjacency_list[to].insert(from);
    }

    int starting_vertex;

    std::cin >> starting_vertex;

    for (VertexId vertex_id : DFS(starting_vertex, adjacency_list)) {
        std::cout << vertex_id << ' ';
    }

    std::cout << '\n';

    return 0;
}
