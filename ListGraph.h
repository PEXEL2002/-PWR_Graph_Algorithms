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

    void addEdge(int v, int w, int weight) override {
        if (v >= numVertices || w < 0) {
            throw std::out_of_range("Vertex index out of valid range");
        }
        adjacencyList[v].push_back({w, weight});
    }

    void print() override {
        for (int i = 0; i < numVertices; i++) {
            std::cout << i << ": ";
            for (const auto& edge : adjacencyList[i]) {
                std::cout << edge.first << "(" << edge.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    void dijkstraAlgorithm(int startVertex) override {
        // Dijkstra's algorithm will be implemented here.
        std::cout << "Dijkstra's algorithm not implemented yet." << std::endl;
    }
};
