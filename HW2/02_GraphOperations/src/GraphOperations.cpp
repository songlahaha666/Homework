#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int u, v;
};

class Graph {
private:
    int n;
    vector<int>* adj;
    bool* visited;
    int* dfn;
    int* low;
    int timeCounter;
    stack<Edge> s;

    bool isValidVertex(int v) const {
        return v >= 0 && v < n;
    }

    void DFS(int v) {
        visited[v] = true;
        cout << v << ' ';

        for (int w : adj[v]) {
            if (!visited[w]) {
                DFS(w);
            }
        }
    }

    void DFSCollect(int v, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);

        for (int w : adj[v]) {
            if (!visited[w]) {
                DFSCollect(w, component);
            }
        }
    }

public:
    Graph(int nodes) : n(nodes) {
        adj = new vector<int>[n];
        visited = new bool[n];
        dfn = new int[n];
        low = new int[n];
        timeCounter = 0;
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
            dfn[i] = 0;
            low[i] = 0;
        }
    }

    ~Graph() {
        delete[] adj;
        delete[] visited;
        delete[] dfn;
        delete[] low;
    }

    void InsertEdge(int u, int v) {
        if (!isValidVertex(u) || !isValidVertex(v)) {
            return;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS() {
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }
        DFS(0);
        cout << endl;
    }

    void DFSFrom(int v) {
        if (!isValidVertex(v)) {
            return;
        }

        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }
        DFS(v);
        cout << endl;
    }

    void BFS(int v) {
        if (!isValidVertex(v)) {
            return;
        }

        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }

        queue<int> q;
        visited[v] = true;
        q.push(v);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            cout << cur << ' ';

            for (int w : adj[cur]) {
                if (!visited[w]) {
                    visited[w] = true;
                    q.push(w);
                }
            }
        }
        cout << endl;
    }

    void ConnectedComponents() {
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }

        int componentId = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++componentId;
                vector<int> component;
                DFSCollect(i, component);

                cout << "Component " << componentId << ": ";
                for (int v : component) {
                    cout << v << ' ';
                }
                cout << endl;
            }
        }
    }

    void BiconnectedRec(int u, int parent) {
        dfn[u] = low[u] = ++timeCounter;

        for (int w : adj[u]) {
            if (w == parent) continue;

            if (dfn[w] == 0) {
                s.push({u, w});
                BiconnectedRec(w, u);
                low[u] = min(low[u], low[w]);

                if (low[w] >= dfn[u]) {
                    cout << "New Biconnected Component:" << endl;
                    Edge edge;
                    do {
                        edge = s.top(); s.pop();
                        cout << edge.u << " " << edge.v << endl;
                    } while (!(edge.u == u && edge.v == w) && !s.empty());
                }
            } else if (dfn[w] < dfn[u]) {
                s.push({u, w});
                low[u] = min(low[u], dfn[w]);
            }
        }
    }

    void Biconnected() {
        // reset dfn/low and stack
        for (int i = 0; i < n; ++i) {
            dfn[i] = 0;
            low[i] = 0;
        }
        while (!s.empty()) s.pop();
        timeCounter = 0;

        for (int i = 0; i < n; ++i) {
            if (dfn[i] == 0) {
                BiconnectedRec(i, -1);
                if (!s.empty()) {
                    cout << "New Biconnected Component:" << endl;
                    while (!s.empty()) {
                        Edge edge = s.top(); s.pop();
                        cout << edge.u << " " << edge.v << endl;
                    }
                }
            }
        }
    }

    void showArraylist() const {
        for (int i = 0; i < n; ++i) {
            cout << i << " : ";
            for (int w : adj[i]) {
                cout << w << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(12);

    g.InsertEdge(0, 1);
    g.InsertEdge(0, 2);
    g.InsertEdge(1, 3);
    g.InsertEdge(1, 4);
    g.InsertEdge(2, 5);
    g.InsertEdge(2, 6);
    g.InsertEdge(3, 7);
    g.InsertEdge(4, 8);
    g.InsertEdge(6, 9);
    g.InsertEdge(10, 11);

    cout << "Adjacency List:" << endl;
    g.showArraylist();

    cout << "DFS starting from vertex 0:" << endl;
    g.DFS();

    cout << "DFS starting from vertex 2:" << endl;
    g.DFSFrom(2);

    cout << "BFS starting from vertex 0:" << endl;
    g.BFS(0);

    cout << "BFS starting from vertex 2:" << endl;
    g.BFS(2);

    cout << "Connected Components:" << endl;
    g.ConnectedComponents();

    cout << "Biconnected Components (edge-based):" << endl;
    g.Biconnected();

    return 0;
}