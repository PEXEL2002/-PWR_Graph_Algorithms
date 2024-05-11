#pragma once  
#include <vector>
class Graph {
public:
    virtual ~Graph() {}
    virtual void addEdge(int v, int w, int weight) = 0;
    virtual void print() = 0;
    virtual std::vector<int> dijkstraAlgorithmToAll(int startVertex) = 0;
    virtual int dijkstraAlgorithmToPoint(int startVertex, int endVertex) = 0;
};