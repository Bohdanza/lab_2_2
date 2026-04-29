#include "adjacencyListGraph.hpp"

#include <algorithm>

using namespace graph;

AdjacencyListGraph::AdjacencyListGraph(const std::string& filename)
{
    LoadFromFile(filename);
}

int AdjacencyListGraph::indexOf(int id) const
{
    for (size_t i = 0; i < vertices_.size(); ++i)
        if (vertices_[i].id == id)
            return static_cast<int>(i);

    return -1;
}

void AdjacencyListGraph::addVertex(int id, const std::string &label, int weight)
{
    if (indexOf(id) != -1)
        return;
    vertices_.push_back({id, label, weight});
    adj_.emplace_back();
}

void AdjacencyListGraph::removeVertex(int id)
{
    const int idx = indexOf(id);
    if (idx == -1)
        return;
    vertices_.erase(vertices_.begin() + idx);
    adj_.erase(adj_.begin() + idx);
    for (auto &neighbors : adj_)
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(), [id](const Neighbor &n) { return n.toId == id; }),
            neighbors.end());
}

void AdjacencyListGraph::addEdge(int from, int to, const std::string &label, int weight)
{
    const int fi = indexOf(from);
    if (fi == -1 || indexOf(to) == -1)
        return;
    adj_[fi].push_back({to, label, weight});
}

void AdjacencyListGraph::removeEdge(int from, int to)
{
    const int fi = indexOf(from);
    if (fi == -1)
        return;
    auto &neighbors = adj_[fi];
    neighbors.erase(
        std::remove_if(neighbors.begin(), neighbors.end(), [to](const Neighbor &n) { return n.toId == to; }),
        neighbors.end());
}

std::vector<Vertex> AdjacencyListGraph::getVertices() const
{
    return vertices_;
}

std::vector<Edge> AdjacencyListGraph::getEdges() const
{
    std::vector<Edge> edges;
    for (size_t i = 0; i < vertices_.size(); ++i)
        for (const auto &n : adj_[i])
            edges.push_back({vertices_[i].id, n.toId, n.label, n.weight});

    return edges;
}
