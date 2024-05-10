#include "Graph.hpp"
#include <iostream>

using namespace std;

namespace ariel {
    // Constructor to initialize an empty graph with zero vertices
    Graph::Graph() : adjMatrix(vector<vector<int>>()), numVertices(0) {}

    // Constructor to initialize a graph with provided adjacency matrix and number of vertices
    Graph::Graph(const std::vector<std::vector<int>>& adjMatrix, size_t numVertices) : adjMatrix(adjMatrix), numVertices(numVertices) {}

    // Method to load a graph from a given adjacency matrix
    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
        // Check if the matrix is square
        size_t size = matrix.size();
        for (size_t i = 0; i < size; ++i) {
            if (matrix[i].size() != size) {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }

        // Set the adjacency matrix and number of vertices
        adjMatrix = matrix;
        numVertices = size;
    }

    // Method to print the adjacency matrix of the graph
    void Graph::printGraph() {
        std::cout << "Adjacency Matrix:" << std::endl;
        for (const auto &row : adjMatrix) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    // Method to get the number of vertices in the graph
    size_t Graph::getNumVertices() const {
        return numVertices;
    }

    // Method to get the adjacency matrix of the graph
    std::vector<std::vector<int>> Graph::getAdjMatrix() const {
        return adjMatrix;
    }

}
