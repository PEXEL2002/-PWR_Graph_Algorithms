#include "MatrixGraph.h"
#include "ListGraph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
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
int generateVertices(int maxVertices){
    return rand() % maxVertices;
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
    std::vector<int> sizeV = {10, 50, 100, 500, 1000};
    std::vector<int> density = {25, 50, 75, 100};
    long long int timeMatrix = 0, timeMatrix1 = 0;
    long long int timeList = 0, timeList1 = 0;
    int startVertex = 0;
    int endVertex = 0;
    
    std::ofstream saveFile("data.csv");
    if (!saveFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku data.csv\n";
        return;
    }
    saveFile << "Operation;Type;Vertices;Density;Time\n";

    for (int vertices : sizeV) {
        for (int dens : density) {
            timeMatrix = 0;
            timeList = 0;
            for (int i = 0; i < 100; i++) {
                generateGraphData(vertices, dens, "test");
                startVertex = generateVertices(vertices);
                endVertex = generateVertices(vertices);
                MatrixGraph* mG = new MatrixGraph("matrix_test.txt");
                ListGraph* lG = new ListGraph("list_test.txt");

                auto start1 = std::chrono::high_resolution_clock::now();
                mG->dijkstraAlgorithmToAll(startVertex);
                auto end1 = std::chrono::high_resolution_clock::now();
                timeMatrix += std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count();

                auto start2 = std::chrono::high_resolution_clock::now();
                lG->dijkstraAlgorithmToAll(startVertex);
                auto end2 = std::chrono::high_resolution_clock::now();
                timeList += std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
                
                startVertex = generateVertices(vertices);
                endVertex = generateVertices(vertices);

                auto start3 = std::chrono::high_resolution_clock::now();
                mG->dijkstraAlgorithmToPoint(startVertex, endVertex);
                auto end3 = std::chrono::high_resolution_clock::now();
                timeMatrix1 += std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count();

                auto start4 = std::chrono::high_resolution_clock::now();
                lG->dijkstraAlgorithmToPoint(startVertex, endVertex);
                auto end4 = std::chrono::high_resolution_clock::now();
                timeList1 += std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - start4).count();
                delete lG;
                delete mG;
            }
            saveFile << "dijkstraAlgorithmToAll;Matrix;" << vertices << ";" << dens << ";" << timeMatrix / 100 << "\n";
            saveFile << "dijkstraAlgorithmToAll;List;" << vertices << ";" << dens<< ";" << timeList / 100 << "\n";
            saveFile << "dijkstraAlgorithmToPoint;Matrix;" << vertices << ";" << dens << ";" << timeMatrix1/100 << "\n";
            saveFile << "dijkstraAlgorithmToPoint;List;" << vertices << ";" << dens << ";" << timeList1/100 << "\n";
        }
    }
    saveFile.close();
}