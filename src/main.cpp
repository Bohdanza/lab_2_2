#include "adjacencyListGraph.hpp"
#include "adjacencyMatrixGraph.hpp"
#include "edgeListGraph.hpp"
#include "baseGraph.hpp"
#include "visualizer.hpp"

#include <string>

namespace
{
    void populateSample(graph::BaseGraph& g)
    {
        g.addVertex(1, "A");
        g.addVertex(2, "B");
        g.addVertex(3, "C");
        g.addVertex(4, "D");
        g.addVertex(5, "E");

        g.addEdge(1, 2, "A-B");
        g.addEdge(1, 3, "A-C");
        g.addEdge(2, 4, "B-D");
        g.addEdge(3, 4, "C-D");
        g.addEdge(4, 5, "D-E");
        g.addEdge(2, 5, "B-E");
    }
}

int main()
{
    graph::AdjacencyListGraph listGraph;
    graph::AdjacencyMatrixGraph matrixGraph;
    graph::EdgeListGraph edgeListGraph;

    populateSample(listGraph);
    populateSample(matrixGraph);
    populateSample(edgeListGraph);

    graph::Visualizer visualizer;
    visualizer.AddGraph(listGraph.ToJson());
    visualizer.AddGraph(matrixGraph.ToJson());
    visualizer.AddGraph(edgeListGraph.ToJson());
    visualizer.Visualize("graphs.html");

    return 0;
}
