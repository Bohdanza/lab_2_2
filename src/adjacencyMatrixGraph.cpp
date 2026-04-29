#include "adjacencyMatrixGraph.hpp"

using namespace graph;

AdjacencyMatrixGraph::AdjacencyMatrixGraph(const std::string& filename)
{
    LoadFromFile(filename);
}

int AdjacencyMatrixGraph::indexOf(int id) const
{
    for (size_t i = 0; i < vertices_.size(); ++i)
    {
        if (vertices_[i].id == id) return static_cast<int>(i);
    }
    return -1;
}

void AdjacencyMatrixGraph::addVertex(int id, const std::string& label, int weight)
{
    if (indexOf(id) != -1) return;
    vertices_.push_back({id, label, weight});
    for (auto& row : matrix_)
        row.emplace_back(std::nullopt);
    matrix_.emplace_back(vertices_.size(), std::nullopt);
}

void AdjacencyMatrixGraph::removeVertex(int id)
{
    const int idx = indexOf(id);
    if (idx == -1) return;
    vertices_.erase(vertices_.begin() + idx);
    matrix_.erase(matrix_.begin() + idx);
    for (auto& row : matrix_)
        row.erase(row.begin() + idx);
}

void AdjacencyMatrixGraph::addEdge(int from, int to, const std::string& label, int weight)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    matrix_[fi][ti] = Cell{label, weight};
}

void AdjacencyMatrixGraph::removeEdge(int from, int to)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    matrix_[fi][ti].reset();
}

std::vector<Vertex> AdjacencyMatrixGraph::getVertices() const { return vertices_; }

std::vector<Edge> AdjacencyMatrixGraph::getEdges() const
{
    std::vector<Edge> edges;
    for (size_t i = 0; i < vertices_.size(); ++i)
        for (size_t j = 0; j < vertices_.size(); ++j)
            if (matrix_[i][j].has_value())
                edges.push_back({vertices_[i].id, vertices_[j].id, matrix_[i][j]->label, matrix_[i][j]->weight});
    
    return edges;
}
