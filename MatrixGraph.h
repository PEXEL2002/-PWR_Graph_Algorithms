#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class MatrixGraph: public Graph {
private:
    std::vector<std::vector<int>> _adjMatrix;
    int _numVertices;

public:
/**
 * @brief Konstruktor klasy MatrixGraph
 * @param filePath ścieżka do pliku z danymi grafu
*/
    MatrixGraph(const std::string& filePath) {
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

/**
 * @brief Funkcja dodająca krawędź do grafu
 * @param v wierzchołek początkowy
 * @param w wierzchołek końcowy
 * @param weight waga krawędzi
*/
    void addEdge(int v, int w, int weight) {
        if (v >= _numVertices || w >= _numVertices || v < 0 || w < 0) {
            throw std::out_of_range("Vertex index out of valid range");
        }
        _adjMatrix[v][w] = weight;
    }

/**
 * @brief Funkcja wypisująca macierz sąsiedztwa grafu
*/
    void print() {
        for (int i = 0; i < _numVertices; i++) {
            for (int j = 0; j < _numVertices; j++) {
                std::cout << _adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
/**
 * @brief Funkcja implementująca algorytm Dijkstry do wszystkich wierzchołków
 * @param startVertex wierzchołek startowy
*/
    void dijkstraAlgorithmToAll(int startVertex) override {
        if (startVertex >= _numVertices || startVertex < 0) {
            throw std::out_of_range("Vertex index out of valid range");
        }
        std::vector<int> distance(_numVertices, INT_MAX); // Initialize distances to all vertices as infinity
        std::vector<bool> visited(_numVertices, false); // Initialize all vertices as not visited
        std::vector<int> predecessor(_numVertices, -1); // Initialize all predecessors as -1
        distance[startVertex] = 0; // Distance from start vertex to itself is 0

        for (int i = 0; i < _numVertices; i++) { // Find shortest path for all vertices
            int minDistance = INT_MAX;
            int minIndex = -1;
            for (int j = 0; j < _numVertices; j++) { // Find the vertex with the minimum distance
                if (!visited[j] && distance[j] <= minDistance) {
                    minDistance = distance[j];
                    minIndex = j;
                }
            }
            visited[minIndex] = true;
            for (int j = 0; j < _numVertices; j++) { // Update distances to all adjacent vertices
                if (!visited[j] && _adjMatrix[minIndex][j] && distance[minIndex] != INT_MAX && distance[minIndex] + _adjMatrix[minIndex][j] < distance[j]) {
                    distance[j] = distance[minIndex] + _adjMatrix[minIndex][j];
                    predecessor[j] = minIndex;
                }
            }
        }

        // Display all distances and paths
        for (int i = 0; i < _numVertices; i++) {
            if (i == startVertex) continue; // Skip start vertex
            std::cout << "Distance from " << startVertex << " to " << i << " is " << distance[i];
            if (distance[i] == INT_MAX) {
                std::cout << " (No path)" << std::endl;
            } else {
                std::cout << " Path: ";
                std::vector<int> path;
                for (int at = i; at != -1; at = predecessor[at]) { // Construct path
                    path.insert(path.begin(), at);  // Insert at the beginning
                }
                for (int v : path) { // Print path
                    std::cout << v << " ";
                }
                std::cout << std::endl;
            }
        }
    }
/**
 * @brief Funkcja implementująca algorytm Dijkstry do wszystkich wierzchołków
 * @param startVertex wierzchołek startowy
 * @param endVertex wierzchołek końcowy
 * @param tests czy funkcja jest wywoływana w testach 1 - tak, 0 - nie
*/
    void dijkstraAlgorithmToPoint(int startVertex, int endVertex) override {
        if (startVertex >= _numVertices || endVertex >= _numVertices || startVertex < 0 || endVertex < 0) {
            throw std::out_of_range("Vertex index out of valid range");
        }
        if (startVertex == endVertex) {
            throw std::invalid_argument("Start and end vertex are the same");
        }
        std::vector<int> distance(_numVertices, INT_MAX); // Initialize distances to all vertices as infinity
        std::vector<bool> visited(_numVertices, false); // Initialize all vertices as not visited
        std::vector<int> predecessor(_numVertices, -1); //  Initialize all predecessors as -1
        distance[startVertex] = 0; // Distance from start vertex to itself is 0

        for (int i = 0; i < _numVertices; i++) { // Find shortest path for all vertices
            int minDistance = INT_MAX;
            int minIndex = -1;
            for (int j = 0; j < _numVertices; j++) { // Find the vertex with the minimum distance
                if (!visited[j] && distance[j] <= minDistance) {
                    minDistance = distance[j];
                    minIndex = j;
                }
            }
            visited[minIndex] = true;
            for (int j = 0; j < _numVertices; j++) { // Update distances to all adjacent vertices
                if (!visited[j] && _adjMatrix[minIndex][j] && distance[minIndex] != INT_MAX && distance[minIndex] + _adjMatrix[minIndex][j] < distance[j]) {
                    distance[j] = distance[minIndex] + _adjMatrix[minIndex][j];
                    predecessor[j] = minIndex;
                }
            }
        }

        std::cout << "Distance from " << startVertex << " to " << endVertex;
        // Display distance and path
        if (distance[endVertex] == INT_MAX) { // If there is no path
            std::cout << ":No path" << std::endl;
        } else {
            std::cout << " is " << distance[endVertex] << " Path: ";
            std::vector<int> path;
            for (int at = endVertex; at != -1; at = predecessor[at]) { // Construct path
                path.insert(path.begin(), at);
            }
            for (int v : path) { // Print path
                std::cout << v << " ";
            }
        }
    }
};