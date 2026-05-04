#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;

struct Edge {
    int u;
    int v;
    int weight;
};

class TestDataGenerator {
private:

    int randomNumber(int minValue, int maxValue) {
        return rand() % (maxValue - minValue + 1) + minValue;
    }

public:

    TestDataGenerator() {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    // 生成 Weighted Undirected Graph
    vector<Edge> GenerateWeightedUndirectedGraph(
        int vertexCount,
        int edgeCount,
        int minWeight,
        int maxWeight
    ) {

        vector<Edge> edges;
        set<pair<int, int>> usedEdges;

        while (static_cast<int>(edges.size()) < edgeCount) {

            int u = randomNumber(0, vertexCount - 1);
            int v = randomNumber(0, vertexCount - 1);

            if (u == v) {
                continue;
            }

            int small = min(u, v);
            int large = max(u, v);

            if (usedEdges.count({small, large})) {
                continue;
            }

            usedEdges.insert({small, large});

            int weight = randomNumber(minWeight, maxWeight);

            edges.push_back({small, large, weight});
        }

        return edges;
    }
};

class DisjointSet {
private:

    vector<int> parent;
    vector<int> rank;

public:

    DisjointSet(int n) {

        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int Find(int x) {

        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }

        return parent[x];
    }

    bool Union(int x, int y) {

        int rootX = Find(x);
        int rootY = Find(y);

        if (rootX == rootY) {
            return false;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else {
            parent[rootY] = rootX;
            ++rank[rootX];
        }

        return true;
    }
};

class BenchmarkGraph {
private:

    int vertexCount;

    vector<Edge> edges;

    vector<vector<pair<int, int>>> adj;

    static bool compareEdge(const Edge& a, const Edge& b) {

        if (a.weight != b.weight) {
            return a.weight < b.weight;
        }

        int aSmall = min(a.u, a.v);
        int aLarge = max(a.u, a.v);

        int bSmall = min(b.u, b.v);
        int bLarge = max(b.u, b.v);

        if (aSmall != bSmall) {
            return aSmall < bSmall;
        }

        return aLarge < bLarge;
    }

public:

    BenchmarkGraph(
        int v,
        const vector<Edge>& inputEdges
    ) {

        vertexCount = v;
        edges = inputEdges;

        adj.resize(vertexCount);

        for (Edge edge : edges) {

            adj[edge.u].push_back(
                {edge.v, edge.weight}
            );

            adj[edge.v].push_back(
                {edge.u, edge.weight}
            );
        }

        for (int i = 0; i < vertexCount; ++i) {
            sort(adj[i].begin(), adj[i].end());
        }
    }

    // =========================
    // Homework 1
    // =========================

    void InsertEdgeBenchmark() {

        vector<vector<pair<int, int>>> tempAdj(vertexCount);

        for (Edge edge : edges) {

            tempAdj[edge.u].push_back(
                {edge.v, edge.weight}
            );

            tempAdj[edge.v].push_back(
                {edge.u, edge.weight}
            );
        }
    }

    bool ExistsEdgeBenchmark() {

        if (edges.empty()) {
            return false;
        }

        Edge target = edges[0];

        for (auto neighbor : adj[target.u]) {

            if (neighbor.first == target.v) {
                return true;
            }
        }

        return false;
    }

    // =========================
    // Homework 2
    // =========================

    void DFS() {

        vector<bool> visited(vertexCount, false);

        stack<int> s;

        s.push(0);

        while (!s.empty()) {

            int u = s.top();
            s.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            for (auto it = adj[u].rbegin();
                 it != adj[u].rend();
                 ++it) {

                int v = it->first;

                if (!visited[v]) {
                    s.push(v);
                }
            }
        }
    }

    void BFS() {

        vector<bool> visited(vertexCount, false);

        queue<int> q;

        visited[0] = true;
        q.push(0);

        while (!q.empty()) {

            int u = q.front();
            q.pop();

            for (auto neighbor : adj[u]) {

                int v = neighbor.first;

                if (!visited[v]) {

                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    void ConnectedComponents() {

        vector<bool> visited(vertexCount, false);

        for (int i = 0; i < vertexCount; ++i) {

            if (visited[i]) {
                continue;
            }

            queue<int> q;

            visited[i] = true;
            q.push(i);

            while (!q.empty()) {

                int u = q.front();
                q.pop();

                for (auto neighbor : adj[u]) {

                    int v = neighbor.first;

                    if (!visited[v]) {

                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    // =========================
    // Homework 3
    // =========================

    int Kruskal() {

        vector<Edge> sortedEdges = edges;

        sort(
            sortedEdges.begin(),
            sortedEdges.end(),
            compareEdge
        );

        DisjointSet ds(vertexCount);

        int totalWeight = 0;
        int selectedEdges = 0;

        for (Edge edge : sortedEdges) {

            if (ds.Union(edge.u, edge.v)) {

                totalWeight += edge.weight;

                selectedEdges++;

                if (selectedEdges == vertexCount - 1) {
                    break;
                }
            }
        }

        return totalWeight;
    }

    int Prim() {

        vector<bool> visited(vertexCount, false);

        auto cmp = [](const Edge& a, const Edge& b) {

            if (a.weight != b.weight) {
                return a.weight > b.weight;
            }

            return a.v > b.v;
        };

        priority_queue<
            Edge,
            vector<Edge>,
            decltype(cmp)
        > pq(cmp);

        visited[0] = true;

        for (auto neighbor : adj[0]) {

            pq.push(
                {0, neighbor.first, neighbor.second}
            );
        }

        int totalWeight = 0;
        int selectedEdges = 0;

        while (!pq.empty() &&
               selectedEdges < vertexCount - 1) {

            Edge edge = pq.top();
            pq.pop();

            if (visited[edge.v]) {
                continue;
            }

            visited[edge.v] = true;

            totalWeight += edge.weight;

            selectedEdges++;

            for (auto neighbor : adj[edge.v]) {

                if (!visited[neighbor.first]) {

                    pq.push(
                        {
                            edge.v,
                            neighbor.first,
                            neighbor.second
                        }
                    );
                }
            }
        }

        return totalWeight;
    }

    // =========================
    // Homework 4
    // =========================

    void Dijkstra() {

        vector<int> dist(vertexCount, INF);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[0] = 0;

        pq.push({0, 0});

        while (!pq.empty()) {

            int currentDistance = pq.top().first;
            int u = pq.top().second;

            pq.pop();

            for (auto neighbor : adj[u]) {

                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[v] > currentDistance + weight) {

                    dist[v] = currentDistance + weight;

                    pq.push(
                        {dist[v], v}
                    );
                }
            }
        }
    }

    void BellmanFord() {

        vector<int> dist(vertexCount, INF);

        dist[0] = 0;

        for (int i = 1;
             i <= vertexCount - 1;
             ++i) {

            for (Edge edge : edges) {

                if (dist[edge.u] < INF &&
                    dist[edge.v] >
                    dist[edge.u] + edge.weight) {

                    dist[edge.v] =
                        dist[edge.u] + edge.weight;
                }
            }
        }
    }

    // =========================
    // Homework 5
    // =========================

    void TopologicalSort() {

        cout << "Not suitable for large-scale benchmark."
             << endl;
    }

    void CriticalPath() {

        cout << "Not suitable for large-scale benchmark."
             << endl;
    }

    void FloydWarshall() {

        cout << "Not suitable for large-scale benchmark."
             << endl;
    }

    void BiconnectedComponents() {

        cout << "Not suitable for large-scale benchmark."
             << endl;
    }
};

void printTime(
    const string& algorithmName,
    chrono::duration<double> duration
) {

    cout << algorithmName
         << " Time: "
         << duration.count()
         << " seconds"
         << endl;
}

void runBenchmark(int edgeCount) {

    int vertexCount;

    if (edgeCount == 10000) {
        vertexCount = 1000;
    }
    else if (edgeCount == 100000) {
        vertexCount = 10000;
    }
    else {
        vertexCount = 100000;
    }

    cout << endl;
    cout << "======================================" << endl;
    cout << "Benchmark Start" << endl;
    cout << "======================================" << endl;

    cout << "Vertex Count: "
         << vertexCount
         << endl;

    cout << "Requested Edges: "
         << edgeCount
         << endl;

    TestDataGenerator generator;

    cout << endl;
    cout << "Generating test data..."
         << endl;

    auto generateStart =
        chrono::high_resolution_clock::now();

    vector<Edge> edges =
        generator.GenerateWeightedUndirectedGraph(
            vertexCount,
            edgeCount,
            1,
            100
        );

    auto generateEnd =
        chrono::high_resolution_clock::now();

    chrono::duration<double> generateTime =
        generateEnd - generateStart;

    // 驗證實際生成的 edge 數量
    // 用於確認測資規模是否正確
    // 也可作為報告中佐證資料數量的依據
    cout << "Generated Edges: "
         << edges.size()
         << endl;

    cout << "Generate Time: "
         << generateTime.count()
         << " seconds"
         << endl;

    cout << endl;
    cout << "Building graph..."
         << endl;

    auto buildStart =
        chrono::high_resolution_clock::now();

    BenchmarkGraph graph(
        vertexCount,
        edges
    );

    auto buildEnd =
        chrono::high_resolution_clock::now();

    chrono::duration<double> buildTime =
        buildEnd - buildStart;

    cout << "Build Graph Time: "
         << buildTime.count()
         << " seconds"
         << endl;

    cout << endl;

    // =========================
    // Homework 1
    // =========================

    cout << "======================================" << endl;
    cout << "Homework 1 - GraphAbstract" << endl;
    cout << "======================================" << endl;

    auto start =
        chrono::high_resolution_clock::now();

    graph.InsertEdgeBenchmark();

    auto end =
        chrono::high_resolution_clock::now();

    printTime(
        "InsertEdge",
        end - start
    );

    start =
        chrono::high_resolution_clock::now();

    graph.ExistsEdgeBenchmark();

    end =
        chrono::high_resolution_clock::now();

    printTime(
        "ExistsEdge",
        end - start
    );

    cout << endl;

    // =========================
    // Homework 2
    // =========================

    cout << "======================================" << endl;
    cout << "Homework 2 - GraphOperations" << endl;
    cout << "======================================" << endl;

    start =
        chrono::high_resolution_clock::now();

    graph.DFS();

    end =
        chrono::high_resolution_clock::now();

    printTime(
        "DFS",
        end - start
    );

    start =
        chrono::high_resolution_clock::now();

    graph.BFS();

    end =
        chrono::high_resolution_clock::now();

    printTime(
        "BFS",
        end - start
    );

    start =
        chrono::high_resolution_clock::now();

    graph.ConnectedComponents();

    end =
        chrono::high_resolution_clock::now();

    printTime(
        "Connected Components",
        end - start
    );

    cout << "Biconnected Components:" << endl;

    graph.BiconnectedComponents();

    cout << endl;

    // =========================
    // Homework 3
    // =========================

    cout << "======================================" << endl;
    cout << "Homework 3 - MinimumSpanningTree" << endl;
    cout << "======================================" << endl;

    start =
        chrono::high_resolution_clock::now();

    int kruskalWeight =
        graph.Kruskal();

    end =
        chrono::high_resolution_clock::now();

    cout << "Kruskal Total Weight: "
         << kruskalWeight
         << endl;

    printTime(
        "Kruskal",
        end - start
    );

    start =
        chrono::high_resolution_clock::now();

    int primWeight =
        graph.Prim();

    end =
        chrono::high_resolution_clock::now();

    cout << "Prim Total Weight: "
         << primWeight
         << endl;

    printTime(
        "Prim",
        end - start
    );

    cout << endl;

    // =========================
    // Homework 4
    // =========================

    cout << "======================================" << endl;
    cout << "Homework 4 - ShortestPath" << endl;
    cout << "======================================" << endl;

    start =
        chrono::high_resolution_clock::now();

    graph.Dijkstra();

    end =
        chrono::high_resolution_clock::now();

    printTime(
        "Dijkstra",
        end - start
    );

    start =
        chrono::high_resolution_clock::now();

    graph.BellmanFord();

    end =
        chrono::high_resolution_clock::now();

    printTime(
        "Bellman-Ford",
        end - start
    );

    cout << "Floyd-Warshall:" << endl;

    graph.FloydWarshall();

    cout << endl;

    // =========================
    // Homework 5
    // =========================

    cout << "======================================" << endl;
    cout << "Homework 5 - ActivityNetwork" << endl;
    cout << "======================================" << endl;

    cout << "Topological Sort:" << endl;

    graph.TopologicalSort();

    cout << endl;

    cout << "Critical Path:" << endl;

    graph.CriticalPath();

    cout << endl;

    cout << "Benchmark Finished"
         << endl;
}

int main() {

    int choice;
    int edgeCount;

    cout << "Select Benchmark Size" << endl;
    cout << "1. 10,000 edges" << endl;
    cout << "2. 100,000 edges" << endl;
    cout << "3. 1,000,000 edges" << endl;
    cout << "Enter choice: ";

    cin >> choice;

    if (choice == 1) {
        edgeCount = 10000;
    }
    else if (choice == 2) {
        edgeCount = 100000;
    }
    else if (choice == 3) {
        edgeCount = 1000000;
    }
    else {

        cout << "Invalid choice."
             << endl;

        return 0;
    }

    runBenchmark(edgeCount);

    return 0;
}