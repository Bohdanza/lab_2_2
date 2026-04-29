#pragma once

#include "baseGraph.hpp"

#include <optional>
#include <vector>

namespace graph
{
    class AdjacencyMatrixGraph : public BaseGraph
    {
        public:
            void addVertex(int id, const std::string& label) override;
            void removeVertex(int id) override;
            void addEdge(int from, int to, const std::string& label) override;
            void removeEdge(int from, int to) override;

            std::vector<Vertex> getVertices() const override;
            std::vector<Edge> getEdges() const override;

        private:
            std::vector<Vertex> vertices_;
            std::vector<std::vector<std::optional<std::string>>> matrix_;

            int indexOf(int id) const;
    };
}