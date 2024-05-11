#pragma once
#include "MatrixGraph.h"
#include "ListGraph.h"
#include <string>
/**
 * @brief Generuje dane grafu o zadanej liczbie wierzchołków i gęstości
 * @param vertices liczba wierzchołków
 * @param density gęstość grafu w procentach
*/
void generateGraphData(int vertices, int density, std::string fileName = "");
/**
 * @brief Funkcja generująca losowe wierzchołki
 * @param maxVertices maksymalna liczba wierzchołków
 * @return wieszchołek
*/
int generateVertices(int maxVertices);
/**
 * @brief Funkcja wypiująca wektor
 * @param vec wektor
 * @param startVertex wierzchołek startowy
*/
void printVector(std::vector<int>& vec, int startVertex)
/**
 * @brief Funkcja przprowadzająca algorytm Dijkstry do wszystkich wierzchołków
 * @param mG graf w postaci macierzy sąsiedztwa
 * @param lG graf w postaci listy sąsiedztwa
*/
void uiDijkstraAll(MatrixGraph& mG, ListGraph& lG);
/**
 * @brief Funkcja przprowadzająca algorytm Dijkstry do wierzchołka
 * @param mG graf w postaci macierzy sąsiedztwa
 * @param lG graf w postaci listy sąsiedztwa
*/
void uiDijkstraToPoint(MatrixGraph& mG, ListGraph& lG);
/**
 * @brief Funkcja wypisująca graf
 * @param mG graf w postaci macierzy sąsiedztwa
 * @param lG graf w postaci listy sąsiedztwa
*/
void uiprintGraph(MatrixGraph& mG, ListGraph& lG);

/**
 * @brief Funkcja przeprowadzająca testy
*/
void testGraph();