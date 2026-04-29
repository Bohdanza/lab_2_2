#pragma once

#include "baseGraph.hpp"

#include <vector>

namespace graph
{
    class AdjacencyListGraph : public BaseGraph
    {
        public:
            AdjacencyListGraph() = default;
            explicit AdjacencyListGraph(const std::string& filename);

            void addVertex(int id, const std::string& label, int weight = -1) override;
            void removeVertex(int id) override;
            void addEdge(int from, int to, const std::string& label, int weight = 0) override;
            void removeEdge(int from, int to) override;

            std::vector<Vertex> getVertices() const override;
            std::vector<Edge> getEdges() const override;

        private:
            struct Neighbor
            {
                    int toId;
                    std::string label;
                    int weight;
            };

            std::vector<Vertex> vertices_;
            std::vector<std::vector<Neighbor>> adj_;

            int indexOf(int id) const;
    };
}
