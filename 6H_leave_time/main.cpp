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

struct Time {
    int in{};
    int out{};
};

std::vector<Time> DFS(int start_vertex, const AdjacencyList& adjacency_list) {
    int time{};
    
    std::vector<Color> vertex_color(adjacency_list.size(), Color::White);

    std::vector<Time> output(adjacency_list.size());

    std::stack<VertexId> stack;

    stack.push(start_vertex);

    while (!stack.empty()) {
        auto vertex_id = stack.top();

        if (vertex_color[vertex_id] == Color::White) {
            output[vertex_id].in = time++;

            // paint gray
            vertex_color[vertex_id] = Color::Gray;

            // add ajacent vertexes_to_the_stack
            for (auto adjacent_vertex_id : adjacency_list[vertex_id]) {
                if (vertex_color[adjacent_vertex_id] == Color::White) {
                    stack.push(adjacent_vertex_id);
                }
            }

        } else {
            vertex_color[vertex_id] = Color::Black;
            output[vertex_id].out = time++;
            stack.pop();
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
    }

    constexpr int kStartingVertex = 1;

    for (auto time : DFS(kStartingVertex, adjacency_list)) {
        std::cout << time.in << ' ' << time.out << '\n';
    }
    
    return 0;
}
