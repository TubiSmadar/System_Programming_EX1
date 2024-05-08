#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <stack>
#include <set>
namespace ariel {
    void pathDFS(Graph& g, size_t index, vector<bool>& visited) {
        visited[index] = true; // Mark the current vertex as visited
        // Traverse all adjacent vertices of index
        for (size_t i = 0; i < visited.size(); ++i) {
            if (g.getAdjMatrix()[index][i] != 0 && !visited[i]) {
                pathDFS(g, i, visited); // Recursive call to visit unvisited adjacent vertices
            }
        }
    }

    int Algorithms::isConnected(Graph& g) {
        std::vector<bool> visited(g.getNumVertices(), false);
        size_t startIndex = 0;
        pathDFS(g, startIndex, visited);
        for (bool v : visited) {
            if (!v) {
                return 0;
            }
        }

        return 1;
    }

    std::vector<int>* Algorithms::shortestPath(const ariel::Graph& g, size_t start, size_t end) {
        const size_t graphSize = g.getNumVertices();
        std::vector<int> dist(graphSize, std::numeric_limits<int>::max());
        std::vector<int> parent(graphSize, -1); // To store the parent vertices
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, std::greater<std::pair<int, size_t>>> pq;

        dist[start] = 0;
        pq.emplace(0, start);
        while (!pq.empty()) {
            size_t u = pq.top().second;
            int u_dist = pq.top().first;
            pq.pop();

            if (u == end) {
                break; // Stop the search when the destination vertex is reached
            }

            if (u_dist > dist[u]) {
                continue; // Skip if this vertex has been relaxed before
            }

            for (size_t v = 0; v < graphSize; ++v) {
                if (g.getAdjMatrix()[u][v] != 0) {
                    int weight = g.getAdjMatrix()[u][v];
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        parent[v] = static_cast<int>(u); // Update parent of v to u
                        pq.emplace(dist[v], v);
                    }
                }
            }
        }
        // If end vertex is not reachable from start vertex, return nullptr
        if (parent[end] == -1) {
            return nullptr;
        }

        // Reconstruct the shortest path from start to end
        std::vector<int>* shortestPath = new std::vector<int>();
        int current = static_cast<int>(end);
        while (current != -1 && static_cast<size_t>(current) != start) {
            shortestPath->push_back(current);
            current = parent[static_cast<size_t>(current)];
        }
        shortestPath->push_back(start);
        std::reverse(shortestPath->begin(), shortestPath->end()); // Reverse the vector to get the path from start to end

        return shortestPath;
    }

    std::string Algorithms::shortestPathToString(const std::vector<int>* shortestPath) {
        if (shortestPath == nullptr) {
            return "No path found"; // Handle the case where shortestPath is nullptr
        }

        std::ostringstream oss;
        for (size_t i = 0; i < shortestPath->size(); ++i) {
            oss << (*shortestPath)[i]; // Dereference the pointer to access elements
            if (i != shortestPath->size() - 1) {
                oss << " -> ";
            }
        }
        return oss.str();
    }

    std::vector<int> Algorithms::isContainsCycle(const Graph& g) {
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        size_t numVertices = g.getNumVertices();

        std::vector<bool> visited(numVertices, false);
        std::vector<bool> onStack(numVertices, false);
        size_t parent = SIZE_MAX;
        std::vector<int> cycleNodes;

        for (size_t i = 0; i < numVertices; ++i) {
            if (isSymmetric(g.getAdjMatrix())){
                if (!visited[i] && unDirectedCycleDFS(adjMatrix, i, parent, visited, cycleNodes)) {
                    // Cycle found, return the nodes forming the cycle
                    return cycleNodes;
                }
            }
            else {
                if (!visited[i] && directedCycleDFS(adjMatrix, i, visited, onStack, cycleNodes)) {
                    // Cycle found, return the nodes forming the cycle
                    return cycleNodes;
                }
            }
        }

        // No cycle found, return an empty vector
        return {};
    }

    bool Algorithms::unDirectedCycleDFS(const std::vector<std::vector<int>>& adjMatrix, size_t node, size_t parent, std::vector<bool>& visited, std::vector<int>& cycleNodes) {
        // Mark the current node as visited and add it to the cycle path
        visited[node] = true;
        cycleNodes.push_back(node);
            for (size_t neighbor = 0; neighbor < adjMatrix.size(); ++neighbor) {
                // Check if there's an edge from the current node to its neighbor
                if (adjMatrix[node][neighbor] != 0) { // Consider only non-zero weighted edges
                    // Check if the neighbor has not been visited
                    if (!visited[neighbor]) {
                        // Recursively visit the neighbor
                        if (unDirectedCycleDFS(adjMatrix, neighbor, node, visited, cycleNodes)) {
                            return true; // Cycle found
                        }
                    } else if (neighbor != parent) {
                        cycleNodes.push_back(neighbor);
                        size_t start = 0;
                        for (size_t i = 0; i < cycleNodes.size(); i++) {
                            if (cycleNodes[i] == cycleNodes[cycleNodes.size()-1])
                            {
                                start = i;
                                break;
                            }
                        }
                        for (size_t i = 0; i < start; i++) {
                            cycleNodes.erase(cycleNodes.begin());
                        }
                        return true;
                    } 
                }
            }

            // If no cycle found, remove the current node from the cycle path
            cycleNodes.pop_back();
            return false;
    
    }

    bool Algorithms::directedCycleDFS(const std::vector<std::vector<int>>& adjMatrix, size_t node, std::vector<bool>& visited, std::vector<bool>& onStack, std::vector<int>& cycleNodes) {
        visited[node] = true;
        onStack[node] = true;
        cycleNodes.push_back(node); // Add the current node to the cycle path

        for (size_t neighbor = 0; neighbor < adjMatrix.size(); ++neighbor) {
            if (adjMatrix[node][neighbor] != 0) { // Consider only non-zero weighted edges
                if (!visited[neighbor]) {
                    if (directedCycleDFS(adjMatrix, neighbor, visited, onStack, cycleNodes)) {
                        return true; // Cycle found
                    }
                } else if (onStack[neighbor]) {
                    cycleNodes.push_back(neighbor);
                    size_t start = 0;
                    for (size_t i = 0; i < cycleNodes.size(); i++) {
                        if (cycleNodes[i] == cycleNodes[cycleNodes.size()-1])
                        {
                            start = i;
                            break;
                        }
                    }
                    for (size_t i = 0; i < start; i++) {
                        cycleNodes.erase(cycleNodes.begin());
                    }
                    // Cycle detected, return true
                    return true;
                }
            }
        }

        onStack[node] = false; // Reset onStack status before returning
        cycleNodes.pop_back(); // Remove the current node from the cycle path
        return false;
    }
    bool Algorithms::isSymmetric(const std::vector<std::vector<int>>& adjMatrix) {
        size_t n = adjMatrix.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (adjMatrix[i][j] != adjMatrix[j][i]) {
                    return false; // Not symmetric
                }
            }
        }
        return true; // Symmetric
    }

    std::string Algorithms::cycleToString(const std::vector<int>& cycle) {
        if (cycle.empty()) {
            return "No cycle found";
        } else {
            std::string cycleStr = "The cycle is: ";
            for (size_t i = 0; i < cycle.size(); ++i) {
                cycleStr += std::to_string(cycle[i]);
                if (i < cycle.size() - 1) {
                    cycleStr += "->";
                }
            }
            return cycleStr;
        }
    }


    std::vector<std::set<int>> Algorithms::isBipartite(const Graph& g) {
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        size_t numVertices = g.getNumVertices();
        std::vector<int> color(numVertices, -1); // Initialize all vertices as uncolored (-1)
        std::vector<std::set<int>> groups(2); // Vector to store the two groups
        std::queue<int> q;

        for (size_t startNode = 0; startNode < numVertices; ++startNode) {
            if (color[startNode] == -1) { // If the start node is uncolored
                // std::cout << "Starting BFS from node " << startNode << std::endl;
                q.push(startNode);
                color[startNode] = 0; // Color the start node with 0
                groups[0].insert(startNode); // Add start node to the first group

                while (!q.empty()) {
                    int current = q.front();
                    q.pop();

                    for (size_t neighbor = 0; neighbor < numVertices; ++neighbor) {
                        if (adjMatrix[static_cast<size_t>(current)][static_cast<size_t>(neighbor)] != 0) { // If there's an edge
                            // std::cout << "Visiting node " << neighbor << std::endl;
                            if (color[neighbor] == -1) { // If the neighbor is uncolored
                                color[neighbor] = 1 - color[static_cast<size_t>(current)]; // Color with the opposite color
                                // std::cout << "Coloring node " << neighbor << " with " << color[neighbor] << std::endl;
                                q.push(neighbor);
                                groups[static_cast<size_t>(color[neighbor])].insert(neighbor); // Add neighbor to the corresponding group
                            } else if (color[neighbor] == color[static_cast<size_t>(current)]) { // If neighbor has the same color as current
                                // Not bipartite, return empty vector
                                // std::cout << "Not bipartite! Color of node " << neighbor << " conflicts with color of node " << current << std::endl;
                                return std::vector<std::set<int>>();
                            }
                        }
                    }
                }
            }
        }

        return groups; // Return the two groups
    }

    std::string Algorithms::bipartiteGraphToString(const std::vector<std::set<int>>& groups) {
        std::stringstream ss;
        if (groups.empty()) {
            ss << "Graph is not bipartite!" << endl;
            return ss.str();
        }

        ss << "Group 1: ";
        for (int node : groups[0]) {
            ss << node << " ";
        }
        ss << "\n";

        ss << "Group 2: ";
        for (int node : groups[1]) {
            ss << node << " ";
        }
        ss << "\n";

        return ss.str();
    }

void Algorithms::negativeCycle(const Graph& g) {
    const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
    size_t numVertices = g.getNumVertices();

    // Initialize distances matrix with the same values as adjacency matrix
    std::vector<std::vector<int>> dist = adjMatrix;

    // Perform Floyd-Warshall algorithm
    for (size_t k = 0; k < numVertices; ++k) {
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max() &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

    }

    // Check for negative cycles explicitly
    for (size_t i = 0; i < numVertices; ++i) {
        if (dist[i][i] < 0) { // Check if the vertex i is reachable from itself with a negative weight
            std::cout << "Negative cycle found!" << std::endl;
            return;
        }
    }

        std::cout << "No negative cycle found!" << std::endl;
    }
}