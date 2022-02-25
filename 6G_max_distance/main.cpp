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

using VertexId = int;

static constexpr VertexId kNoneVertexId = -1;

using AdjacencyList = std::vector<std::set<VertexId>>;

enum class Color {
    White, Gray, Black
};

struct Graph {
public:
    Graph() = delete;

    Graph(AdjacencyList adjacency_list) :
    adjacency_list_(std::move(adjacency_list)) {}

    static Graph ReadUndirectedGraph(std::istream& input) {
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

        return Graph{std::move(adjacency_list)};
    }

    int GetMaxDistanceFrom(VertexId start_id) const {
        auto colors = GetArrayOfColor(Color::White);

        std::vector<VertexId> previous(adjacency_list_.size(), kNoneVertexId);
        std::vector<int> distance(adjacency_list_.size());


        BFS(start_id, colors, [&previous, &distance, &colors](VertexId from_vertex_id, VertexId to_vertex_id){
            if (from_vertex_id == kNoneVertexId) {
                return;
            }

            distance[to_vertex_id] = distance[from_vertex_id] + 1;
            previous[to_vertex_id] = from_vertex_id;
        });

        return *std::max_element(distance.begin(), distance.end());
    }

private:
    std::vector<Color> GetArrayOfColor(Color color) const {
        return {adjacency_list_.size(), color};
    }

    template<typename Predicate>
    void BFS(VertexId start_id, std::vector<Color>& color_of, Predicate predicate) const {
        predicate(kNoneVertexId, start_id);

        color_of[start_id] = Color::Gray;

        std::queue<VertexId> planned;

        planned.push(start_id);

        while (!planned.empty()) {
            VertexId vertex_which_neighbours_need_to_be_processed = planned.front();

            planned.pop();

            for (VertexId adjacent_vertex : adjacency_list_[vertex_which_neighbours_need_to_be_processed]) {
                if (color_of[adjacent_vertex] == Color::White) {
                    predicate(vertex_which_neighbours_need_to_be_processed, adjacent_vertex);

                    color_of[adjacent_vertex] = Color::Gray;

                    planned.push(adjacent_vertex);
                }
            }

            color_of[vertex_which_neighbours_need_to_be_processed] = Color::Black;
        }
    }

private:
    AdjacencyList adjacency_list_;
};

int main() {
    auto graph = Graph::ReadUndirectedGraph(std::cin);

    VertexId starting_vertex;

    std::cin >> starting_vertex;

    std::cout << graph.GetMaxDistanceFrom(starting_vertex);

    return 0;
}
