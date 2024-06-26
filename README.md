

# Algorithms Library

This repository contains a C++ exercise as part of system programming course in Ariel University.

## Prerequisites
- C++ compiler supporting C++11 or later.
- Makefile (for building the project).

  
## Features

- `Graph Representation`: The library uses adjacency matrices to represent graphs.
- `Algorithms`: It includes implementations for several graph algorithms:
   - Checking if a graph is connected.
   - Finding shortest paths between vertices using Dijkstra's algorithm.
   - Detecting cycles in directed and undirected graphs.
   - Determining if a graph is bipartite.
   - Detecting negative cycles using the Floyd-Warshall algorithm.
- `Convenience Functions`: Utility functions are provided for converting graph properties into human-readable strings.

## Documentation

### Graph class
- `Graph()`: Default constructor.
- `Graph(const std::vector<std::vector<int>>& adjMatrix, size_t numVertices)`: Constructor with adjacency matrix and number of vertices.
- `void loadGraph(const std::vector<std::vector<int>>& matrix)`: Load a graph from an adjacency matrix.
- `void printGraph()`: Print the adjacency matrix.
- `size_t getNumVertices() const`: Get the number of vertices in the graph.
- `std::vector<std::vector<int>> getAdjMatrix() const`: Get the adjacency matrix of the graph.

### Algorithms class
- `std::vector<int> isConnected(const Graph& g)`: Check if the graph is connected.
- `std::vector<int> shortestPath(const Graph& g, size_t start, size_t end)`: Find the shortest path between two vertices.
- `std::vector<int> isContainsCycle(const Graph& g)`: Detect cycles in the graph.
- `std::vector<std::set<int>> isBipartite(const Graph& g)`: Check if the graph is bipartite and return the two groups.
- `void negativeCycle(const Graph& g)`: Detect negative cycles in the graph.

### Files

- `Graph.hpp`: Header file containing the declaration of the Graph class.
- `Graph.cpp`: Source file containing the implementation of the Graph class.
- `Algorithms.hpp`: Header file containing the declaration of algorithm functions.
- `Algorithms.cpp`: Source file containing the implementation of algorithm functions.
- `Makefile`: Makefile for building and running the project.

## Usage

### cloning 

>To clone repository:

`git clone https://github.com/TubiSmadar/System_Programming_EX1.git`

`cd System_Programming_EX1`

To build and run the project, you can use the provided Makefile. Here are the available commands:

### Running

> To run the demo program:

`make demo`

`./demo`

### Testing

>To run tests:

`make test`

`./test`

### Memory Checking with Valgrind

>To run Valgrind for memory checking:

`make valgrind`

### Cleaning Up

>To clean up compiled files:

`make clean`




# מטלה 1 - גרפים (Classes and Namespaces)

המטרה שלכם במטלה הזאת היא ליצור מחלקה שמייצגת גרף ולממש אלגוריתמים על הגרפים (זה הזמן להזכר בקורס אלגוריתמים 1).

במטלה הזאת הייצוג של הגרף שלכם יתבצע בעזרת מטריצת שכנויות - https://he.wikipedia.org/wiki/%D7%9E%D7%98%D7%A8%D7%99%D7%A6%D7%AA_%D7%A9%D7%9B%D7%A0%D7%95%D7%AA.

הגרף יכול להיות גרף מכוון ולא מכוון וגם גרף ממושקל. מטריצת השכנויות חייבת להיות מטריצה ריבועית.

עליכם לכתוב את הקבצים הבאים:

```
Graph.cpp
Algorithms.cpp
```

הקובץ `Graph.cpp` מכיל מחלקה המייצגת גרף.
המחלקה מכילה את הפעולות `loadGraph` המקבלת מטריצת שכנויות וטוענת אותה לתוך הגרף ו-`printGraph` שמדפיסה את הייצוג של הגרף (הפורמט לבחירתכם, ראו דוגמה ב-`Demo.cpp`).

הקובץ `Algorithms.cpp` מכיל מימושים לאלגוריתמים על גרפים. ביניהם:

- `isConnected(g)` - האלגוריתם מקבל גרף ומחזיר 1 אם הגרף קשיר (אחרת מחזיר 0).
- `shortestPath(g,start,end)` - האלגוריתם מקבל גרף, קודקוד התחלה וקודקוד סיום ומחזיר את המסלול הקל ביותר (במקרה שהגרף לא ממושקל - הקצר ביותר) בין שני הקודקודים. במידה ואין מסלול כזה, האלגוריתם יחזיר -1.
- `isContainsCycle(g)` - האלגוריתם מקבל גרף ומדפיס מעגל כלשהו. אם לא קיים מעגל בגרף, האלגוריתם יחזיר 0.
- `isBipartite(g)` - האלגוריתם מקבל גרף ומחזיר את החלוקה של הגרף לגרף דו-צדדי. אם אי אפשר לחלק את הגרף, האלגוריתם יחזיר 0.
- `negativeCycle(g)` - האלגוריתם מקבל גרף ומוצא מעגל שלילי (כלומר מעגל שסכום המשקלים של הצלעות שלילי). אם לא קיים מעגל כזה, האלגוריתם ידפיס שלא קיים מעגל שלילי.

הקובץ `Demo.cpp` מכיל דוגמאות של קלטים ופלטים.
עליכם לכתוב בתחילת כל קובץ את מספר תעודת הזהות שלכם ואת המייל. כמו כן, בנוסף לקבצים של המטלה אתם נדרשים להגיש גם קובץ README המתאר את אופן המימוש ואת החלוקה שביצעתם בקוד (סוג של מדריך משתמש). אי עמידה בהנחיות תגרור הפחתה בציון. בהצלחה!
  
