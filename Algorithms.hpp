
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <sstream>
#include <vector>
#include <set>
namespace ariel {
class Algorithms {
public:
    static int isConnected(ariel::Graph&);
    static std::vector<int> shortestPath(const ariel::Graph&, size_t, size_t);
    static std::string shortestPathToString(const std::vector<int>&);
    static std::vector<int> isContainsCycle(const ariel::Graph&);
    static bool unDirectedCycleDFS(const std::vector<std::vector<int>>&, size_t, size_t, std::vector<bool>&, std::vector<int>&);
    static std::string cycleToString(const std::vector<int>&);
    static bool isSymmetric(const std::vector<std::vector<int>>&);
    static bool directedCycleDFS(const std::vector<std::vector<int>>&, size_t, std::vector<bool>&, std::vector<bool>&, std::vector<int>&);
    static std::vector<std::set<int>> isBipartite(const Graph&);
    static std::string bipartiteGraphToString(const std::vector<std::set<int>>&);
    static void negativeCycle(const ariel::Graph&);
    static void printMatrix(const std::vector<std::vector<int>>&);

};
};

#endif
