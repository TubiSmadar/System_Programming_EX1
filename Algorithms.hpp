
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <sstream>
#include <vector>
#include <set>
namespace ariel {
class Algorithms {
public:
    static int isConnected(ariel::Graph& g);
    static std::vector<int>* shortestPath(const ariel::Graph& g, size_t start, size_t end);
    static std::string shortestPathToString(const std::vector<int>* shortestPath);
    static std::vector<int> isContainsCycle(const ariel::Graph& g);
    static bool unDirectedCycleDFS(const std::vector<std::vector<int>>& adjMatrix, size_t node, size_t parent, std::vector<bool>& visited, std::vector<int>& cycleNodes);
    static std::string cycleToString(const std::vector<int>&);
    static bool isSymmetric(const std::vector<std::vector<int>>& adjMatrix);
    static bool directedCycleDFS(const std::vector<std::vector<int>>& adjMatrix, size_t node, std::vector<bool>& visited, std::vector<bool>& onStack, std::vector<int>& cycleNodes);

    static std::vector<std::set<int>> isBipartite(const Graph&);
    static std::string bipartiteGraphToString(const std::vector<std::set<int>>&);
    static void negativeCycle(const ariel::Graph& g);
    static void printMatrix(const std::vector<std::vector<int>>& );

};
};

#endif
