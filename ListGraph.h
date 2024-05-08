#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>

class ListGraph : public Graph {
private:
    std::vector<std::list<std::pair<int, int>>> adjacencyList;
    int numVertices;

public:
/**
 * @brief Konstruktor klasy ListGraph
 * @param filePath ścieżka do pliku z danymi grafu
*/
    ListGraph(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file");
        }

        std::string line;
        numVertices = 0;
        // Czytaj każdą linię pliku, która reprezentuje listę sąsiedztwa jednego wierzchołka
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::list<std::pair<int, int>> vertexList;

            while (iss >> token) {
                int pos = token.find('(');
                int endPos = token.find(')');
                int vertex = std::stoi(token.substr(0, pos));
                int weight = std::stoi(token.substr(pos + 1, endPos - pos - 1));
                vertexList.push_back({vertex, weight});
            }
            adjacencyList.push_back(vertexList);
            numVertices++;
        }

        file.close();
    }
/**
 * @brief Funkcja dodająca krawędź do grafu
 * @param v wierzchołek początkowy
 * @param w wierzchołek końcowy
 * @param weight waga krawędzi
*/
    void addEdge(int v, int w, int weight) override {
        if (v >= numVertices || w < 0) {
            throw std::out_of_range("Vertex index out of valid range");
        }
        adjacencyList[v].push_back({w, weight});
    }
/**
 * @brief Funkcja wypisująca listę sąsiedztwa grafu
*/
    void print() override {
        for (int i = 0; i < numVertices; i++) {
            std::cout << i << ": ";
            for (const auto& edge : adjacencyList[i]) {
                std::cout << edge.first << "(" << edge.second << ") ";
            }
            std::cout << std::endl;
        }
    }
/**
 * @brief Funkcja implementująca algorytm Dijkstry do wszystkich wierzchołków
*/
    // Placeholder for Dijkstra's algorithm
    void dijkstraAlgorithmToAll(int startVertex) override{
        std::cout << "Dijkstra's algorithm not implemented yet.";
    }
/**
 * @brief Funkcja implementująca algorytm Dijkstry do jednego wierzchołka
 * @param startVertex wierzchołek startowy
 * @param endVertex wierzchołek końcowy
*/
    void dijkstraAlgorithmToPoint(int startVertex, int endVertex) override{
        std::cout << "Dijkstra's algorithm not implemented yet.";
    }
};
