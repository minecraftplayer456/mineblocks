#include "Graph.hpp"

#include <utility>

namespace Engine {
    Graph::Graph(std::vector<Node*> p_Nodes)
        : m_Nodes(std::move(p_Nodes))
    {
    }

    void Graph::SortDependencies()
    {

        std::queue<Node*> free;

        for (Node* node : m_Nodes) {
            if (node->m_InNeighbours.empty()) {
                free.push(node);
            }
        }

        std::vector<Node*> sorted;

        while (!free.empty()) {
            Node* top = free.front();
            sorted.push_back(top);
            free.pop();

            for (int i = 0; i < top->m_OutNeighbours.size(); i++) {
                Node* neighbour = top->m_OutNeighbours[i];

                auto it = std::find(neighbour->m_InNeighbours.begin(),
                                    neighbour->m_InNeighbours.end(), top);
                neighbour->m_InNeighbours.erase(it);

                if (neighbour->m_InNeighbours.empty()) {
                    free.push(neighbour);
                }
            }
        }

        m_SortedNodes = sorted;
    }

    std::vector<Node*> Graph::GetNodes() const
    {
        return m_Nodes;
    }

    std::vector<Node*> Graph::GetSortedNodes() const
    {
        return m_SortedNodes;
    }
} // namespace Engine