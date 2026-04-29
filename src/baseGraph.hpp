#pragma once

#include <string>
#include <vector>

namespace graph
{

    struct Vertex
    {
        int id;
        std::string label;
    };

    struct Edge
    {
        int from;
        int to;
        std::string label;
    };

    class BaseGraph
    {
        public:
            virtual ~BaseGraph() = default;

            virtual void addVertex(int id, const std::string& label) = 0;
            virtual void removeVertex(int id) = 0;
            virtual void addEdge(int from, int to, const std::string& label) = 0;
            virtual void removeEdge(int from, int to) = 0;

            virtual std::vector<Vertex> getVertices() const = 0;
            virtual std::vector<Edge> getEdges() const = 0;

            std::string NodesToJson() const;
            std::string EdgesToJson() const;

            virtual void visualize(const std::string& path) const;
    };

}
