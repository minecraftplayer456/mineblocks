#include "graph.hpp"

namespace engine::utils {
    void Graph::addNode(const std::shared_ptr<Node>& node)
    {
        m_nodes.push_back(node);
    }

    std::vector<std::shared_ptr<Node>> Graph::getNodes()
    {
        return m_nodes;
    }

    void Graph::sort()
    {
        std::queue<std::shared_ptr<Node>> free;

        for (const std::shared_ptr<Node>& node : m_nodes) {
            if (node->m_inNeighbours.empty()) {
                free.push(node);
            }
        }

        std::vector<std::shared_ptr<Node>> sorted;

        while (!free.empty()) {
            std::shared_ptr<Node> top = free.front();
            sorted.push_back(top);
            free.pop();

            for (int i = 0; i < top->m_outNeighbours.size(); i++) {
                std::shared_ptr<Node> neighbour = top->m_outNeighbours[i];

                neighbour->m_inNeighbours.erase(
                    std::find(neighbour->m_inNeighbours.begin(),
                              neighbour->m_inNeighbours.end(), top));

                if (neighbour->m_inNeighbours.empty()) {
                    free.push(neighbour);
                }
            }
        }

        m_nodes = sorted;
    }
} // namespace engine::utils