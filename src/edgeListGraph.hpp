#pragma once

#include "baseGraph.hpp"

#include <vector>

namespace Graph
{
    class EdgeListGraph : public BaseGraph
    {
        public:
            EdgeListGraph() = default;
            explicit EdgeListGraph(const std::string& filename);

            void AddVertex(int id, const std::string& label, int weight = -1) override;
            void RemoveVertex(int id) override;
            void AddEdge(int from, int to, const std::string& label, int weight = 0) override;
            void RemoveEdge(int from, int to) override;
            void SetEdgeActive(int from, int to, bool active) override;

            std::vector<Vertex> GetVertices() const override;
            std::vector<Edge> GetEdges() const override;

        private:
            std::vector<Vertex> v_vertices;
            std::vector<Edge> v_edges;

            bool hasVertex(int id) const;
    };
}
