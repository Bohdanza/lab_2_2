#include "edgeListGraph.hpp"

#include <algorithm>

using namespace Graph;

EdgeListGraph::EdgeListGraph(const std::string& filename)
{
    loadFromFile(filename);
}

bool EdgeListGraph::hasVertex(int id) const
{
    return std::any_of(v_vertices.begin(), v_vertices.end(), [id](const Vertex &v) { return v.Id == id; });
}

void EdgeListGraph::AddVertex(int id, const std::string &label, int weight)
{
    if (hasVertex(id))
        return;
    v_vertices.push_back({id, label, weight});
}

void EdgeListGraph::RemoveVertex(int id)
{
    v_vertices.erase(
        std::remove_if(v_vertices.begin(), v_vertices.end(), [id](const Vertex &v) { return v.Id == id; }),
        v_vertices.end());
    v_edges.erase(std::remove_if(v_edges.begin(), v_edges.end(),
                                [id](const Edge &e) { return e.From == id || e.To == id; }),
                 v_edges.end());
}

void EdgeListGraph::AddEdge(int from, int to, const std::string &label, int weight)
{
    if (!hasVertex(from) || !hasVertex(to))
        return;
    v_edges.push_back({from, to, label, weight});
}

void EdgeListGraph::RemoveEdge(int from, int to)
{
    v_edges.erase(std::remove_if(v_edges.begin(), v_edges.end(),
                                [from, to](const Edge &e) { return e.From == from && e.To == to; }),
                 v_edges.end());
}

void EdgeListGraph::SetEdgeActive(int from, int to, bool active)
{
    for (auto &e : v_edges)
        if (e.From == from && e.To == to)
            e.Active = active;
}

std::vector<Vertex> EdgeListGraph::GetVertices() const
{
    return v_vertices;
}

std::vector<Edge> EdgeListGraph::GetEdges() const
{
    return v_edges;
}
