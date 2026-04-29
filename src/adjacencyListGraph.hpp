#pragma once

#include "baseGraph.hpp"

#include <vector>

namespace Graph
{
    class AdjacencyListGraph : public BaseGraph
    {
        public:
            AdjacencyListGraph() = default;
            explicit AdjacencyListGraph(const std::string& filename);

            void AddVertex(int id, const std::string& label, int weight = -1) override;
            void RemoveVertex(int id) override;
            void AddEdge(int from, int to, const std::string& label, int weight = 0) override;
            void RemoveEdge(int from, int to) override;
            void SetEdgeActive(int from, int to, bool active) override;

            std::vector<Vertex> GetVertices() const override;
            std::vector<Edge> GetEdges() const override;

        private:
            struct Neighbor
            {
                    int ToId;
                    std::string Label;
                    int Weight;
                    bool Active = false;
            };

            std::vector<Vertex> v_vertices;
            std::vector<std::vector<Neighbor>> v_adj;

            int indexOf(int id) const;
    };
}
