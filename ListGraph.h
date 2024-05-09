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
        std::cout << "List: " << std::endl;
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
 * @param startVertex wierzchołek startowy
*/
    void dijkstraAlgorithmToAll(int startVertex) override{
        if (startVertex >= numVertices || startVertex < 0) {
            throw std::out_of_range("Vertex index out of valid range");
        }
        std::vector<int> distance(numVertices, INT_MAX);
        std::vector<bool> visited(numVertices, false);
        std::vector<int> predecessor(numVertices, -1);
        distance[startVertex] = 0;
        for(int i = 0; i < numVertices - 1; i++){
            int u = -1;
            for(int j = 0; j < numVertices; j++){
                if(!visited[j] && (u == -1 || distance[j] < distance[u])){
                    u = j;
                }
            }
            visited[u] = true;
            for(const auto& edge : adjacencyList[u]){
                int v = edge.first;
                int weight = edge.second;
                if(distance[u] != INT_MAX && distance[u] + weight < distance[v]){
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
            }
        }
        std::cout << "Dijkstra List: " << std::endl;
        for(int i = 0; i < numVertices; i++){
            if (i == startVertex) continue; // Skip start vertex
            if(distance[i] == INT_MAX){
            std::cout << "No path from " << startVertex+1 << " to " << i+1 << std::endl;
            } else {
            std::cout << "Distance from " << startVertex+1 << " to " << i+1 << " is " << distance[i];
            std::vector<int> path;
            int currentVertex = i;
            while(currentVertex != startVertex){
                path.push_back(currentVertex);
                currentVertex = predecessor[currentVertex];
            }
            path.push_back(startVertex);
            std::cout << " Path: ";
            for(int j = path.size() - 1; j >= 0; j--){
                std::cout << path[j] + 1;
                if(j != 0){
                std::cout << " ";
                }
            }
            std::cout << std::endl;
            }
        }
    }
/**
 * @brief Funkcja implementująca algorytm Dijkstry do wszystkich wierzchołków
 * @param startVertex wierzchołek startowy
 * @param endVertex wierzchołek końcowy
*/
    void dijkstraAlgorithmToPoint(int startVertex, int endVertex) override{
        if(startVertex >= numVertices || endVertex >= numVertices || startVertex < 0 || endVertex < 0){
            throw std::out_of_range("Vertex index out of valid range");
        }
        if(startVertex == endVertex){
            throw std::invalid_argument("Start and end vertex are the same");
        }
        std::vector<int> distance(numVertices, INT_MAX);
        std::vector<bool> visited(numVertices, false);
        std::vector<int> predecessor(numVertices, -1);
        distance[startVertex] = 0;
        for(int i = 0; i < numVertices - 1; i++){
            int u = -1;
            for(int j = 0; j < numVertices; j++){
                if(!visited[j] && (u == -1 || distance[j] < distance[u])){
                    u = j;
                }
            }
            visited[u] = true;
            for(const auto& edge : adjacencyList[u]){
                int v = edge.first;
                int weight = edge.second;
                if(distance[u] != INT_MAX && distance[u] + weight < distance[v]){
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
            }
        }
        if(distance[endVertex] == INT_MAX){
            std::cout << "No path from " << startVertex << " to " << endVertex << std::endl;
        } else {
            std::cout << "Dijkstra List: " << std::endl;
            std::cout << "Distance from " << startVertex+1 << " to " << endVertex+1 << " is " << distance[endVertex];
            std::vector<int> path;
            int currentVertex = endVertex;
            while(currentVertex != startVertex){
                path.push_back(currentVertex);
                currentVertex = predecessor[currentVertex];
            }
            path.push_back(startVertex);
            std::cout << " Path: ";
            for(int i = path.size() - 1; i >= 0; i--){
                std::cout << path[i] + 1;
                if(i != 0){
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};
