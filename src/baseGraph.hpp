#pragma once

#include <iosfwd>
#include <string>
#include <vector>

namespace graph
{

    struct Vertex
    {
        int id;
        std::string label;
        int weight = -1;
    };

    struct Edge
    {
        int from;
        int to;
        std::string label;
        int weight = 0;
    };

    class BaseGraph
    {
        public:
            virtual ~BaseGraph() = default;

            virtual void addVertex(int id, const std::string& label, int weight = -1) = 0;
            virtual void removeVertex(int id) = 0;
            virtual void addEdge(int from, int to, const std::string& label, int weight = 0) = 0;
            virtual void removeEdge(int from, int to) = 0;

            virtual std::vector<Vertex> getVertices() const = 0;
            virtual std::vector<Edge> getEdges() const = 0;

            std::string NodesToJson() const;
            std::string EdgesToJson() const;
            std::string ToJson() const;

        protected:
            void LoadFromStream(std::istream& in);
            void LoadFromFile(const std::string& filename);
    };

}
