#pragma once

namespace Engine {
    class Graph;

    class Node {
        friend Graph;

      protected:
        std::vector<Node*> m_InNeighbours;
        std::vector<Node*> m_OutNeighbours;
    };

    class Graph {
      public:
        explicit Graph(std::vector<Node*> p_Nodes);

        void SortDependencies();

        [[nodiscard]] std::vector<Node*> GetNodes() const;
        [[nodiscard]] std::vector<Node*> GetSortedNodes() const;

      private:
        std::vector<Node*> m_Nodes;
        std::vector<Node*> m_SortedNodes;
    };
} // namespace Engine
