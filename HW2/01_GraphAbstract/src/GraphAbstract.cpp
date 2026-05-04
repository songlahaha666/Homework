#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct Edge {
    int u, v;
};

class Graph {
private:
    int n;
    int e;
    vector<int>* adj;

    bool isValidVertex(int v) const {
        return v >= 0 && v < n;
    }

    bool removeNeighbor(int u, int v) {
        auto& neighbors = adj[u];
        auto it = find(neighbors.begin(), neighbors.end(), v);
        if (it == neighbors.end()) {
            return false;
        }
        neighbors.erase(it);
        return true;
    }

public:
    Graph(int nodes) : n(nodes), e(0) {
        adj = new vector<int>[n];
    }

    virtual ~Graph() {
        delete[] adj;
    }

    virtual bool IsEmpty() const {
        return n == 0;
    }

    virtual int NumberOfVertices() const {
        return n;
    }

    virtual int NumberOfEdges() const {
        return e;
    }

    virtual int Degree(int u) const {
        if (!isValidVertex(u)) {
            return 0;
        }
        return static_cast<int>(adj[u].size());
    }

    virtual bool ExistsEdge(int u, int v) const {
        if (!isValidVertex(u) || !isValidVertex(v)) {
            return false;
        }
        return find(adj[u].begin(), adj[u].end(), v) != adj[u].end();
    }

    virtual void InsertVertex(int v) {
        (void)v;
        vector<int>* newAdj = new vector<int>[n + 1];
        for (int i = 0; i < n; ++i) {
            newAdj[i] = adj[i];
        }
        delete[] adj;
        adj = newAdj;
        ++n;
    }

    virtual void InsertEdge(int u, int v) {
        if (!isValidVertex(u) || !isValidVertex(v) || ExistsEdge(u, v)) {
            return;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++e;
    }

    virtual void DeleteVertex(int v) {
        if (!isValidVertex(v)) {
            return;
        }

        vector<int>* newAdj = new vector<int>[n - 1];
        for (int i = 0, newIndex = 0; i < n; ++i) {
            if (i == v) {
                continue;
            }

            for (int neighbor : adj[i]) {
                if (neighbor == v) {
                    continue;
                }

                if (neighbor > v) {
                    newAdj[newIndex].push_back(neighbor - 1);
                } else {
                    newAdj[newIndex].push_back(neighbor);
                }
            }

            ++newIndex;
        }

        delete[] adj;
        adj = newAdj;
        --n;

        int edgeCount = 0;
        for (int i = 0; i < n; ++i) {
            edgeCount += static_cast<int>(adj[i].size());
        }
        e = edgeCount / 2;
    }

    virtual void DeleteEdge(int u, int v) {
        if (!isValidVertex(u) || !isValidVertex(v) || !ExistsEdge(u, v)) {
            return;
        }

        bool removedFromU = removeNeighbor(u, v);
        bool removedFromV = removeNeighbor(v, u);
        if (removedFromU && removedFromV) {
            --e;
        }
    }
 
    void showMartix() {
        for (int k = 0; k < n; k++) {
            cout << k << " ";
        }
        cout << endl;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; j++) {
                if (ExistsEdge(i, j)) {
                    cout << "1 ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    void showArraylist() {
        vector<int>::iterator it;
        for (int i = 0; i < n; ++i) {
            cout << i << " : ";
            for (it = adj[i].begin(); it != adj[i].end(); ++it)
                cout << *it << " ";
            cout << endl;
        }
    }
};

int main() {
    Graph g(10);

    g.InsertEdge(0, 1);
    g.InsertEdge(1, 2);
    g.InsertEdge(1, 3);
    g.InsertEdge(2, 4);
    g.InsertEdge(4, 3);
    g.InsertEdge(3, 5);
    g.InsertEdge(5, 6);
    g.InsertEdge(5, 7);
    g.InsertEdge(6, 7);
    g.InsertEdge(7, 8);
    g.InsertEdge(7, 9);

    cout << "IsEmpty: " << g.IsEmpty() << endl;
    cout << "NumberOfVertices: " << g.NumberOfVertices() << endl;
    cout << "NumberOfEdges: " << g.NumberOfEdges() << endl;
    cout << "Degree(7): " << g.Degree(7) << endl;
    cout << "ExistsEdge(5, 7): " << g.ExistsEdge(5, 7) << endl;

    g.showArraylist();
    g.showMartix();

    g.DeleteEdge(5, 7);
    g.DeleteVertex(9);

    cout << endl << "After DeleteEdge(5, 7) and DeleteVertex(9)" << endl;
    cout << "NumberOfVertices: " << g.NumberOfVertices() << endl;
    cout << "NumberOfEdges: " << g.NumberOfEdges() << endl;
    g.showArraylist();

    return 0;
}