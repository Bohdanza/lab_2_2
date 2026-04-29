#include "baseGraph.hpp"

#include <fstream>
#include <istream>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace graph
{

    std::string BaseGraph::NodesToJson() const
    {
        const auto nodes = getVertices();
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            const auto& n = nodes[i];
            const std::string label = n.weight == -1
                ? n.label
                : n.label + " (" + std::to_string(n.weight) + ")";
            oss << "{\"id\":" << n.id
                << ",\"label\":\"" << label << "\""
                << ",\"weight\":" << n.weight << "}";
            if (i + 1 < nodes.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    std::string BaseGraph::EdgesToJson() const
    {
        const auto edges = getEdges();
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < edges.size(); ++i)
        {
            const auto& e = edges[i];
            const std::string label = e.label.empty()
                ? std::to_string(e.weight)
                : e.label + " (" + std::to_string(e.weight) + ")";
            oss << "{\"from\":" << e.from << ",\"to\":" << e.to
                << ",\"label\":\"" << label << "\""
                << ",\"weight\":" << e.weight << "}";
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

    void BaseGraph::LoadFromStream(std::istream& in)
    {
        int vertexCount = 0;
        if (!(in >> vertexCount) || vertexCount < 0)
            throw std::runtime_error("LoadFromStream: failed to read vertex count");
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 1; i <= vertexCount; ++i)
        {
            std::string line;
            if (!std::getline(in, line))
                throw std::runtime_error("LoadFromStream: failed to read vertex line");
            std::istringstream iss(line);
            std::string label;
            int weight = -1;
            if (!(iss >> label))
                throw std::runtime_error("LoadFromStream: failed to read vertex label");
            iss >> weight;
            addVertex(i, label, weight);
        }

        int edgeCount = 0;
        if (!(in >> edgeCount) || edgeCount < 0)
            throw std::runtime_error("LoadFromStream: failed to read edge count");

        for (int i = 0; i < edgeCount; ++i)
        {
            int from = 0;
            int to = 0;
            int weight = 0;
            if (!(in >> from >> to >> weight))
                throw std::runtime_error("LoadFromStream: failed to read edge");
            addEdge(from, to, "", weight);
        }
    }

    void BaseGraph::LoadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file)
            throw std::runtime_error("LoadFromFile: cannot open file: " + filename);
        LoadFromStream(file);
    }
}
