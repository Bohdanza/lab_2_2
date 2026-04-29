#include "edgeListGraph.hpp"

#include <algorithm>

using namespace graph;

EdgeListGraph::EdgeListGraph(const std::string& filename)
{
    LoadFromFile(filename);
}

bool EdgeListGraph::hasVertex(int id) const
{
    return std::any_of(vertices_.begin(), vertices_.end(), [id](const Vertex &v) { return v.id == id; });
}

void EdgeListGraph::addVertex(int id, const std::string &label, int weight)
{
    if (hasVertex(id))
        return;
    vertices_.push_back({id, label, weight});
}

void EdgeListGraph::removeVertex(int id)
{
    vertices_.erase(
        std::remove_if(vertices_.begin(), vertices_.end(), [id](const Vertex &v) { return v.id == id; }),
        vertices_.end());
    edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                                [id](const Edge &e) { return e.from == id || e.to == id; }),
                 edges_.end());
}

void EdgeListGraph::addEdge(int from, int to, const std::string &label, int weight)
{
    if (!hasVertex(from) || !hasVertex(to))
        return;
    edges_.push_back({from, to, label, weight});
}

void EdgeListGraph::removeEdge(int from, int to)
{
    edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                                [from, to](const Edge &e) { return e.from == from && e.to == to; }),
                 edges_.end());
}

std::vector<Vertex> EdgeListGraph::getVertices() const
{
    return vertices_;
}

std::vector<Edge> EdgeListGraph::getEdges() const
{
    return edges_;
}
