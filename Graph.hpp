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

        public:
            Graph();
            Graph(const std::vector<std::vector<int>>&, size_t);

            void loadGraph(const std::vector<std::vector<int>> &matrix);
            void printGraph();
            std::vector<std::vector<int>> getAdjMatrix() const;
            size_t getNumVertices() const;
    };
}

#endif
