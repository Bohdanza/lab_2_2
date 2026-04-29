#pragma once

#include "baseGraph.hpp"

#include <vector>

namespace graph
{
    class EdgeListGraph : public BaseGraph
    {
        public:
            EdgeListGraph() = default;
            explicit EdgeListGraph(const std::string& filename);

            void addVertex(int id, const std::string& label, int weight = -1) override;
            void removeVertex(int id) override;
            void addEdge(int from, int to, const std::string& label, int weight = 0) override;
            void removeEdge(int from, int to) override;

            std::vector<Vertex> getVertices() const override;
            std::vector<Edge> getEdges() const override;

        private:
            std::vector<Vertex> vertices_;
            std::vector<Edge> edges_;

            bool hasVertex(int id) const;
    };
}
