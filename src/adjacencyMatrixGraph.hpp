#pragma once

#include "baseGraph.hpp"

#include <optional>
#include <vector>

namespace Graph
{
    class AdjacencyMatrixGraph : public BaseGraph
    {
        public:
            struct Cell
            {
                std::string Label;
                int Weight;
                char Active = 0;
            };

            AdjacencyMatrixGraph() = default;
            explicit AdjacencyMatrixGraph(const std::string& filename);

            void AddVertex(int id, const std::string& label, int weight = -1) override;
            void RemoveVertex(int id) override;
            void AddEdge(int from, int to, const std::string& label, int weight = 0) override;
            void RemoveEdge(int from, int to) override;
            void SetEdgeActive(int from, int to, char active) override;
            void SetVertexActive(int id, char active) override;
            void SetVertexWeight(int id, int weight) override;
            void SetEdgeWeight(int from, int to, int weight) override;

            std::vector<Vertex> GetVertices() const override;
            std::vector<Edge> GetEdges() const override;

            std::vector<Vertex> Vertices;
            std::vector<std::vector<std::optional<Cell>>> Matrix;

        private:
            int indexOf(int id) const;
    };
}
