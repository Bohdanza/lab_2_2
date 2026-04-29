#include "visualizer.hpp"

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

    void Visualizer::AddGraph(const std::string& json)
    {
        graphs_.push_back(json);
    }

    void Visualizer::Visualize(const std::string& path) const
    {
        std::ostringstream tiles;
        for (size_t i = 0; i < graphs_.size(); ++i)
        {
            tiles << "    <div class=\"tile\"><div class=\"title\">Graph " << (i + 1)
                  << "</div><div id=\"graph" << i << "\" class=\"canvas\"></div></div>\n";
        }

        std::ostringstream payload;
        payload << "[";
        for (size_t i = 0; i < graphs_.size(); ++i)
        {
            payload << graphs_[i];
            if (i + 1 < graphs_.size()) payload << ",";
        }
        payload << "]";

        std::ofstream out(path);
        out << R"(<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Graphs</title>
  <script src="https://unpkg.com/vis-network/standalone/umd/vis-network.min.js"></script>
  <style>
    html, body { margin: 0; font-family: sans-serif; }
    .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(360px, 1fr)); gap: 8px; padding: 8px; box-sizing: border-box; }
    .tile { border: 1px solid #ddd; box-sizing: border-box; }
    .title { padding: 4px 8px; background: #f5f5f5; border-bottom: 1px solid #ddd; font-size: 14px; }
    .canvas { width: 100%; height: 480px; }
  </style>
</head>
<body>
  <div class="grid">
)" << tiles.str() << R"(  </div>
  <script>
    const graphs = )" << payload.str() << R"(;
    const options = {
      nodes: { shape: "dot", size: 18, font: { size: 16 } },
      edges: { arrows: { to: { enabled: false }, from: { enabled: false } }, font: { align: "middle" } },
      physics: { stabilization: true }
    };
    graphs.forEach((g, i) => {
      const nodes = new vis.DataSet(g.nodes);
      const edges = new vis.DataSet(g.edges);
      new vis.Network(document.getElementById("graph" + i), { nodes, edges }, options);
    });
  </script>
</body>
</html>)";
        out.close();

        openInBrowser(path);
    }
}
