#include "baseGraph.hpp"

#include <fstream>
#include <istream>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace Graph
{

    std::string BaseGraph::NodesToJson() const
    {
        const auto nodes = GetVertices();
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            const auto& n = nodes[i];
            const std::string label = n.Weight == -1
                ? n.Label
                : n.Label + " (" + std::to_string(n.Weight) + ")";
            oss << "{\"id\":" << n.Id
                << ",\"label\":\"" << label << "\""
                << ",\"weight\":" << n.Weight << "}";
            if (i + 1 < nodes.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    std::string BaseGraph::EdgesToJson() const
    {
        const auto edges = GetEdges();
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < edges.size(); ++i)
        {
            const auto& e = edges[i];
            const std::string label = e.Label.empty()
                ? std::to_string(e.Weight)
                : e.Label + " (" + std::to_string(e.Weight) + ")";
            oss << "{\"from\":" << e.From << ",\"to\":" << e.To
                << ",\"label\":\"" << label << "\""
                << ",\"weight\":" << e.Weight;
            if (e.Active)
                oss << ",\"color\":\"green\",\"width\":4";
            oss << "}";
            if (i + 1 < edges.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    std::string BaseGraph::ToJson() const
    {
        std::ostringstream oss;
        oss << "{\"nodes\":" << NodesToJson() << ",\"edges\":" << EdgesToJson() << "}";
        return oss.str();
    }

    void BaseGraph::loadFromStream(std::istream& in)
    {
        int vertexCount = 0;
        if (!(in >> vertexCount) || vertexCount < 0)
            throw std::runtime_error("loadFromStream: failed to read vertex count");
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 1; i <= vertexCount; ++i)
        {
            std::string line;
            if (!std::getline(in, line))
                throw std::runtime_error("loadFromStream: failed to read vertex line");
            std::istringstream iss(line);
            std::string label;
            int weight = -1;
            if (!(iss >> label))
                throw std::runtime_error("loadFromStream: failed to read vertex label");
            iss >> weight;
            AddVertex(i, label, weight);
        }

        int edgeCount = 0;
        if (!(in >> edgeCount) || edgeCount < 0)
            throw std::runtime_error("loadFromStream: failed to read edge count");

        for (int i = 0; i < edgeCount; ++i)
        {
            int from = 0;
            int to = 0;
            int weight = 0;
            if (!(in >> from >> to >> weight))
                throw std::runtime_error("loadFromStream: failed to read edge");
            AddEdge(from, to, "", weight);
        }
    }

    void BaseGraph::loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file)
            throw std::runtime_error("loadFromFile: cannot open file: " + filename);
        loadFromStream(file);
    }
}
