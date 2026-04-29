#include "adjacencyMatrixGraph.hpp"

using namespace Graph;

AdjacencyMatrixGraph::AdjacencyMatrixGraph(const std::string& filename)
{
    loadFromFile(filename);
}

int AdjacencyMatrixGraph::indexOf(int id) const
{
    for (size_t i = 0; i < Vertices.size(); ++i)
    {
        if (Vertices[i].Id == id) return static_cast<int>(i);
    }
    return -1;
}

void AdjacencyMatrixGraph::AddVertex(int id, const std::string& label, int weight)
{
    if (indexOf(id) != -1) return;
    Vertices.push_back({id, label, weight});
    for (auto& row : Matrix)
        row.emplace_back(std::nullopt);
    Matrix.emplace_back(Vertices.size(), std::nullopt);
}

void AdjacencyMatrixGraph::RemoveVertex(int id)
{
    const int idx = indexOf(id);
    if (idx == -1) return;
    Vertices.erase(Vertices.begin() + idx);
    Matrix.erase(Matrix.begin() + idx);
    for (auto& row : Matrix)
        row.erase(row.begin() + idx);
}

void AdjacencyMatrixGraph::AddEdge(int from, int to, const std::string& label, int weight)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    Matrix[fi][ti] = Cell{label, weight, false};
}

void AdjacencyMatrixGraph::RemoveEdge(int from, int to)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    Matrix[fi][ti].reset();
}

void AdjacencyMatrixGraph::SetEdgeActive(int from, int to, bool active)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    if (Matrix[fi][ti].has_value())
        Matrix[fi][ti]->Active = active;
}

void AdjacencyMatrixGraph::SetVertexActive(int id, bool active)
{
    const int idx = indexOf(id);
    if (idx == -1) return;
    Vertices[idx].Active = active;
}

void AdjacencyMatrixGraph::SetVertexWeight(int id, int weight)
{
    const int idx = indexOf(id);
    if (idx == -1) return;
    Vertices[idx].Weight = weight;
}

void AdjacencyMatrixGraph::SetEdgeWeight(int from, int to, int weight)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    if (Matrix[fi][ti].has_value())
        Matrix[fi][ti]->Weight = weight;
}

std::vector<Vertex> AdjacencyMatrixGraph::GetVertices() const { return Vertices; }

std::vector<Edge> AdjacencyMatrixGraph::GetEdges() const
{
    std::vector<Edge> edges;
    for (size_t i = 0; i < Vertices.size(); ++i)
        for (size_t j = 0; j < Vertices.size(); ++j)
            if (Matrix[i][j].has_value())
                edges.push_back({Vertices[i].Id, Vertices[j].Id, Matrix[i][j]->Label, Matrix[i][j]->Weight, Matrix[i][j]->Active});

    return edges;
}
