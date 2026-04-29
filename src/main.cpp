#include "adjacencyListGraph.hpp"
#include "adjacencyMatrixGraph.hpp"
#include "edgeListGraph.hpp"
#include "visualizer.hpp"

#include <string>

int main()
{
    const std::string inputPath = "testGraph.txt";

    graph::AdjacencyListGraph listGraph(inputPath);
    graph::AdjacencyMatrixGraph matrixGraph(inputPath);
    graph::EdgeListGraph edgeListGraph(inputPath);

    graph::Visualizer visualizer;
    visualizer.AddGraph(listGraph.ToJson());
    visualizer.AddGraph(matrixGraph.ToJson());
    visualizer.AddGraph(edgeListGraph.ToJson());
    visualizer.Visualize("graphs.html");

    return 0;
}
