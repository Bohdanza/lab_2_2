#include "adjacencyListGraph.hpp"
#include "adjacencyMatrixGraph.hpp"
#include "edgeListGraph.hpp"
#include "visualizer.hpp"

#include <string>

int main()
{
    const std::string inputPath = "testGraph.txt";

    Graph::AdjacencyListGraph listGraph(inputPath);
    Graph::AdjacencyMatrixGraph matrixGraph(inputPath);
    Graph::EdgeListGraph edgeListGraph(inputPath);

    Graph::Visualizer visualizer;
    visualizer.AddGraph(listGraph.ToJson());
    visualizer.AddGraph(matrixGraph.ToJson());
    visualizer.AddGraph(edgeListGraph.ToJson());
    visualizer.Visualize("graphs.html");

    return 0;
}
