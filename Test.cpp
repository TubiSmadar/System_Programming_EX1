#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    // Connected graph
    CHECK(ariel::Algorithms::isConnected(g) == 1);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    // Disconnected graph
    CHECK(ariel::Algorithms::isConnected(g) == 0);

    vector<vector<int>> graph3 = {
        {0}};
    g.loadGraph(graph3);
    // Graph with only 1 vertex
    CHECK(ariel::Algorithms::isConnected(g) == 1);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    // Base case
    CHECK(ariel::Algorithms::shortestPathToString(ariel::Algorithms::shortestPath(g, 0, 2)) == "0 -> 1 -> 2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    // No path test
    CHECK(ariel::Algorithms::shortestPathToString(ariel::Algorithms::shortestPath(g, 0, 4)) == "No path found");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    // Directed graph without cycles.
    CHECK(ariel::Algorithms::cycleToString(ariel::Algorithms::isContainsCycle(g)) == "No cycle found");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    // Directed graph with cycles.
    CHECK(ariel::Algorithms::cycleToString(ariel::Algorithms::isContainsCycle(g)) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph3 = {{0, 1, 0, 1, 1}, 
                                  {1, 0, 1, 0, 0}, 
                                  {0, 1, 0, 1, 0}, 
                                  {1, 0, 1, 0, 0}, 
                                  {1, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::cycleToString(ariel::Algorithms::isContainsCycle(g)) == "The cycle is: 0->1->2->3->0");
    
    vector<vector<int>> graph4 = {{0, 1, 0, 0, 0},
                                  {0, 0, 0, 1, 1}, 
                                  {0, 1, 0, 0, 0}, 
                                  {0, 0, 1, 0, 0}, 
                                  {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    // Undirected graph with cycle
    CHECK(ariel::Algorithms::cycleToString(ariel::Algorithms::isContainsCycle(g)) == "The cycle is: 1->3->2->1");
    
    vector<vector<int>> graph5 = {{0, 1}, 
                                  {3, 0}};
    g.loadGraph(graph5);
    // Undirected graph with cycle of 2 nodes.
    CHECK(ariel::Algorithms::cycleToString(ariel::Algorithms::isContainsCycle(g)) == "The cycle is: 0->1->0");

    vector<vector<int>> graph6 = {{0}};
    g.loadGraph(graph6);
    // Graph with one vertex no edges.
    CHECK(ariel::Algorithms::cycleToString(ariel::Algorithms::isContainsCycle(g)) == "No cycle found");
  
    vector<vector<int>> graph7 = {{1}};
    g.loadGraph(graph7);
    // Graph with one vertex cyclic edge.
    CHECK(ariel::Algorithms::cycleToString(ariel::Algorithms::isContainsCycle(g)) == "The cycle is: 0->0");


}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    // Base case of bipartite graph.
    CHECK(ariel::Algorithms::bipartiteGraphToString(ariel::Algorithms::isBipartite(g)) == "Group 1: 0 2 \nGroup 2: 1 \n");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    // Disonnected graph not bipartite.
    CHECK(ariel::Algorithms::bipartiteGraphToString(ariel::Algorithms::isBipartite(g)) == "Graph is not bipartite!\n");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    // Connected graph not bipartite.
    CHECK(ariel::Algorithms::bipartiteGraphToString(ariel::Algorithms::isBipartite(g)) == "Graph is not bipartite!\n");
     
    vector<vector<int>> graph6 = {{0}};
    g.loadGraph(graph6);
    // Graph with one vertex no edges.
    CHECK(ariel::Algorithms::bipartiteGraphToString(ariel::Algorithms::isBipartite(g)) == "Group 1: 0 \nGroup 2: \n");

    vector<vector<int>> graph7 = {{1}};
    g.loadGraph(graph7);
    // Graph with one vertex cyclic edge.
    CHECK(ariel::Algorithms::bipartiteGraphToString(ariel::Algorithms::isBipartite(g)) == "Graph is not bipartite!\n");

}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {{1}};
    g.loadGraph(graph);
    // Graph with one vertex cyclic edge.
    
    // Redirect stdout to a stringstream
    std::ostringstream redirectedOutput;
    std::streambuf* oldStdout = std::cout.rdbuf(redirectedOutput.rdbuf());
    ariel::Algorithms::negativeCycle(g);

    // Restore stdout
    std::cout.rdbuf(oldStdout);

    // Check the content of the stringstream
    CHECK(redirectedOutput.str() == "No negative cycle found!\n");

    vector<vector<int>> graph1 = {{-1}};
    g.loadGraph(graph1);
    // Graph with one vertex negative cyclic edge.
    std::ostringstream redirectedOutput1;
    std::streambuf* oldStdout1 = std::cout.rdbuf(redirectedOutput1.rdbuf());
    ariel::Algorithms::negativeCycle(g);

    // Restore stdout
    std::cout.rdbuf(oldStdout1);

    // Check the content of the stringstream
    CHECK(redirectedOutput1.str() == "Negative cycle found!\n");

    // Graph with both negative and positive cycles.
    vector<vector<int>> graph2 =  {{0, 1, -1, -1},
                                   {1, 0, 0, 2}, 
                                   {-1, 0, 0, -4}, 
                                   {-1, 2, -4, 0}};
    g.loadGraph(graph2);
    // Graph with one vertex cyclic edge.
    std::ostringstream redirectedOutput2;
    std::streambuf* oldStdout2 = std::cout.rdbuf(redirectedOutput2.rdbuf());
    ariel::Algorithms::negativeCycle(g);

    // Restore stdout
    std::cout.rdbuf(oldStdout2);

    // Check the content of the stringstream
    CHECK(redirectedOutput2.str() == "Negative cycle found!\n");

    // Undirected graph with 2 negtive edge
    vector<vector<int>> graph3 = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
        g.loadGraph(graph3);
    std::ostringstream redirectedOutput3;
    std::streambuf* oldStdout3 = std::cout.rdbuf(redirectedOutput3.rdbuf());
    ariel::Algorithms::negativeCycle(g);

    // Restore stdout
    std::cout.rdbuf(oldStdout3);

    // Check the content of the stringstream
    CHECK(redirectedOutput3.str() == "No negative cycle found!\n");

    
 

}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}
