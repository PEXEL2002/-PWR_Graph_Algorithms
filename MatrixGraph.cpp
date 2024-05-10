#include "MatrixGraph.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <set>

MatrixGraph::MatrixGraph(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }
    std::string line;
    _numVertices = 0;
    std::vector<std::vector<int>> tempMatrix;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int weight;
        while (iss >> weight) {
            row.push_back(weight);
        }
        if (_numVertices == 0) {
            _numVertices = row.size();
        }
        tempMatrix.push_back(row);
    }

    if (tempMatrix.size() != _numVertices) {
        throw std::runtime_error("Matrix is not square or data is invalid");
    }

    _adjMatrix = tempMatrix;
    file.close();
}
MatrixGraph::~MatrixGraph(){}
void MatrixGraph::addEdge(int v, int w, int weight) {
     if (v >= _numVertices || w >= _numVertices || v < 0 || w < 0) {
         throw std::out_of_range("Vertex index out of valid range");
     }
     _adjMatrix[v][w] = weight;
}
void MatrixGraph::print() {
    std::cout << "Matrix: " << std::endl;
    for (int i = 0; i < _numVertices; i++) {
        for (int j = 0; j < _numVertices; j++) {
            std::cout << _adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void MatrixGraph::dijkstraAlgorithmToAll(int startVertex) {
    std::vector<int> distances(_numVertices, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distances[startVertex] = 0;
    pq.push({0, startVertex});

    while (!pq.empty()) { // while there are still vertices to visit
        int currentVertex = pq.top().second;
        pq.pop();

        for (int adjacent = 0; adjacent < _numVertices; adjacent++) { // iterate through all vertices
            if (_adjMatrix[currentVertex][adjacent] != 0) { // Assuming 0 as no edge
                int weight = _adjMatrix[currentVertex][adjacent];
                if (distances[currentVertex] + weight < distances[adjacent]) {
                    distances[adjacent] = distances[currentVertex] + weight;
                    pq.push({distances[adjacent], adjacent});
                }
            }
        }
    }

    // Print or process distances
    for (int i = 0; i < _numVertices; i++) {
        if(distances[i] != std::numeric_limits<int>::max()){
            if(i == startVertex){
                continue;
            }else{
                std::cout << "Najkrótsza ścieżka od wierzchołka " << startVertex << " do wierzchołka " << i << " wynosi " << distances[i] << std::endl;
            }
        }
        std::cout << "Brak połączenia między wierzchołkiem " << startVertex << " a " << i << std::endl;
    }
}
void MatrixGraph::dijkstraAlgorithmToPoint(int startVertex, int endVertex) {
    std::vector<int> distances(_numVertices, std::numeric_limits<int>::max());
    std::vector<bool> visited(_numVertices, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distances[startVertex] = 0;
    pq.push({0, startVertex});

    while (!pq.empty()) { // while there are still vertices to visit
        int currentVertex = pq.top().second;
        pq.pop();
        // if currentVertex is the endVertex, print the distance and return
        if (currentVertex == endVertex) {
            std::cout << "Najkrótsza ścieżka od wierzchołka " << startVertex << " do wierzchołka " << endVertex << " wynosi " << distances[currentVertex] << std::endl;
            return;
        }

        if (visited[currentVertex]) continue;
        visited[currentVertex] = true;

        for (int adjacent = 0; adjacent < _numVertices; adjacent++) { // iterate through all vertices
            if (_adjMatrix[currentVertex][adjacent] != 0) {
                int weight = _adjMatrix[currentVertex][adjacent];
                if (distances[currentVertex] + weight < distances[adjacent]) {
                    distances[adjacent] = distances[currentVertex] + weight;
                    pq.push({distances[adjacent], adjacent});
                }
            }
        }
    }

    // if the function reaches here, there is no path from startVertex to endVertex
    std::cout << "Ścieżka od wierzchołka " << startVertex << " do wierzchołka " << endVertex << " nie istnieje." << std::endl;
}