/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    ariel::Graph g;

    // Graph 1: 3x3 matrix representing a connected graph.
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g.loadGraph(graph1);
    cout << "Graph 1:" << endl;
    g.printGraph();
    cout << Algorithms::cycleToString(Algorithms::isContainsCycle(g)) << endl;
    cout << Algorithms::bipartiteGraphToString(Algorithms::isBipartite(g)) << endl; //Should print "Group 1: 0 2 Group 2: 1 "

    // Graph 2: 5x5 matrix representing a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph2);
    cout << "Graph 2:" << endl;
    g.printGraph();
    cout << Algorithms::bipartiteGraphToString(Algorithms::isBipartite(g)) << endl; //Should print "Graph is not bipartite!"

    // Graph 3: 5x5 matrix representing a connected weighted graph.
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}
    };
    g.loadGraph(graph3);
    cout << "Graph 3:" << endl;
    g.printGraph();
    cout << Algorithms::bipartiteGraphToString(Algorithms::isBipartite(g)) << endl; //Should print "Graph is not bipartite!"

    // Graph 4: Invalid graph - 5x4 matrix.
    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}
    };
    try {
        g.loadGraph(graph4);
    } catch (const std::invalid_argument &e) {
        cout << e.what() << endl; 
    }

    // Graph 5: A graph with a negative cycle.
    vector<vector<int>> graph5 = {
        {0, 1, 0, 0, 0},
        {-1, 0, -2, 0, 0},
        {0, -1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph5);
    cout << "Graph 5:" << endl;
    g.printGraph();
    cout << Algorithms::cycleToString(Algorithms::isContainsCycle(g)) << endl;
    Algorithms::negativeCycle(g);

    // Graph 6: A connected graph with a negative cycle.
    vector<vector<int>> graph6 = {
        {0, -3, 1},
        {-3, 0, 1},
        {1, 1, 0}
    };
    g.loadGraph(graph6);
    cout << "Graph 6:" << endl;
    g.printGraph();
    Algorithms::negativeCycle(g);

    // Graph 7: 4x4 matrix representing a bipartite graph.
    vector<vector<int>> graph7 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    g.loadGraph(graph7);
    cout << "Graph 7:" << endl;
    g.printGraph();
    cout << Algorithms::bipartiteGraphToString(Algorithms::isBipartite(g)) << endl;

    // Graph 8: 5x5 matrix representing a disconnected graph.
    vector<vector<int>> graph8 = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph8);
    cout << "Graph 8:" << endl;
    g.printGraph();
    cout << Algorithms::bipartiteGraphToString(Algorithms::isBipartite(g)) << endl;

    return 0;
}
