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
 * @param outputToFile czy wynik ma być zapisany do pliku 1 - tak, 0 - nie
 * @param outputToFileName nazwa pliku do zapisu wyniku
*/
    void dijkstraAlgorithmToAll(int startVertex, bool outputToFile, std::string outputToFileName) override{
        std::cout << "Dijkstra's algorithm not implemented yet.";
    }
/**
 * @brief Funkcja implementująca algorytm Dijkstry do wszystkich wierzchołków
 * @param startVertex wierzchołek startowy
 * @param endVertex wierzchołek końcowy
 * @param outputToFile czy wynik ma być zapisany do pliku 1 - tak, 0 - nie
 * @param outputToFileName nazwa pliku do zapisu wyniku
*/
    void dijkstraAlgorithmToPoint(int startVertex, int endVertex, bool outputToFile, std::string outputToFileName) override{
        std::cout << "Dijkstra's algorithm not implemented yet.";
    }
};