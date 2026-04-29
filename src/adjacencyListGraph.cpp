#include "adjacencyListGraph.hpp"

#include <algorithm>

using namespace Graph;

AdjacencyListGraph::AdjacencyListGraph(const std::string& filename)
{
    loadFromFile(filename);
}

int AdjacencyListGraph::indexOf(int id) const
{
    for (size_t i = 0; i < Vertices.size(); ++i)
        if (Vertices[i].Id == id)
            return static_cast<int>(i);

    return -1;
}

void AdjacencyListGraph::AddVertex(int id, const std::string &label, int weight)
{
    if (indexOf(id) != -1)
        return;
    Vertices.push_back({id, label, weight});
    Adjacency.emplace_back();
}

void AdjacencyListGraph::RemoveVertex(int id)
{
    const int idx = indexOf(id);
    if (idx == -1)
        return;
    Vertices.erase(Vertices.begin() + idx);
    Adjacency.erase(Adjacency.begin() + idx);
    for (auto &neighbors : Adjacency)
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(), [id](const Neighbor &n) { return n.ToId == id; }),
            neighbors.end());
}

void AdjacencyListGraph::AddEdge(int from, int to, const std::string &label, int weight)
{
    const int fi = indexOf(from);
    if (fi == -1 || indexOf(to) == -1)
        return;
    Adjacency[fi].push_back({to, label, weight, false});
}

void AdjacencyListGraph::RemoveEdge(int from, int to)
{
    const int fi = indexOf(from);
    if (fi == -1)
        return;
    auto &neighbors = Adjacency[fi];
    neighbors.erase(
        std::remove_if(neighbors.begin(), neighbors.end(), [to](const Neighbor &n) { return n.ToId == to; }),
        neighbors.end());
}

void AdjacencyListGraph::SetEdgeActive(int from, int to, bool active)
{
    const int fi = indexOf(from);
    if (fi == -1)
        return;
    for (auto &n : Adjacency[fi])
        if (n.ToId == to)
            n.Active = active;
}

void AdjacencyListGraph::SetVertexActive(int id, bool active)
{
    const int idx = indexOf(id);
    if (idx == -1)
        return;
    Vertices[idx].Active = active;
}

void AdjacencyListGraph::SetVertexWeight(int id, int weight)
{
    const int idx = indexOf(id);
    if (idx == -1)
        return;
    Vertices[idx].Weight = weight;
}

void AdjacencyListGraph::SetEdgeWeight(int from, int to, int weight)
{
    const int fi = indexOf(from);
    if (fi == -1)
        return;
    for (auto &n : Adjacency[fi])
        if (n.ToId == to)
            n.Weight = weight;
}

std::vector<Vertex> AdjacencyListGraph::GetVertices() const
{
    return Vertices;
}

std::vector<Edge> AdjacencyListGraph::GetEdges() const
{
    std::vector<Edge> edges;
    for (size_t i = 0; i < Vertices.size(); ++i)
        for (const auto &n : Adjacency[i])
            edges.push_back({Vertices[i].Id, n.ToId, n.Label, n.Weight, n.Active});

    return edges;
}
