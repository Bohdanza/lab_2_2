#include "adjacencyMatrixGraph.hpp"

using namespace Graph;

AdjacencyMatrixGraph::AdjacencyMatrixGraph(const std::string& filename)
{
    loadFromFile(filename);
}

int AdjacencyMatrixGraph::indexOf(int id) const
{
    for (size_t i = 0; i < v_vertices.size(); ++i)
    {
        if (v_vertices[i].Id == id) return static_cast<int>(i);
    }
    return -1;
}

void AdjacencyMatrixGraph::AddVertex(int id, const std::string& label, int weight)
{
    if (indexOf(id) != -1) return;
    v_vertices.push_back({id, label, weight});
    for (auto& row : v_matrix)
        row.emplace_back(std::nullopt);
    v_matrix.emplace_back(v_vertices.size(), std::nullopt);
}

void AdjacencyMatrixGraph::RemoveVertex(int id)
{
    const int idx = indexOf(id);
    if (idx == -1) return;
    v_vertices.erase(v_vertices.begin() + idx);
    v_matrix.erase(v_matrix.begin() + idx);
    for (auto& row : v_matrix)
        row.erase(row.begin() + idx);
}

void AdjacencyMatrixGraph::AddEdge(int from, int to, const std::string& label, int weight)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    v_matrix[fi][ti] = Cell{label, weight, false};
}

void AdjacencyMatrixGraph::RemoveEdge(int from, int to)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    v_matrix[fi][ti].reset();
}

void AdjacencyMatrixGraph::SetEdgeActive(int from, int to, bool active)
{
    const int fi = indexOf(from);
    const int ti = indexOf(to);
    if (fi == -1 || ti == -1) return;
    if (v_matrix[fi][ti].has_value())
        v_matrix[fi][ti]->Active = active;
}

std::vector<Vertex> AdjacencyMatrixGraph::GetVertices() const { return v_vertices; }

std::vector<Edge> AdjacencyMatrixGraph::GetEdges() const
{
    std::vector<Edge> edges;
    for (size_t i = 0; i < v_vertices.size(); ++i)
        for (size_t j = 0; j < v_vertices.size(); ++j)
            if (v_matrix[i][j].has_value())
                edges.push_back({v_vertices[i].Id, v_vertices[j].Id, v_matrix[i][j]->Label, v_matrix[i][j]->Weight, v_matrix[i][j]->Active});

    return edges;
}
