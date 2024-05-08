#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

using namespace std;

namespace ariel{
    class Graph {
        private:
            std::vector<std::vector<int>> adjMatrix; 
            size_t numVertices;
            bool isDirected;

        public:
            Graph();
            void loadGraph(const std::vector<std::vector<int>> &matrix);
            void printGraph();
            bool isSymmetric(std::vector<std::vector<int>> matrix) ;
            std::vector<std::vector<int>> getAdjMatrix() const;
            size_t getNumVertices() const;
            bool getIsDirected() {return isDirected;}
    };
}

#endif