#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <set>
#include <utility>

void generateGraphData(int vertices, int density) {
    std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices, 0));
    std::vector<std::vector<std::pair<int, int>>> list(vertices);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDis(1, 100);  // Zakres wag od 1 do 100
    
    int maxEdges = vertices * (vertices - 1) / 2;
    int numEdges = static_cast<int>(maxEdges * (density / 100.0));  // Poprawka na prawidłowe obliczenie procenta
    std::string matrixFileName = "matrix_" + std::to_string(vertices) + "_" + std::to_string(density) + ".txt";
    std::string listFileName = "list_" + std::to_string(vertices) + "_" + std::to_string(density) + ".txt";

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
