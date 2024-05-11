#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <queue>

class ListGraph : public Graph {
private:
    std::vector<std::vector<std::pair<int, int>>> _adjacencyList;
    int _numVertices;

public:
/**
 * @brief Konstruktor klasy ListGraph
 * @param filePath ścieżka do pliku z danymi grafu
*/
    ListGraph(const std::string& filePath);
/**
 * @brief Destruktor klasy ListGraph
*/
    ~ListGraph();
/**
 * @brief Funkcja dodająca krawędź do grafu
 * @param v wierzchołek początkowy
 * @param w wierzchołek końcowy
 * @param weight waga krawędzi
*/
    void addEdge(int v, int w, int weight) override;
/**
 * @brief Funkcja wypisująca listę sąsiedztwa grafu
*/
    void print() override;
/**
 * @brief Funkcja implementująca algorytm Dijkstry do wszystkich wierzchołków
 * @param startVertex wierzchołek startowy
 * @return wektor z odległościami do wszystkich wierzchołków
*/
    std::vector<int> dijkstraAlgorithmToAll(int startVertex) override;
/**
 * @brief Funkcja implementująca algorytm Dijkstry do wszystkich wierzchołków
 * @param startVertex wierzchołek startowy
 * @param endVertex wierzchołek końcowy
 * @return waga najkrótszej ścieżki
*/
    int dijkstraAlgorithmToPoint(int startVertex, int endVertex) override;
};