#include "baseGraph.hpp"

#include <cstdlib>
#include <fstream>
#include <sstream>

namespace graph
{

    namespace
    {

        void openInBrowser(const std::string& path)
        {
#if defined(_WIN32)
            std::string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
            std::string cmd = "open \"" + path + "\"";
#else
            std::string cmd = "xdg-open \"" + path + "\"";
#endif
            std::system(cmd.c_str());
        }

    }

    std::string BaseGraph::NodesToJson() const
    {
        const auto nodes = getVertices();
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            oss << "{id:" << nodes[i].id << ",label:\"" << nodes[i].label << "\"}";
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
            oss << "{from:" << edges[i].from << ",to:" << edges[i].to << ",label:\"" << edges[i].label << "\"}";
            if (i + 1 < edges.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    void BaseGraph::visualize(const std::string& path) const
    {
        std::ofstream out(path);
        out << R"(<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Graph</title>
  <script src="https://unpkg.com/vis-network/standalone/umd/vis-network.min.js"></script>
  <style>
    html, body { margin: 0; height: 100%; }
    #graph { width: 100vw; height: 100vh; border: 1px solid #ddd; }
  </style>
</head>
<body>
  <div id="graph"></div>
  <script>
    const nodes = new vis.DataSet()"
            << NodesToJson() << R"();
    const edges = new vis.DataSet()"
            << EdgesToJson() << R"();
    const options = {
      nodes: { shape: "dot", size: 18, font: { size: 16 } },
      edges: { arrows: { to: { enabled: false }, from: { enabled: false } }, font: { align: "middle" } },
      physics: { stabilization: true }
    };
    new vis.Network(document.getElementById("graph"), { nodes, edges }, options);
  </script>
</body>
</html>)";
        out.close();

        openInBrowser(path);
    }
}
