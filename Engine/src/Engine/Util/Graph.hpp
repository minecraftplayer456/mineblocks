#pragma once

namespace Engine {
    class Graph;

    class Node {
        friend Graph;

      protected:
        std::vector<Node*> inNeighbours = {};
        std::vector<Node*> outNeighbours = {};
    };

    class Graph {
      public:
        explicit Graph(std::vector<Node*> nodes);

        void SortDependencies();

        [[nodiscard]] auto GetNodes() const -> std::vector<Node*>;
        [[nodiscard]] auto GetSortedNodes() const -> std::vector<Node*>;

      private:
        std::vector<Node*> nodes;
        std::vector<Node*> sortedNodes;
    };
} // namespace Engine
