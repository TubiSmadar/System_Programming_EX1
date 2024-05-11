/*
315638577
gunslokij@gmail.com
*/

#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <stack>
#include <set>
namespace ariel {

    // Function to perform Depth-First Search (DFS) to find a path starting from a given index in the graph
    void pathDFS(Graph& g, size_t index, vector<bool>& visited) {
        visited[index] = true; // Mark the current vertex as visited
        // Traverse all adjacent vertices of index
        for (size_t i = 0; i < visited.size(); ++i) {
            if (g.getAdjMatrix()[index][i] != 0 && !visited[i]) {
                pathDFS(g, i, visited); // Recursive call to visit unvisited adjacent vertices
            }
        }
    }

    // Function to check if the graph is connected
    int Algorithms::isConnected(Graph& g) {
        std::vector<bool> visited(g.getNumVertices(), false); // Initialize visited array to false
        size_t startIndex = 0; // Start DFS from vertex 0
        pathDFS(g, startIndex, visited); // Perform DFS to mark all reachable vertices
        // Check if all vertices are visited
        for (bool v : visited) {
            if (!v) {
                return 0; // Graph is not connected
            }
        }
        return 1; // Graph is connected
    }

    // Function to find the shortest path in the graph using Dijkstra's algorithm
    std::vector<int> Algorithms::shortestPath(const ariel::Graph& g, size_t start, size_t end) {
        const size_t graphSize = g.getNumVertices();
        std::vector<int> dist(graphSize, std::numeric_limits<int>::max()); // Initialize distances to infinity
        std::vector<int> parent(graphSize, -1); // To store the parent vertices
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, std::greater<std::pair<int, size_t>>> pq;

        dist[start] = 0; // Distance to start vertex is 0
        pq.emplace(0, start); // Insert start vertex into priority queue with distance 0
        while (!pq.empty()) {
            size_t u = pq.top().second; // Extract vertex with minimum distance from priority queue
            int u_dist = pq.top().first;
            pq.pop();

            if (u == end) {
                break; // Stop the search when the destination vertex is reached
            }

            if (u_dist > dist[u]) {
                continue; // Skip if this vertex has been relaxed before
            }

            // Relax all edges outgoing from vertex u
            for (size_t v = 0; v < graphSize; ++v) {
                if (g.getAdjMatrix()[u][v] != 0) { // Check if there is an edge from u to v
                    int weight = g.getAdjMatrix()[u][v]; // Get weight of edge from u to v
                    if (dist[u] + weight < dist[v]) { // Update distance if a shorter path is found
                        dist[v] = dist[u] + weight;
                        parent[v] = static_cast<int>(u); // Update parent of v to u
                        pq.emplace(dist[v], v); // Insert updated vertex into priority queue
                    }
                }
            }
        }

        // Reconstruct the shortest path from start to end
        std::vector<int> shortestPath;
        if (parent[end] == -1) {
            // If end vertex is not reachable from start vertex, return an empty vector
            return shortestPath;
        }

        int current = static_cast<int>(end);
        while (current != -1 && static_cast<size_t>(current) != start) {
            shortestPath.push_back(current);
            current = parent[static_cast<size_t>(current)]; // Update current vertex to its parent
        }
        shortestPath.push_back(static_cast<int>(start)); // Include start vertex in the shortest path
        std::reverse(shortestPath.begin(), shortestPath.end()); // Reverse the vector to get the path from start to end
        return shortestPath;
    }

    // Function to convert a shortest path represented by a vector of vertices to a string
    std::string ariel::Algorithms::shortestPathToString(const std::vector<int>& shortestPath) {
        if (shortestPath.empty()) {
            return "No path found"; // Handle the case where shortestPath is empty
        }

        std::ostringstream oss;
        for (size_t i = 0; i < shortestPath.size(); ++i) {
            oss << shortestPath[i]; // Access elements directly from the vector
            if (i != shortestPath.size() - 1) {
                oss << " -> "; // Add arrow separator between vertices
            }
        }
        return oss.str(); // Return the constructed string representation of the shortest path
    }

    // Function to check if a graph contains a cycle
    std::vector<int> Algorithms::isContainsCycle(const Graph& g) {
        // Get the adjacency matrix and number of vertices from the graph
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        size_t numVertices = g.getNumVertices();

        // Initialize boolean vectors to keep track of visited nodes and nodes on stack
        std::vector<bool> visited(numVertices, false);
        std::vector<bool> onStack(numVertices, false);
        size_t parent = SIZE_MAX; // Variable to store the parent node
        std::vector<int> cycleNodes; // Vector to store the nodes forming the cycle

        // Iterate through each vertex in the graph
        for (size_t i = 0; i < numVertices; ++i) {
            // Check if the graph is symmetric
            if (isSymmetric(g.getAdjMatrix())){
                // If the vertex is not visited and there is an undirected cycle starting from it
                if (!visited[i] && unDirectedCycleDFS(adjMatrix, i, parent, visited, cycleNodes)) {
                    // Cycle found, return the nodes forming the cycle
                    return cycleNodes;
                }
            } else {
                // If the vertex is not visited and there is a directed cycle starting from it
                if (!visited[i] && directedCycleDFS(adjMatrix, i, visited, onStack, cycleNodes)) {
                    // Cycle found, return the nodes forming the cycle
                    return cycleNodes;
                }
            }
        }

        // No cycle found, return an empty vector
        return {};
    }

    // Depth-First Search (DFS) function to detect undirected cycles in the graph
    bool Algorithms::unDirectedCycleDFS(const std::vector<std::vector<int>>& adjMatrix, size_t node, size_t parent, std::vector<bool>& visited, std::vector<int>& cycleNodes) {
        // Mark the current node as visited and add it to the cycle path
        visited[node] = true;
        cycleNodes.push_back(node);

        // Iterate through the neighbors of the current node
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
                    // If the neighbor is visited and not the parent, a cycle is found
                    // Adjust the cycle nodes vector to represent the cycle path
                    cycleNodes.push_back(neighbor);
                    size_t start = 0;
                    for (size_t i = 0; i < cycleNodes.size(); i++) {
                        if (cycleNodes[i] == cycleNodes[cycleNodes.size()-1]) {
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

    // Depth-First Search (DFS) function to detect directed cycles in the graph
    bool Algorithms::directedCycleDFS(const std::vector<std::vector<int>>& adjMatrix, size_t node, std::vector<bool>& visited, std::vector<bool>& onStack, std::vector<int>& cycleNodes) {
        // Mark the current node as visited and add it to the cycle path
        visited[node] = true;
        onStack[node] = true;
        cycleNodes.push_back(node);

        // Iterate through the neighbors of the current node
        for (size_t neighbor = 0; neighbor < adjMatrix.size(); ++neighbor) {
            // Check if there's an edge from the current node to its neighbor
            if (adjMatrix[node][neighbor] != 0) { // Consider only non-zero weighted edges
                // If the neighbor is not visited, recursively visit it
                if (!visited[neighbor]) {
                    if (directedCycleDFS(adjMatrix, neighbor, visited, onStack, cycleNodes)) {
                        return true; // Cycle found
                    }
                } else if (onStack[neighbor]) {
                    // If the neighbor is already on the stack, a cycle is detected
                    // Adjust the cycle nodes vector to represent the cycle path
                    cycleNodes.push_back(neighbor);
                    size_t start = 0;
                    for (size_t i = 0; i < cycleNodes.size(); i++) {
                        if (cycleNodes[i] == cycleNodes[cycleNodes.size()-1]) {
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

        // Reset onStack status before returning
        onStack[node] = false;
        // Remove the current node from the cycle path
        cycleNodes.pop_back();
        return false;
    }

    // Function to check if the given adjacency matrix represents a symmetric graph
    bool Algorithms::isSymmetric(const std::vector<std::vector<int>>& adjMatrix) {
        size_t n = adjMatrix.size();
        // Iterate through the rows and columns of the adjacency matrix
        for (size_t i = 0; i < n; ++i) {
            // Check if the diagonal elements are zero
            if(adjMatrix[i][i]!=0){
                return false;
            }
            // Iterate through the lower triangle of the matrix
            for (size_t j = 0; j < i; ++j) {
                // Check if the corresponding elements are equal
                if (adjMatrix[i][j] != adjMatrix[j][i]) {
                    return false; // Not symmetric
                }
            }
        }
        return true; // Symmetric
    }

    // Function to convert a cycle represented by a vector of nodes to a string
    std::string Algorithms::cycleToString(const std::vector<int>& cycle) {
        if (cycle.empty()) {
            return "No cycle found"; // Handle the case where no cycle is found
        } else {
            std::string cycleStr = "The cycle is: ";
            // Append each node to the string with arrow separator
            for (size_t i = 0; i < cycle.size(); ++i) {
                cycleStr += std::to_string(cycle[i]);
                if (i < cycle.size() - 1) {
                    cycleStr += "->";
                }
            }
            return cycleStr; // Return the constructed cycle string
        }
    }

    // Function to check if a graph is bipartite and return the two groups if it is
    std::vector<std::set<int>> Algorithms::isBipartite(const Graph& g) {
        // Get the adjacency matrix and number of vertices from the graph
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        size_t numVertices = g.getNumVertices();

        // Initialize the color vector to store colors of vertices (-1: uncolored, 0: color 1, 1: color 2)
        std::vector<int> color(numVertices, -1);
        // Initialize a vector of sets to store the two groups
        std::vector<std::set<int>> groups(2);
        // Queue for BFS traversal
        std::queue<int> q;

        // Iterate through each vertex in the graph
        for (size_t startNode = 0; startNode < numVertices; ++startNode) {
            // If the start node is uncolored
            if (color[startNode] == -1) {
                // Start BFS traversal from the start node
                q.push(startNode);
                color[startNode] = 0; // Color the start node with 0 (color 1)
                groups[0].insert(startNode); // Add start node to the first group

                // Perform BFS traversal
                while (!q.empty()) {
                    int current = q.front();
                    q.pop();

                    // Iterate through the neighbors of the current node
                    for (size_t neighbor = 0; neighbor < numVertices; ++neighbor) {
                        // If there's an edge from the current node to its neighbor
                        if (adjMatrix[static_cast<size_t>(current)][static_cast<size_t>(neighbor)] != 0) {
                            // If the neighbor is uncolored
                            if (color[neighbor] == -1) {
                                // Color with the opposite color of the current node
                                color[neighbor] = 1 - color[static_cast<size_t>(current)];
                                q.push(neighbor);
                                // Add neighbor to the corresponding group
                                groups[static_cast<size_t>(color[neighbor])].insert(neighbor);
                            } else if (color[neighbor] == color[static_cast<size_t>(current)]) {
                                // If neighbor has the same color as current, graph is not bipartite
                                return std::vector<std::set<int>>(); // Return empty vector
                            }
                        }
                    }
                }
            }
        }

        return groups; // Return the two groups
    }

    // Function to convert bipartite groups to a string
    std::string Algorithms::bipartiteGraphToString(const std::vector<std::set<int>>& groups) {
        std::stringstream ss;
        // If the groups vector is empty, graph is not bipartite
        if (groups.empty()) {
            ss << "Graph is not bipartite!" << std::endl;
            return ss.str(); // Return the error message
        }

        // Print group 1
        ss << "Group 1: ";
        for (int node : groups[0]) {
            ss << node << " ";
        }
        ss << "\n";

        // Print group 2
        ss << "Group 2: ";
        for (int node : groups[1]) {
            ss << node << " ";
        }
        ss << "\n";

        return ss.str(); // Return the bipartite groups as string
    }

    // Function to detect negative cycles in the graph
    void Algorithms::negativeCycle(const Graph& g) {
        // Get the adjacency matrix and number of vertices from the graph
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        size_t numVertices = g.getNumVertices();

        // Initialize distances matrix with the same values as adjacency matrix
        std::vector<std::vector<int>> dist = adjMatrix;

        // Perform Floyd-Warshall algorithm to find shortest distances between all pairs of vertices
        for (size_t k = 0; k < numVertices; ++k) {
            for (size_t i = 0; i < numVertices; ++i) {
                for (size_t j = 0; j < numVertices; ++j) {
                    if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max() &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        // Update distances if a shorter path is found
                        if (!isSymmetric(adjMatrix)) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        } else {
                            if (adjMatrix[i][j] != 0 && dist[i][j] != std::numeric_limits<int>::max() && dist[i][j] + adjMatrix[i][j] < dist[i][j]){
                                dist[i][j] = dist[i][j] + adjMatrix[i][j];
                                // Check for negative cycle
                                if (k == numVertices-1 && dist[i][j] < 0) {
                                    std::cout << "Negative cycle found!" << std::endl;
                                    return;
                                }
                            }
                        }
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
