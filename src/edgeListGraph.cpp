#include "edgeListGraph.hpp"

#include <algorithm>

using namespace Graph;

EdgeListGraph::EdgeListGraph(const std::string& filename)
{
    loadFromFile(filename);
}

bool EdgeListGraph::hasVertex(int id) const
{
    return std::any_of(Vertices.begin(), Vertices.end(), [id](const Vertex &v) { return v.Id == id; });
}

void EdgeListGraph::AddVertex(int id, const std::string &label, int weight)
{
    if (hasVertex(id))
        return;
    Vertices.push_back({id, label, weight});
}

void EdgeListGraph::RemoveVertex(int id)
{
    Vertices.erase(
        std::remove_if(Vertices.begin(), Vertices.end(), [id](const Vertex &v) { return v.Id == id; }),
        Vertices.end());
    Edges.erase(std::remove_if(Edges.begin(), Edges.end(),
                                [id](const Edge &e) { return e.From == id || e.To == id; }),
                 Edges.end());
}

void EdgeListGraph::AddEdge(int from, int to, const std::string &label, int weight)
{
    if (!hasVertex(from) || !hasVertex(to))
        return;
    Edges.push_back({from, to, label, weight});
}

void EdgeListGraph::RemoveEdge(int from, int to)
{
    Edges.erase(std::remove_if(Edges.begin(), Edges.end(),
                                [from, to](const Edge &e) { return e.From == from && e.To == to; }),
                 Edges.end());
}

void EdgeListGraph::SetEdgeActive(int from, int to, char active)
{
    for (auto &e : Edges)
        if (e.From == from && e.To == to)
            e.Active = active;
}

void EdgeListGraph::SetVertexActive(int id, char active)
{
    for (auto &v : Vertices)
        if (v.Id == id)
            v.Active = active;
}

void EdgeListGraph::SetVertexWeight(int id, int weight)
{
    for (auto &v : Vertices)
        if (v.Id == id)
            v.Weight = weight;
}

void EdgeListGraph::SetEdgeWeight(int from, int to, int weight)
{
    for (auto &e : Edges)
        if (e.From == from && e.To == to)
            e.Weight = weight;
}

std::vector<Vertex> EdgeListGraph::GetVertices() const
{
    return Vertices;
}

std::vector<Edge> EdgeListGraph::GetEdges() const
{
    return Edges;
}
