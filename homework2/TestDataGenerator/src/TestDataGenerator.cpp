#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Edge 結構
// u：起點
// v：終點
// weight：權重
struct Edge {
    int u;
    int v;
    int weight;
};

// Test Data Generator
//
// 功能：
// 自動生成 Graph 測資
//
// 支援：
// 1. Directed Graph
// 2. Undirected Graph
// 3. Weighted Graph
// 4. Unweighted Graph
//
// 可控制：
// 1. 頂點數
// 2. 邊數
// 3. 權重範圍
class TestDataGenerator {
private:

    // 產生 minValue ~ maxValue 的隨機數
    int randomNumber(int minValue, int maxValue) {
        return rand() % (maxValue - minValue + 1) + minValue;
    }

public:

    TestDataGenerator() {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    // 生成 Weighted Directed Graph
    vector<Edge> GenerateWeightedDirectedGraph(
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

            // 避免 self-loop
            if (u == v) {
                continue;
            }

            // 避免重複邊
            if (usedEdges.count({u, v})) {
                continue;
            }

            usedEdges.insert({u, v});

            int weight = randomNumber(minWeight, maxWeight);
            edges.push_back({u, v, weight});
        }

        return edges;
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

            // 無向圖中，(u, v) 和 (v, u) 視為同一條邊
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

    // 生成 Unweighted Directed Graph
    // weight 預設為 1
    vector<Edge> GenerateUnweightedDirectedGraph(
        int vertexCount,
        int edgeCount
    ) {
        vector<Edge> edges;
        set<pair<int, int>> usedEdges;

        while (static_cast<int>(edges.size()) < edgeCount) {
            int u = randomNumber(0, vertexCount - 1);
            int v = randomNumber(0, vertexCount - 1);

            if (u == v) {
                continue;
            }

            if (usedEdges.count({u, v})) {
                continue;
            }

            usedEdges.insert({u, v});
            edges.push_back({u, v, 1});
        }

        return edges;
    }

    // 生成 Unweighted Undirected Graph
    // weight 預設為 1
    vector<Edge> GenerateUnweightedUndirectedGraph(
        int vertexCount,
        int edgeCount
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
            edges.push_back({small, large, 1});
        }

        return edges;
    }

    // 顯示測資
    void ShowEdges(const vector<Edge>& edges) {
        cout << "Edge List" << endl;
        cout << "==========================" << endl;

        for (Edge edge : edges) {
            cout << edge.u
                 << " -> "
                 << edge.v
                 << " : "
                 << edge.weight
                 << endl;
        }

        cout << endl;
        cout << "Total Edges: "
             << edges.size()
             << endl;
    }
};

int main() {
    TestDataGenerator generator;

    cout << "======================================" << endl;
    cout << "Weighted Directed Graph" << endl;
    cout << "======================================" << endl;

    vector<Edge> weightedDirected =
        generator.GenerateWeightedDirectedGraph(
            10,
            20,
            1,
            100
        );

    generator.ShowEdges(weightedDirected);

    cout << endl << endl;

    cout << "======================================" << endl;
    cout << "Weighted Undirected Graph" << endl;
    cout << "======================================" << endl;

    vector<Edge> weightedUndirected =
        generator.GenerateWeightedUndirectedGraph(
            10,
            20,
            1,
            100
        );

    generator.ShowEdges(weightedUndirected);

    cout << endl << endl;

    cout << "======================================" << endl;
    cout << "Unweighted Directed Graph" << endl;
    cout << "======================================" << endl;

    vector<Edge> unweightedDirected =
        generator.GenerateUnweightedDirectedGraph(
            10,
            20
        );

    generator.ShowEdges(unweightedDirected);

    cout << endl << endl;

    cout << "======================================" << endl;
    cout << "Unweighted Undirected Graph" << endl;
    cout << "======================================" << endl;

    vector<Edge> unweightedUndirected =
        generator.GenerateUnweightedUndirectedGraph(
            10,
            20
        );

    generator.ShowEdges(unweightedUndirected);

    return 0;
}