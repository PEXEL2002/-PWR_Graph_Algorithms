class Graph {
public:
    virtual ~Graph() {}
    virtual void addEdge(int v, int w) = 0;
    virtual void print() const = 0;
    virtual void dijkstraAlgorithm(int startVertex) = 0;
};