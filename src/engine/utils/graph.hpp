#pragma once

#include <memory>
#include <queue>
#include <vector>

namespace engine::utils {
    class Graph;

    class Node {
        friend Graph;

      protected:
        std::vector<std::shared_ptr<Node>> m_inNeighbours;
        std::vector<std::shared_ptr<Node>> m_outNeighbours;
    };

    class Graph {
      public:
        void addNode(const std::shared_ptr<Node>& node);

        void sort();

        std::vector<std::shared_ptr<Node>> getNodes();

      private:
        std::vector<std::shared_ptr<Node>> m_nodes;
    };
} // namespace engine::utils