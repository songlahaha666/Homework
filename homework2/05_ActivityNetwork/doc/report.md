# Activity Network

## 1.解題說明

Activity Network 是用來描述一組具有先後順序的活動，
常用於專案排程分析。

本題實作兩個重要演算法：

- Topological Sort：找出事件的執行順序
- Critical Path Method (CPM)：找出關鍵路徑與專案最短完成時間

圖的表示方式為加權有向圖（Directed Weighted Graph），
其中：

- 頂點代表事件
- 邊代表活動
- 權重代表活動所需時間

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

### InsertEdge

```cpp
void InsertEdge(int u, int v, int weight) {
    if (!isValidVertex(u) || !isValidVertex(v)) {
        return;
    }

    adj[u].push_back({v, weight});
    edges.push_back({u, v, weight});

    sort(adj[u].begin(), adj[u].end());
}
```

### Topological Sort（Kahn's Algorithm）

```cpp
bool TopologicalSort(vector<int>& topoOrder) {
    vector<int> indegree(n, 0);

    for (int u = 0; u < n; ++u) {
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            indegree[v]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topoOrder.push_back(u);

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            indegree[v]--;

            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return static_cast<int>(topoOrder.size()) == n;
}
```

### Critical Path

```cpp
void CriticalPath() {
    vector<int> topoOrder;

    if (!TopologicalSort(topoOrder)) {
        cout << "此圖不是 DAG，無法進行 Critical Path 分析。" << endl;
        return;
    }

    vector<int> ve(n, 0);

    for (int u : topoOrder) {
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            ve[v] = max(ve[v], ve[u] + weight);
        }
    }

    vector<int> vl(n, ve[topoOrder.back()]);

    for (int i = n - 1; i >= 0; --i) {
        int u = topoOrder[i];

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            vl[u] = min(vl[u], vl[v] - weight);
        }
    }

    for (Edge edge : edges) {
        int e = ve[edge.u];
        int l = vl[edge.v] - edge.weight;

        if (e == l) {
            cout << edge.u << " -> " << edge.v << endl;
        }
    }
}
```

## 3.效能分析

### 時間複雜度

InsertEdge：O(deg(u) log deg(u))

TopologicalSort：O(n + e)

CriticalPath：O(n + e)

showArraylist：O(n + e)

### 空間複雜度

Adjacency List：O(n + e)

Edge List：O(e)

Topological Order：O(n)

ve / vl 陣列：O(n)

## 4.測試

```cpp
int main() {
    Graph g(9);

    g.InsertEdge(0, 1, 6);
    g.InsertEdge(0, 2, 4);
    g.InsertEdge(0, 3, 5);

    g.InsertEdge(1, 4, 1);
    g.InsertEdge(2, 4, 1);
    g.InsertEdge(3, 5, 2);

    g.InsertEdge(4, 6, 9);
    g.InsertEdge(4, 7, 7);

    g.InsertEdge(5, 7, 4);

    g.InsertEdge(6, 8, 2);
    g.InsertEdge(7, 8, 4);

    g.showArraylist();

    g.CriticalPath();

    return 0;
}
```

### 輸出

```
==================================
Activity Network
==================================

鄰接串列 (Adjacency List)
0 : (1, 6) (2, 4) (3, 5) 
1 : (4, 1) 
2 : (4, 1) 
3 : (5, 2) 
4 : (6, 9) (7, 7) 
5 : (7, 4) 
6 : (8, 2) 
7 : (8, 4) 
8 : 

==============================
Activity Network 分析結果
==============================

拓樸排序 (Topological Order)
0 1 2 3 4 5 6 7 8 

最早事件時間 (ve)
Vertex 0 : 0
Vertex 1 : 6
Vertex 2 : 4
Vertex 3 : 5
Vertex 4 : 7
Vertex 5 : 7
Vertex 6 : 16
Vertex 7 : 14
Vertex 8 : 18

最晚事件時間 (vl)
Vertex 0 : 0
Vertex 1 : 6
Vertex 2 : 6
Vertex 3 : 8
Vertex 4 : 7
Vertex 5 : 10
Vertex 6 : 16
Vertex 7 : 14
Vertex 8 : 18

Critical Activities
0 -> 1 (Duration: 6)
1 -> 4 (Duration: 1)
4 -> 6 (Duration: 9)
4 -> 7 (Duration: 7)
6 -> 8 (Duration: 2)
7 -> 8 (Duration: 4)

專案最短完成時間：18
```

## 5.心得討論
這題一開始看起來很抽象，因為不像最短路徑或 MST 那樣直覺。<br>
Topological Sort 還算好理解，就是一直找入度為 0 的點，慢慢把順序排出來。<br>
Critical Path 就比較複雜，尤其是 ve 跟 vl 的計算，一開始真的會搞混，寫的時候也要一直 debug。<br>
但寫完之後會發現，其實就是在找哪些活動「不能延遲」，只要延遲整個專案就會變慢。
這題算是比較偏實務應用，寫完之後比較能理解專案排程怎麼運作，也知道為什麼有些工作會被稱為關鍵路徑。