#include "MatrixGraph.h"
#include "ListGraph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <set>
#include <utility>
#include <chrono>

void generateGraphData(int vertices, int density, std::string fileName = "") {
    std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices, 0));
    std::vector<std::vector<std::pair<int, int>>> list(vertices);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDis(1, 100);
    
    int maxEdges = vertices * (vertices - 1) / 2;
    int numEdges = static_cast<int>(maxEdges * (density / 100.0));

    std::string matrixFileName;
    std::string listFileName;
    if (fileName == "") {
        matrixFileName = "matrix_" + std::to_string(vertices) + "_" + std::to_string(density) + ".txt";
        listFileName = "list_" + std::to_string(vertices) + "_" + std::to_string(density) + ".txt";
    } else {
        matrixFileName = "matrix_" + fileName + ".txt";
        listFileName = "list_" + fileName + ".txt";
    }

    std::set<std::pair<int, int>> edges;
    while (edges.size() < numEdges) {
        int i = gen() % vertices;
        int j = gen() % vertices;
        if (i != j) {
            if (i > j) std::swap(i, j);
            edges.insert({i, j});
        }
    }

    // Dodawanie krawędzi do macierzy i listy sąsiedztwa
    for (const auto& edge : edges) {
        int weight = weightDis(gen);
        matrix[edge.first][edge.second] = weight;
        matrix[edge.second][edge.first] = weight;
        list[edge.first].push_back({edge.second, weight});
        list[edge.second].push_back({edge.first, weight});
    }
    // Zapisywanie do pliku - macierz sąsiedztwa
    std::ofstream matrixFile(matrixFileName);
    if (!matrixFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << matrixFileName << std::endl;
        return;
    }
    for (const auto& row : matrix) {
        for (int val : row) {
            matrixFile << val << " ";
        }
        matrixFile << "\n";
    }
    matrixFile.close();

    // Zapisywanie do pliku - lista sąsiedztwa
    std::ofstream listFile(listFileName);
    if (!listFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << listFileName << std::endl;
        return;
    }
    for (const auto& row : list) {
        for (const auto& pair : row) {
            listFile << pair.first << "(" << pair.second << ") ";
        }
        listFile << "\n";
    }
    listFile.close();
}

void uiDijkstraAll(MatrixGraph& mG, ListGraph& lG) {
    int startVertex;
    std::cout << "Podaj wierzchołek startowy: ";
    std::cin >> startVertex;
    auto start1 = std::chrono::high_resolution_clock::now();
    mG.dijkstraAlgorithmToAll(startVertex);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);

    auto start2 = std::chrono::high_resolution_clock::now();
    lG.dijkstraAlgorithmToAll(startVertex);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);

    std::cout << "Czas wykonania: \n";
    std::cout << "Macierz | " << duration1.count() << "ns\n";
    std::cout << "Lista   |" << duration2.count() << "ns\n";
}

void uiDijkstraToPoint(MatrixGraph& mG, ListGraph& lG) {
    int startVertex;
    int endVertex;
    std::cout << "Podaj wierzchołek startowy: ";
    std::cin >> startVertex;
    std::cout << "Podaj wierzchołek końcowy: ";
    std::cin >> endVertex;
    auto start1 = std::chrono::high_resolution_clock::now();
    mG.dijkstraAlgorithmToPoint(startVertex, endVertex);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);

    auto start2 = std::chrono::high_resolution_clock::now();
    lG.dijkstraAlgorithmToPoint(startVertex, endVertex);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);

    std::cout << "Czas wykonania: \n";
    std::cout << "Macierz | " << duration1.count() << "ns\n";
    std::cout << "Lista   |" << duration2.count() << "ns\n";
}

void uiprintGraph(MatrixGraph& mG, ListGraph& lG) {
    mG.print();
    lG.print();
}

void testGraph() {
    std::cout << "In progress\n";
}