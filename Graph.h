#pragma once  
class Graph {
public:
    virtual ~Graph() {}
    virtual void addEdge(int v, int w, int weight) = 0;
    virtual void print() = 0;
    virtual void dijkstraAlgorithmToAll(int startVertex, bool outputToFile, std::string outputToFileName) = 0;
    virtual void dijkstraAlgorithmToPoint(int startVertex, int endVertex, bool outputToFile, std::string outputToFileName) = 0;
};