#include "Graph.hpp"

#include <utility>

namespace Engine {
    Graph::Graph(std::vector<Node*> nodes)
        : nodes(std::move(nodes))
    {
    }

    void Graph::SortDependencies()
    {

        std::queue<Node*> free;

        for (Node* node : nodes) {
            if (node->inNeighbours.empty()) {
                free.push(node);
            }
        }

        std::vector<Node*> sorted;

        while (!free.empty()) {
            Node* top = free.front();
            sorted.push_back(top);
            free.pop();

            for (int i = 0; i < top->outNeighbours.size(); i++) {
                Node* neighbour = top->outNeighbours[i];

                auto it = std::find(neighbour->inNeighbours.begin(),
                                    neighbour->inNeighbours.end(), top);
                neighbour->inNeighbours.erase(it);

                if (neighbour->inNeighbours.empty()) {
                    free.push(neighbour);
                }
            }
        }

        sortedNodes = sorted;
    }

    auto Graph::GetNodes() const -> std::vector<Node*>
    {
        return nodes;
    }

    auto Graph::GetSortedNodes() const -> std::vector<Node*>
    {
        return sortedNodes;
    }
} // namespace Engine