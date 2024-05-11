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
    MatrixGraph(const std::string& filePath);
/**
 * @brief Destruktor klasy MatrixGraph
*/
    ~MatrixGraph();
/**
 * @brief Funkcja dodająca krawędź do grafu
 * @param v wierzchołek początkowy
 * @param w wierzchołek końcowy
 * @param weight waga krawędzi
*/
    void addEdge(int v, int w, int weight);

/**
 * @brief Funkcja wypisująca macierz sąsiedztwa grafu
*/
    void print();
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