#include "adjacencyListGraph.hpp"

#include <algorithm>

using namespace Graph;

AdjacencyListGraph::AdjacencyListGraph(const std::string& filename)
{
    loadFromFile(filename);
}

int AdjacencyListGraph::indexOf(int id) const
{
    for (size_t i = 0; i < v_vertices.size(); ++i)
        if (v_vertices[i].Id == id)
            return static_cast<int>(i);

    return -1;
}

void AdjacencyListGraph::AddVertex(int id, const std::string &label, int weight)
{
    if (indexOf(id) != -1)
        return;
    v_vertices.push_back({id, label, weight});
    v_adj.emplace_back();
}

void AdjacencyListGraph::RemoveVertex(int id)
{
    const int idx = indexOf(id);
    if (idx == -1)
        return;
    v_vertices.erase(v_vertices.begin() + idx);
    v_adj.erase(v_adj.begin() + idx);
    for (auto &neighbors : v_adj)
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(), [id](const Neighbor &n) { return n.ToId == id; }),
            neighbors.end());
}

void AdjacencyListGraph::AddEdge(int from, int to, const std::string &label, int weight)
{
    const int fi = indexOf(from);
    if (fi == -1 || indexOf(to) == -1)
        return;
    v_adj[fi].push_back({to, label, weight, false});
}

void AdjacencyListGraph::RemoveEdge(int from, int to)
{
    const int fi = indexOf(from);
    if (fi == -1)
        return;
    auto &neighbors = v_adj[fi];
    neighbors.erase(
        std::remove_if(neighbors.begin(), neighbors.end(), [to](const Neighbor &n) { return n.ToId == to; }),
        neighbors.end());
}

void AdjacencyListGraph::SetEdgeActive(int from, int to, bool active)
{
    const int fi = indexOf(from);
    if (fi == -1)
        return;
    for (auto &n : v_adj[fi])
        if (n.ToId == to)
            n.Active = active;
}

std::vector<Vertex> AdjacencyListGraph::GetVertices() const
{
    return v_vertices;
}

std::vector<Edge> AdjacencyListGraph::GetEdges() const
{
    std::vector<Edge> edges;
    for (size_t i = 0; i < v_vertices.size(); ++i)
        for (const auto &n : v_adj[i])
            edges.push_back({v_vertices[i].Id, n.ToId, n.Label, n.Weight, n.Active});

    return edges;
}
