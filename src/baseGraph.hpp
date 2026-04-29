#pragma once

#include <iosfwd>
#include <string>
#include <vector>

namespace Graph
{

    struct Vertex
    {
        int Id;
        std::string Label;
        int Weight = -1;
        bool Active = false;
    };

    struct Edge
    {
        int From;
        int To;
        std::string Label;
        int Weight = 0;
        bool Active = false;
    };

    class BaseGraph
    {
        public:
            virtual ~BaseGraph() = default;

            virtual void AddVertex(int id, const std::string& label, int weight = -1) = 0;
            virtual void RemoveVertex(int id) = 0;
            virtual void AddEdge(int from, int to, const std::string& label, int weight = 0) = 0;
            virtual void RemoveEdge(int from, int to) = 0;
            virtual void SetEdgeActive(int from, int to, bool active) = 0;
            virtual void SetVertexActive(int id, bool active) = 0;
            virtual void SetVertexWeight(int id, int weight) = 0;
            virtual void SetEdgeWeight(int from, int to, int weight) = 0;

            virtual std::vector<Vertex> GetVertices() const = 0;
            virtual std::vector<Edge> GetEdges() const = 0;

            std::string NodesToJson() const;
            std::string EdgesToJson() const;
            std::string ToJson() const;

        protected:
            void loadFromStream(std::istream& in);
            void loadFromFile(const std::string& filename);
    };

}
