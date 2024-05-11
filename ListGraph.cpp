#include "ListGraph.h"
#include <limits>
#include <queue>
#include <vector>
#include <set>

ListGraph::ListGraph(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    std::string line;
    _numVertices = 0;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::pair<int, int>> vertexVector;

        while (iss >> token) {
            int pos = token.find('(');
            int endPos = token.find(')');
            int vertex = std::stoi(token.substr(0, pos));
            int weight = std::stoi(token.substr(pos + 1, endPos - pos - 1));
            vertexVector.push_back({vertex, weight});
        }
        _adjacencyList.push_back(vertexVector);
        _numVertices++;
    }
    file.close();
}
ListGraph::~ListGraph(){}

void ListGraph::addEdge(int v, int w, int weight) {
    if (v >= _numVertices || w < 0) {
        throw std::out_of_range("Vertex index out of valid range");
    }
    _adjacencyList[v].push_back({w, weight});
}
void ListGraph::print() {
    std::cout << "List: " << std::endl;
    for (int i = 0; i < _numVertices; i++) {
        std::cout << i << ": ";
        for (const auto& edge : _adjacencyList[i]) {
            std::cout << edge.first << "(" << edge.second << ") ";
        }
        std::cout << std::endl;
    }
}
void ListGraph::dijkstraAlgorithmToAll(int startVertex) {
    std::vector<int> distances(_numVertices, std::numeric_limits<int>::max());
    std::vector<bool> visited(_numVertices, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distances[startVertex] = 0;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        int currentVertex = pq.top().second;
        pq.pop();

        if (visited[currentVertex]) continue;
        visited[currentVertex] = true;

        for (const auto& edge : _adjacencyList[currentVertex]) {
            int adjacent = edge.first;
            int weight = edge.second;
            if (distances[currentVertex] + weight < distances[adjacent]) {
                distances[adjacent] = distances[currentVertex] + weight;
                pq.push({distances[adjacent], adjacent});
            }
        }
    }
    std::cout << "Lista sąsiedztwa: " << std::endl;
    // Print distances
    for (int i = 0; i < _numVertices; i++) {
        if (distances[i] != std::numeric_limits<int>::max()) {
            std::cout << "Najkrótsza ścieżka od wierzchołka " << startVertex << " do wierzchołka " << i << " wynosi " << distances[i] << std::endl;
        } else {
            std::cout << "Brak połączenia między wierzchołkiem " << startVertex << " a " << i << std::endl;
        }
    }
}
void ListGraph::dijkstraAlgorithmToPoint(int startVertex, int endVertex) {
    std::vector<int> distances(_numVertices, std::numeric_limits<int>::max());
    std::vector<bool> visited(_numVertices, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distances[startVertex] = 0;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        int currentVertex = pq.top().second;
        pq.pop();

        // if the current vertex is the end vertex, print the distance and return
        if (currentVertex == endVertex) {
            std::cout << "Lista sąsiedztwa: " << std::endl;
            std::cout << "Najkrótsza ścieżka od wierzchołka " << startVertex << " do wierzchołka " << endVertex << " wynosi " << distances[currentVertex] << std::endl;
            return; // end the function
        }

        if (visited[currentVertex]) continue;
        visited[currentVertex] = true;

        for (const auto& edge : _adjacencyList[currentVertex]) {
            int adjacent = edge.first;
            int weight = edge.second;
            if (distances[currentVertex] + weight < distances[adjacent]) {
                distances[adjacent] = distances[currentVertex] + weight;
                if (!visited[adjacent]) { // Dodajemy do kolejki tylko jeśli wierzchołek nie został odwiedzony
                    pq.push({distances[adjacent], adjacent});
                }
            }
        }
    }
    std::cout << "Lista sąsiedztwa: " << std::endl;
    //if the function reaches this point, it means that there is no path from startVertex to endVertex
    std::cout << "Ścieżka od wierzchołka " << startVertex << " do wierzchołka " << endVertex << " nie istnieje." << std::endl;
}