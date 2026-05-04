#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Edge 結構
// u：邊的起點
// v：邊的終點
// weight：邊的權重
struct Edge {
    int u;
    int v;
    int weight;
};

// Disjoint Set，也稱為 Union-Find
// 用於 Kruskal 演算法
// 功能是判斷兩個頂點是否已經在同一個集合中，避免 MST 產生 cycle
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        // 一開始每個頂點都是自己的 parent
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 尋找 x 所屬集合的代表節點
    int Find(int x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]); // 路徑壓縮，加快查找速度
        }
        return parent[x];
    }

    // 合併兩個集合
    // 如果 x 和 y 原本就在同一集合，代表加入這條邊會形成 cycle
    bool Union(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);

        if (rootX == rootY) {
            return false;
        }

        // 依 rank 合併，讓樹高度盡量變小
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            ++rank[rootX];
        }

        return true;
    }
};

// 加權無向圖
// Graph Representation：Adjacency List
class Graph {
private:
    int n; // 頂點數
    int e; // 邊數

    // adjacency list
    // pair<相鄰頂點, 邊的權重>
    vector<pair<int, int>>* adj;

    // edge list
    // Kruskal 演算法需要將所有邊取出來排序
    vector<Edge> edges;

    // 檢查頂點是否合法
    bool isValidVertex(int v) const {
        return v >= 0 && v < n;
    }

    // 邊排序規則
    // 1. 權重小的邊優先
    // 2. 權重相同時，頂點編號小的邊優先
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

    // 檢查 u 和 v 之間是否已經存在邊
    bool ExistsEdge(int u, int v) const {
        if (!isValidVertex(u) || !isValidVertex(v)) {
            return false;
        }

        for (auto neighbor : adj[u]) {
            if (neighbor.first == v) {
                return true;
            }
        }

        return false;
    }

    // 插入一條加權無向邊
    // 因為是無向圖，所以 u -> v 和 v -> u 都要加入 adjacency list
    void InsertEdge(int u, int v, int weight) {
        if (!isValidVertex(u) || !isValidVertex(v) || ExistsEdge(u, v)) {
            return;
        }

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});

        // edge list 只存一次，給 Kruskal 排序使用
        edges.push_back({u, v, weight});

        ++e;

        // 讓 adjacency list 依照頂點編號由小到大排列
        // 這樣輸出與後續處理會比較穩定
        sort(adj[u].begin(), adj[u].end());
        sort(adj[v].begin(), adj[v].end());
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

    // Kruskal's Algorithm
    // 作法：
    // 1. 將所有邊依照權重由小到大排序
    // 2. 從權重最小的邊開始選
    // 3. 如果加入該邊不會形成 cycle，就加入 MST
    // 4. 直到 MST 有 n - 1 條邊
    void Kruskal() {
        vector<Edge> sortedEdges = edges;
        vector<Edge> mst;
        int totalWeight = 0;

        // Kruskal 是照邊權重由小到大選
        sort(sortedEdges.begin(), sortedEdges.end(), compareEdge);

        DisjointSet ds(n);

        for (Edge edge : sortedEdges) {
            // 如果兩個頂點不在同一集合，代表加入此邊不會形成 cycle
            if (ds.Union(edge.u, edge.v)) {
                mst.push_back(edge);
                totalWeight += edge.weight;

                // MST 的邊數最多為 n - 1
                if (static_cast<int>(mst.size()) == n - 1) {
                    break;
                }
            }
        }

        cout << "Kruskal's Algorithm:" << endl;

        // 如果 MST 邊數不足 n - 1，代表圖不是連通圖
        if (static_cast<int>(mst.size()) != n - 1) {
            cout << "The graph is not connected. MST cannot be formed." << endl;
            return;
        }

        cout << "MST Edges:" << endl;
        for (Edge edge : mst) {
            cout << edge.u << " - " << edge.v
                 << " : " << edge.weight << endl;
        }

        cout << "Total Weight: " << totalWeight << endl;
    }

    // Prim's Algorithm
    // 作法：
    // 1. 從指定起點開始
    // 2. 每次從目前已連接的頂點集合中，選擇權重最小的邊
    // 3. 將新的頂點加入 MST
    // 4. 重複直到所有頂點都被加入
    void Prim(int start) {
        if (!isValidVertex(start)) {
            return;
        }

        vector<bool> visited(n, false);
        vector<Edge> mst;
        int totalWeight = 0;

        // priority_queue 預設是 max heap
        // 這裡自訂比較規則，讓它變成 min heap
        // 權重小的邊優先，權重相同時頂點編號小的邊優先
        auto cmp = [](const Edge& a, const Edge& b) {
            if (a.weight != b.weight) {
                return a.weight > b.weight;
            }

            int aSmall = min(a.u, a.v);
            int aLarge = max(a.u, a.v);
            int bSmall = min(b.u, b.v);
            int bLarge = max(b.u, b.v);

            if (aSmall != bSmall) {
                return aSmall > bSmall;
            }

            return aLarge > bLarge;
        };

        // Min-heap priority queue
        // 用來挑選目前可選邊中權重最小的邊
        priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);

        // Prim 是從起點開始，一步一步擴張出去
        visited[start] = true;

        // 先將起點相鄰的所有邊加入 priority queue
        for (auto neighbor : adj[start]) {
            pq.push({start, neighbor.first, neighbor.second});
        }

        while (!pq.empty() && static_cast<int>(mst.size()) < n - 1) {
            Edge edge = pq.top();
            pq.pop();

            // 如果這個頂點已經加入 MST，就跳過
            // 避免形成 cycle
            if (visited[edge.v]) {
                continue;
            }

            // 將新頂點加入 MST
            visited[edge.v] = true;
            mst.push_back(edge);
            totalWeight += edge.weight;

            // 將新頂點連出去的邊加入 priority queue
            for (auto neighbor : adj[edge.v]) {
                if (!visited[neighbor.first]) {
                    pq.push({edge.v, neighbor.first, neighbor.second});
                }
            }
        }

        cout << "Prim's Algorithm:" << endl;
        cout << "Start Vertex: " << start << endl;

        // 如果 MST 邊數不足 n - 1，代表圖不是連通圖
        if (static_cast<int>(mst.size()) != n - 1) {
            cout << "The graph is not connected. MST cannot be formed." << endl;
            return;
        }

        cout << "MST Edges:" << endl;
        for (Edge edge : mst) {
            cout << edge.u << " - " << edge.v
                 << " : " << edge.weight << endl;
        }

        cout << "Total Weight: " << totalWeight << endl;
    }
};

// 測試 Minimum Spanning Tree
int main() {
    // 建立 7 個頂點的加權無向圖
    // 頂點編號從 0 開始，到 6 結束
    Graph g(7);

    // 建立測試圖
    // InsertEdge(u, v, weight)
    g.InsertEdge(0, 1, 7);
    g.InsertEdge(0, 3, 5);
    g.InsertEdge(1, 2, 8);
    g.InsertEdge(1, 3, 9);
    g.InsertEdge(1, 4, 7);
    g.InsertEdge(2, 4, 5);
    g.InsertEdge(3, 4, 15);
    g.InsertEdge(3, 5, 6);
    g.InsertEdge(4, 5, 8);
    g.InsertEdge(4, 6, 9);
    g.InsertEdge(5, 6, 11);

    // 顯示 adjacency list
    cout << "Adjacency List:" << endl;
    g.showArraylist();

    cout << endl;

    // 執行 Kruskal 演算法
    // Kruskal 會照邊權重由小到大選邊
    g.Kruskal();

    cout << endl;

    // 執行 Prim 演算法
    // Prim 從起點 0 開始，一步一步擴張 MST
    g.Prim(0);

    return 0;
}