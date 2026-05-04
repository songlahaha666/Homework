#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;

// Edge 結構
// u：起點
// v：終點
// weight：邊的權重
struct Edge {
    int u;
    int v;
    int weight;
};

// 加權圖
// Graph Representation：Adjacency List
// 這題用來實作最短路徑演算法
class Graph {
private:
    int n; // 頂點數
    int e; // 邊數

    // adjacency list
    // pair<相鄰頂點, 邊的權重>
    vector<pair<int, int>>* adj;

    // edge list
    // Bellman-Ford 需要逐一檢查所有邊
    vector<Edge> edges;

    bool isValidVertex(int v) const {
        return v >= 0 && v < n;
    }

public:
    Graph(int nodes) : n(nodes), e(0) {
        adj = new vector<pair<int, int>>[n];
    }

    ~Graph() {
        delete[] adj;
    }

    bool IsEmpty() const {
        return n == 0;
    }

    int NumberOfVertices() const {
        return n;
    }

    int NumberOfEdges() const {
        return e;
    }

    // 插入有向加權邊
    // Shortest Path 常用有向圖表示路徑方向
    void InsertDirectedEdge(int u, int v, int weight) {
        if (!isValidVertex(u) || !isValidVertex(v)) {
            return;
        }

        adj[u].push_back({v, weight});
        edges.push_back({u, v, weight});
        ++e;

        // 讓相鄰頂點依照編號由小到大排列
        // 方便輸出，也符合數字小優先
        sort(adj[u].begin(), adj[u].end());
    }

    // 插入無向加權邊
    // 若測試資料需要無向圖，可以使用此函式
    void InsertUndirectedEdge(int u, int v, int weight) {
        if (!isValidVertex(u) || !isValidVertex(v)) {
            return;
        }

        InsertDirectedEdge(u, v, weight);
        InsertDirectedEdge(v, u, weight);
    }

    // 顯示 adjacency list
    void showArraylist() const {
        for (int i = 0; i < n; ++i) {
            cout << i << " : ";

            for (auto neighbor : adj[i]) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }

            cout << endl;
        }
    }

    // 顯示從 source 到每個頂點的最短距離
    void showDistance(const vector<int>& dist, int source) const {
        cout << "Source Vertex: " << source << endl;

        for (int i = 0; i < n; ++i) {
            cout << "Distance from " << source << " to " << i << " : ";

            if (dist[i] >= INF) {
                cout << "INF";
            } else {
                cout << dist[i];
            }

            cout << endl;
        }
    }

    // Dijkstra Algorithm
    // 適用情況：
    // 1. 單一起點到所有頂點的最短路徑
    // 2. 邊的權重不可為負數
    //
    // 注意：
    // Dijkstra 不能處理負權重邊，因為它每次會貪婪地選目前距離最小的頂點
    void Dijkstra(int source) {
        if (!isValidVertex(source)) {
            return;
        }

        vector<int> dist(n, INF);
        vector<bool> visited(n, false);

        // priority_queue 預設是 max heap
        // 這裡使用 greater 讓它變成 min heap
        // pair<目前距離, 頂點編號>
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            // 檢查 u 的所有相鄰頂點
            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // Relaxation
                // 如果經過 u 到 v 的距離比較短，就更新
                if (!visited[v] && dist[v] > currentDistance + weight) {
                    dist[v] = currentDistance + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Dijkstra Algorithm:" << endl;
        showDistance(dist, source);
    }

    // Bellman-Ford Algorithm
    // 適用情況：
    // 1. 單一起點到所有頂點的最短路徑
    // 2. 可以處理負權重邊
    //
    // 注意：
    // Bellman-Ford 可以處理負權重，但不能有負權重 cycle
    void BellmanFord(int source) {
        if (!isValidVertex(source)) {
            return;
        }

        vector<int> dist(n, INF);
        dist[source] = 0;

        // 最短路徑最多只會經過 n - 1 條邊
        // 所以需要進行 n - 1 輪 relaxation
        for (int i = 1; i <= n - 1; ++i) {
            for (Edge edge : edges) {
                if (dist[edge.u] < INF &&
                    dist[edge.v] > dist[edge.u] + edge.weight) {
                    dist[edge.v] = dist[edge.u] + edge.weight;
                }
            }
        }

        // 再檢查一次所有邊
        // 如果還能更新，代表圖中存在負權重 cycle
        bool hasNegativeCycle = false;

        for (Edge edge : edges) {
            if (dist[edge.u] < INF &&
                dist[edge.v] > dist[edge.u] + edge.weight) {
                hasNegativeCycle = true;
                break;
            }
        }

        cout << "Bellman-Ford Algorithm:" << endl;

        if (hasNegativeCycle) {
            cout << "Negative weight cycle detected." << endl;
            return;
        }

        showDistance(dist, source);
    }

    // Floyd-Warshall Algorithm
    // 適用情況：
    // 1. All-Pairs Shortest Paths，全點對最短路徑
    // 2. 可以處理負權重邊
    //
    // 注意：
    // Floyd-Warshall 使用 adjacency matrix 概念
    // 時間複雜度為 O(V^3)，空間複雜度為 O(V^2)
    // 適合小圖，不適合千萬筆資料
    void FloydWarshall() {
        vector<vector<int>> dist(n, vector<int>(n, INF));

        // 自己到自己的距離為 0
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }

        // 將 adjacency list 的邊放入 matrix
        for (int u = 0; u < n; ++u) {
            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                dist[u][v] = min(dist[u][v], weight);
            }
        }

        // k 代表中繼點
        // 檢查 i 是否能透過 k 到 j 得到更短路徑
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] < INF && dist[k][j] < INF &&
                        dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        cout << "Floyd-Warshall Algorithm:" << endl;
        cout << "All-Pairs Shortest Paths:" << endl;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] >= INF) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    // 建立 5 個頂點的加權有向圖
    // 頂點編號從 0 開始，到 4 結束
    Graph g(5);

    // 建立測試圖
    // InsertDirectedEdge(u, v, weight)
    //
    // 此測資包含負權重邊，但沒有負權重 cycle
    // 因此：
    // Dijkstra 不適合用來驗證此測資
    // Bellman-Ford 可以處理
    // Floyd-Warshall 也可以處理
    g.InsertDirectedEdge(0, 1, 6);
    g.InsertDirectedEdge(0, 2, 7);
    g.InsertDirectedEdge(1, 2, 8);
    g.InsertDirectedEdge(1, 3, 5);
    g.InsertDirectedEdge(1, 4, -4);
    g.InsertDirectedEdge(2, 3, -3);
    g.InsertDirectedEdge(2, 4, 9);
    g.InsertDirectedEdge(3, 1, -2);
    g.InsertDirectedEdge(4, 0, 2);
    g.InsertDirectedEdge(4, 3, 7);

    cout << "Adjacency List:" << endl;
    g.showArraylist();

    cout << endl;

    // Bellman-Ford 可以處理負權重邊
    g.BellmanFord(0);

    cout << endl;

    // Floyd-Warshall 使用 adjacency matrix 概念
    // 適合小圖，不適合千萬筆資料
    g.FloydWarshall();

    cout << endl;

    // Dijkstra 不能處理負權重邊
    // 所以下面另外建立一張沒有負權重的圖來測試 Dijkstra
    Graph positiveGraph(5);

    positiveGraph.InsertDirectedEdge(0, 1, 10);
    positiveGraph.InsertDirectedEdge(0, 3, 5);
    positiveGraph.InsertDirectedEdge(1, 2, 1);
    positiveGraph.InsertDirectedEdge(1, 3, 2);
    positiveGraph.InsertDirectedEdge(2, 4, 4);
    positiveGraph.InsertDirectedEdge(3, 1, 3);
    positiveGraph.InsertDirectedEdge(3, 2, 9);
    positiveGraph.InsertDirectedEdge(3, 4, 2);
    positiveGraph.InsertDirectedEdge(4, 0, 7);
    positiveGraph.InsertDirectedEdge(4, 2, 6);

    cout << "Positive Weighted Graph:" << endl;
    positiveGraph.showArraylist();

    cout << endl;

    // Dijkstra 用非負權重測資
    positiveGraph.Dijkstra(0);

    return 0;
}