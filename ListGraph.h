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
        std::vector<int> distance(numVertices, INT_MAX); // Initialize distances to all vertices as infinity
        std::vector<bool> visited(numVertices, false); // Initialize all vertices as not visited
        std::vector<int> predecessor(numVertices, -1); // Initialize all predecessors as -1
        distance[startVertex] = 0;// Distance from start vertex to itself is 0
        for(int i = 0; i < numVertices - 1; i++){ // Find shortest path for all vertices
            int u = -1;
            for(int j = 0; j < numVertices; j++){ // Find the vertex with the minimum distance
                if(!visited[j] && (u == -1 || distance[j] < distance[u])){
                    u = j;
                }
            }
            visited[u] = true;
            for(const auto& edge : adjacencyList[u]){ // Update distances to all adjacent vertices
                int v = edge.first;
                int weight = edge.second;
                if(distance[u] != INT_MAX && distance[u] + weight < distance[v]){
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
            }
        }
        // Display all distances and paths
        std::cout << "Dijkstra List: " << std::endl;
        for(int i = 0; i < numVertices; i++){
            if (i == startVertex) continue; // Skip start vertex
            std::cout << "Distance from " << startVertex+1 << " to " << i+1 << " is " << distance[i];
            if(distance[i] == INT_MAX){
                std::cout << " (No path)" << std::endl;
            } else {
                std::cout << " Path: ";
                    std::vector<int> path;
                    for (int at = i; at != -1; at = predecessor[at]) { //   Construct path
                        path.insert(path.begin(), at);  // Insert at the    beginning
                    }
                    for (int v : path) { // Print path
                        std::cout << v+1 << " ";
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
        std::vector<int> distance(numVertices, INT_MAX); // Initialize distances to all vertices as infinity
        std::vector<bool> visited(numVertices, false); // Initialize all vertices as not visited
        std::vector<int> predecessor(numVertices, -1); //  Initialize all predecessors as -1
        distance[startVertex] = 0; // Distance from start vertex to itself is 0
        for(int i = 0; i < numVertices - 1; i++){ // Find shortest path for all vertices
            int u = -1;
            for(int j = 0; j < numVertices; j++){ // Find the vertex with the minimum distance
                if(!visited[j] && (u == -1 || distance[j] < distance[u])){
                    u = j;
                }
            }
            visited[u] = true; 
            for(const auto& edge : adjacencyList[u]){ // Update distances to all adjacent vertices
                int v = edge.first;
                int weight = edge.second;
                if(distance[u] != INT_MAX && distance[u] + weight < distance[v]){
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
            }
        }
        // Display distance and path
        std::cout << "Dijkstra List: " << std::endl;
        std::cout << "Distance from " << startVertex+1 << " to " << endVertex+1;
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
                std::cout << v+1 << " ";
            }
        }
        std::cout << std::endl;
        }
};
