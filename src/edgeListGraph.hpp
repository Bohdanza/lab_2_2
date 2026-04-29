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
            void SetVertexActive(int id, bool active) override;
            void SetVertexWeight(int id, int weight) override;
            void SetEdgeWeight(int from, int to, int weight) override;

            std::vector<Vertex> GetVertices() const override;
            std::vector<Edge> GetEdges() const override;

            std::vector<Vertex> Vertices;
            std::vector<Edge> Edges;

        private:
            bool hasVertex(int id) const;
    };
}
