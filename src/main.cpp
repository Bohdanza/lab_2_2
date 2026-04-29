#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Node
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

static std::string nodes_to_json(const std::vector<Node> &nodes)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        oss << "{id:" << nodes[i].id << ",label:\"" << nodes[i].label << "\"}";
        if (i + 1 < nodes.size())
            oss << ",";
    }
    oss << "]";
    return oss.str();
}

static std::string edges_to_json(const std::vector<Edge> &edges)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < edges.size(); ++i)
    {
        oss << "{from:" << edges[i].from << ",to:" << edges[i].to << ",label:\"" << edges[i].label << "\"}";
        if (i + 1 < edges.size())
            oss << ",";
    }
    oss << "]";
    return oss.str();
}

static void write_html(const std::string &path, const std::vector<Node> &nodes, const std::vector<Edge> &edges)
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
        << nodes_to_json(nodes) << R"();
    const edges = new vis.DataSet()"
        << edges_to_json(edges) << R"();
    const options = {
      nodes: { shape: "dot", size: 18, font: { size: 16 } },
      edges: { arrows: { to: { enabled: false }, from: { enabled: false } }, font: { align: "middle" } },
      physics: { stabilization: true }
    };
    new vis.Network(document.getElementById("graph"), { nodes, edges }, options);
  </script>
</body>
</html>)";
}

static void open_in_browser(const std::string &path)
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

int main()
{
    std::vector<Node> nodes = {
        {1, "A"}, {2, "B"}, {3, "C"}, {4, "D"}, {5, "E"},
    };
    std::vector<Edge> edges = {
        {1, 2, "1"}, {1, 3, "2"}, {2, 4, "3"}, {3, 4, "1"}, {4, 5, "5"}, {2, 5, "4"},
    };

    const std::string path = "graph.html";
    write_html(path, nodes, edges);
    std::cout << "Wrote " << path << "\n";
    open_in_browser(path);
    return 0;
}
