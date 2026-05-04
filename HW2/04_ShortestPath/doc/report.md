# Shortest Path

## 1.解題說明

Shortest Path 是用來找出圖中兩個頂點之間最短距離的問題。

本題實作三種最短路徑演算法：

- Dijkstra：適用於非負權重的單源最短路徑
- Bellman-Ford：可以處理負權重的單源最短路徑
- Floyd-Warshall：可以計算所有點對之間的最短路徑

本題使用加權有向圖作為主要測試資料，並分別針對不同演算法設計適合的測試圖。

---

## 2.演算法設計與實作

### Edge 結構

```cpp
struct Edge {
    int u;
    int v;
    int weight;
};
```

### Graph Representation（Adjacency List）

```cpp
vector<pair<int, int>>* adj;
vector<Edge> edges;
```

### InsertDirectedEdge

```cpp
void InsertDirectedEdge(int u, int v, int weight) {
    if (!isValidVertex(u) || !isValidVertex(v)) {
        return;
    }

    adj[u].push_back({v, weight});
    edges.push_back({u, v, weight});
    ++e;

    sort(adj[u].begin(), adj[u].end());
}
```

### InsertUndirectedEdge

```cpp
void InsertUndirectedEdge(int u, int v, int weight) {
    if (!isValidVertex(u) || !isValidVertex(v)) {
        return;
    }

    InsertDirectedEdge(u, v, weight);
    InsertDirectedEdge(v, u, weight);
}
```

### Dijkstra

```cpp
void Dijkstra(int source) {
    if (!isValidVertex(source)) {
        return;
    }

    vector<int> dist(n, INF);
    vector<bool> visited(n, false);

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

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && dist[v] > currentDistance + weight) {
                dist[v] = currentDistance + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Dijkstra Algorithm:" << endl;
    showDistance(dist, source);
}
```

### Bellman-Ford

```cpp
void BellmanFord(int source) {
    if (!isValidVertex(source)) {
        return;
    }

    vector<int> dist(n, INF);
    dist[source] = 0;

    for (int i = 1; i <= n - 1; ++i) {
        for (Edge edge : edges) {
            if (dist[edge.u] < INF &&
                dist[edge.v] > dist[edge.u] + edge.weight) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

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
```

### Floyd-Warshall

```cpp
void FloydWarshall() {
    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    for (int u = 0; u < n; ++u) {
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            dist[u][v] = min(dist[u][v], weight);
        }
    }

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
```

## 3.效能分析

### 時間複雜度

InsertDirectedEdge：O(deg(u) log deg(u))

InsertUndirectedEdge：O(deg(u) log deg(u) + deg(v) log deg(v))

Dijkstra：O((n + e) log n)

Bellman-Ford：O(n × e)

Floyd-Warshall：O(n³)

showArraylist：O(n + e)

showDistance：O(n)

### 空間複雜度

Adjacency List：O(n + e)

Edge List：O(e)

Dijkstra Distance Array：O(n)

Dijkstra Priority Queue：O(e)

Bellman-Ford Distance Array：O(n)

Floyd-Warshall Matrix：O(n²)

本題主要使用 adjacency list 儲存圖，可以有效節省空間。
Floyd-Warshall 則使用 matrix 計算所有點對最短路徑，因此空間需求較高。

## 4.測試

```cpp
int main() {
    Graph g(5);

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

    g.BellmanFord(0);

    cout << endl;

    g.FloydWarshall();

    cout << endl;

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

    positiveGraph.Dijkstra(0);

    return 0;
}
```

### 輸出

```
Adjacency List:
0 : (1, 6) (2, 7) 
1 : (2, 8) (3, 5) (4, -4) 
2 : (3, -3) (4, 9) 
3 : (1, -2) 
4 : (0, 2) (3, 7) 

Bellman-Ford Algorithm:
Source Vertex: 0
Distance from 0 to 0 : 0
Distance from 0 to 1 : 2
Distance from 0 to 2 : 7
Distance from 0 to 3 : 4
Distance from 0 to 4 : -2

Floyd-Warshall Algorithm:
All-Pairs Shortest Paths:
0 2 7 4 -2 
-2 0 5 2 -4 
-7 -5 0 -3 -9 
-4 -2 3 0 -6 
2 4 9 6 0 

Positive Weighted Graph:
0 : (1, 10) (3, 5) 
1 : (2, 1) (3, 2) 
2 : (4, 4) 
3 : (1, 3) (2, 9) (4, 2) 
4 : (0, 7) (2, 6) 

Dijkstra Algorithm:
Source Vertex: 0
Distance from 0 to 0 : 0
Distance from 0 to 1 : 8
Distance from 0 to 2 : 9
Distance from 0 to 3 : 5
Distance from 0 to 4 : 7
```

## 5.心得討論
這題一開始看起來只是最短路徑，但真的寫下去才發現三個演算法的差別滿大的。<br>
Dijkstra 寫起來比較像是一直找目前最近的點，搭配 priority queue 之後效率比較好，但是它不能處理負權重，所以測試時還要另外準備一張沒有負權重的圖。<br>
Bellman-Ford 的概念一開始比較繞，因為它是一直重複更新所有邊，寫起來感覺比較暴力，
但好處是可以處理負權重，還能檢查負權重 cycle。<br>
Floyd-Warshall 看起來反而最直覺，就是用三層迴圈一直比較有沒有經過中繼點更短，但也因為是三層迴圈，所以資料一大就會很恐怖。<br>
寫完這題之後比較能理解，不是所有最短路徑演算法都適合同一種情況，要看圖有沒有負權重、是要單一起點還是所有點對，再選適合的演算法。