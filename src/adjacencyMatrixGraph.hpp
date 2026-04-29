#pragma once

#include "baseGraph.hpp"

#include <optional>
#include <vector>

namespace Graph
{
    class AdjacencyMatrixGraph : public BaseGraph
    {
        public:
            AdjacencyMatrixGraph() = default;
            explicit AdjacencyMatrixGraph(const std::string& filename);

            void AddVertex(int id, const std::string& label, int weight = -1) override;
            void RemoveVertex(int id) override;
            void AddEdge(int from, int to, const std::string& label, int weight = 0) override;
            void RemoveEdge(int from, int to) override;
            void SetEdgeActive(int from, int to, bool active) override;

            std::vector<Vertex> GetVertices() const override;
            std::vector<Edge> GetEdges() const override;

        private:
            struct Cell
            {
                std::string Label;
                int Weight;
                bool Active = false;
            };

            std::vector<Vertex> v_vertices;
            std::vector<std::vector<std::optional<Cell>>> v_matrix;

            int indexOf(int id) const;
    };
}
