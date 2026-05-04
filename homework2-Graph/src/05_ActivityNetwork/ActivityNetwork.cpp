#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <windows.h>


using namespace std;

// Edge 結構
// u：起點事件
// v：終點事件
// weight：活動所需時間
struct Edge {
    int u;
    int v;
    int weight;
};

// Activity Network
// Graph Type：Weighted Directed Graph
// Graph Representation：Adjacency List
class Graph {
private:
    int n; // 頂點數

    // adjacency list
    // pair<相鄰頂點, 活動時間>
    vector<pair<int, int>>* adj;

    // edge list
    // Critical Path 需要逐一檢查所有邊
    vector<Edge> edges;

    bool isValidVertex(int v) const {
        return v >= 0 && v < n;
    }

public:
    Graph(int nodes) : n(nodes) {
        adj = new vector<pair<int, int>>[n];
    }

    ~Graph() {
        delete[] adj;
    }

    // 插入有向加權邊
    // u -> v
    // weight 代表活動所需時間
    void InsertEdge(int u, int v, int weight) {
        if (!isValidVertex(u) || !isValidVertex(v)) {
            return;
        }

        adj[u].push_back({v, weight});
        edges.push_back({u, v, weight});

        // 數字小優先
        sort(adj[u].begin(), adj[u].end());
    }

    // 顯示 adjacency list
    void showArraylist() const {
        cout << "鄰接串列 (Adjacency List)" << endl;

        for (int i = 0; i < n; ++i) {
            cout << i << " : ";

            for (auto neighbor : adj[i]) {
                cout << "("
                     << neighbor.first
                     << ", "
                     << neighbor.second
                     << ") ";
            }

            cout << endl;
        }
    }

    // Topological Sort
    // 使用 Kahn's Algorithm
    //
    // 適用於：
    // Directed Acyclic Graph (DAG)
    //
    // 功能：
    // 找出事件執行順序
    bool TopologicalSort(vector<int>& topoOrder) {
        vector<int> indegree(n, 0);

        // 計算每個頂點的入度
        for (int u = 0; u < n; ++u) {
            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                indegree[v]++;
            }
        }

        // queue 中放入度為 0 的頂點
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

            // 移除 u 指向的邊
            for (auto neighbor : adj[u]) {
                int v = neighbor.first;

                indegree[v]--;

                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // 如果拓樸排序後頂點數不足
        // 代表圖中存在 cycle
        return static_cast<int>(topoOrder.size()) == n;
    }

    // Critical Path Method (CPM)
    //
    // 功能：
    // 1. 計算最早事件時間 ve
    // 2. 計算最晚事件時間 vl
    // 3. 找出 Critical Activities
    void CriticalPath() {
        vector<int> topoOrder;

        cout << "==============================" << endl;
        cout << "Activity Network 分析結果" << endl;
        cout << "==============================" << endl;

        // 必須先進行拓樸排序
        if (!TopologicalSort(topoOrder)) {
            cout << "此圖不是 DAG，無法進行 Critical Path 分析。" << endl;
            return;
        }

        cout << endl;

        // 顯示拓樸排序結果
        cout << "拓樸排序 (Topological Order)" << endl;

        for (int v : topoOrder) {
            cout << v << " ";
        }

        cout << endl << endl;

        // ve：最早事件發生時間
        vector<int> ve(n, 0);

        // 依照拓樸順序計算 ve
        for (int u : topoOrder) {
            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                ve[v] = max(ve[v], ve[u] + weight);
            }
        }

        // vl：最晚事件發生時間
        vector<int> vl(n, ve[topoOrder.back()]);

        // 反向計算 vl
        for (int i = n - 1; i >= 0; --i) {
            int u = topoOrder[i];

            for (auto neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                vl[u] = min(vl[u], vl[v] - weight);
            }
        }

        // 顯示 ve
        cout << "最早事件時間 (ve)" << endl;

        for (int i = 0; i < n; ++i) {
            cout << "Vertex "
                 << i
                 << " : "
                 << ve[i]
                 << endl;
        }

        cout << endl;

        // 顯示 vl
        cout << "最晚事件時間 (vl)" << endl;

        for (int i = 0; i < n; ++i) {
            cout << "Vertex "
                 << i
                 << " : "
                 << vl[i]
                 << endl;
        }

        cout << endl;

        // 顯示 Critical Activities
        //
        // e = 活動最早開始時間
        // l = 活動最晚開始時間
        //
        // 若 e == l
        // 代表此活動為 Critical Activity
        cout << "Critical Activities" << endl;

        for (Edge edge : edges) {
            int e = ve[edge.u];
            int l = vl[edge.v] - edge.weight;

            if (e == l) {
                cout << edge.u
                     << " -> "
                     << edge.v
                     << " (Duration: "
                     << edge.weight
                     << ")"
                     << endl;
            }
        }

        cout << endl;

        // 專案完成總時間
        cout << "專案最短完成時間：" 
             << ve[topoOrder.back()]
             << endl;
    }
};


int main() {
    // 建立 Activity Network
    //
    // 頂點代表事件
    // 邊代表活動
    // weight 代表活動所需時間
    SetConsoleOutputCP(CP_UTF8);//把 console 輸出改成 UTF-8

    Graph g(9);

    // 建立測試圖
    //
    // InsertEdge(u, v, weight)
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

    // 顯示 adjacency list
    cout << "==================================" << endl;
    cout << "Activity Network" << endl;
    cout << "==================================" << endl;

    cout << endl;

    g.showArraylist();

    cout << endl;

    // 執行 Critical Path 分析
    g.CriticalPath();

    return 0;
}