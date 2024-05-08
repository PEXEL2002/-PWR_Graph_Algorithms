#pragma once  
class Graph {
public:
    virtual ~Graph() {}
    virtual void addEdge(int v, int w, int weight) = 0;
    virtual void print() = 0;
    virtual void dijkstraAlgorithm(int startVertex) = 0;
};