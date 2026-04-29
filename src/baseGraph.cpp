#include "baseGraph.hpp"

#include <sstream>

namespace graph
{

    std::string BaseGraph::NodesToJson() const
    {
        const auto nodes = getVertices();
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            oss << "{\"id\":" << nodes[i].id << ",\"label\":\"" << nodes[i].label << "\"}";
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
            oss << "{\"from\":" << edges[i].from << ",\"to\":" << edges[i].to << ",\"label\":\"" << edges[i].label << "\"}";
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
}
