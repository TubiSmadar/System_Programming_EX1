#include "Graph.hpp"
#include <iostream>

using namespace std;

namespace ariel {
    Graph::Graph() {

    }

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
        // Check if the matrix is square
        size_t size = matrix.size();
        for (size_t i = 0; i < size; ++i) {
            if (matrix[i].size() != size) {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }

        // Set the adjacency matrix
        adjMatrix = matrix;
        numVertices = size;

        if (isSymmetric(matrix)) {
            isDirected = true;
        }
        else {
            isDirected = false;
        }

    }

    void Graph::printGraph() {
        std::cout << "Adjanceny Matrix:" <<std::endl;
        for (const auto &row : adjMatrix) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    bool Graph::isSymmetric(std::vector<std::vector<int>> matrix) {
        int rows = matrix.size();
        if (rows == 0) {
            return true; // Empty matrix is symmetric
        }
        int cols = matrix[0].size();

        // Check if the matrix is square
        if (rows != cols) {
            return false; // Non-square matrices are not symmetric
        }

        // Check if the matrix is symmetric
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < i; ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false; // If corresponding elements are not equal, matrix is not symmetric
                }
            }
        }
        return true; // Matrix is symmetric
    }
    size_t Graph::getNumVertices() const {return adjMatrix.size();}

    std::vector<std::vector<int>> Graph::getAdjMatrix() const {return adjMatrix;}

}