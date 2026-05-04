# Benchmark Report

## 1.解題說明

本實驗目的是透過大量圖形測資，
比較不同圖論演算法在實際執行時的效能差異。

測試內容涵蓋本次作業中所有主要演算法，
並使用相同規模的資料進行測試，以確保公平性。

測試規模包含：

- 10,000 edges
- 100,000 edges
- 1,000,000 edges

透過這些測試，可以觀察不同演算法在資料量增加時的表現變化。

---

## 2.程式實作

本實驗撰寫一個 Benchmark 程式，
負責以下流程：

1. 使用 TestDataGenerator 產生隨機加權圖
2. 建立 adjacency list 作為圖的表示方式
3. 呼叫各演算法進行運算
4. 使用 `chrono` 計算執行時間

主要測試演算法如下：

### GraphOperations
- DFS
- BFS
- Connected Components

### MinimumSpanningTree
- Kruskal
- Prim

### ShortestPath
- Dijkstra
- Bellman-Ford

### ActivityNetwork
- Topological Sort
- Critical Path（僅功能展示）

---

## 3.效能分析

### 時間複雜度

DFS：O(n + e)

BFS：O(n + e)

Connected Components：O(n + e)

Kruskal：O(e log e)

Prim：O(e log n)

Dijkstra：O(e log n)

Bellman-Ford：O(n × e)

Topological Sort：O(n + e)

Critical Path：O(n + e)

---

### 空間複雜度

Adjacency List：O(n + e)

Edge List：O(e)

Priority Queue：O(e)

Distance / visited 陣列：O(n)

---

## 4.測試與驗證

本實驗透過程式自動生成測資，
並執行各演算法進行測試。

為確保測資正確，
程式會輸出實際生成的邊數：

```cpp
cout << "Generated Edges: " << edges.size() << endl;
```
用來確認生成資料與預期一致。<br>

測試過程中，
透過 chrono 計算各演算法的執行時間，
並觀察不同規模下的變化。

### 輸出

#### 10,000 edges
```
Select Benchmark Size
1. 10,000 edges
2. 100,000 edges
3. 1,000,000 edges
Enter choice: 1

======================================
Benchmark Start
======================================
Vertex Count: 1000
Requested Edges: 10000

Generating test data...
Generated Edges: 10000
Generate Time: 0.0087899 seconds

Building graph...
Build Graph Time: 0.0024578 seconds

======================================
Homework 1 - GraphAbstract
======================================
InsertEdge Time: 0.0010987 seconds
ExistsEdge Time: 6e-07 seconds

======================================
Homework 2 - GraphOperations
======================================
DFS Time: 0.0009804 seconds
BFS Time: 0.0004689 seconds
Connected Components Time: 0.000463 seconds
Biconnected Components:
Not suitable for large-scale benchmark.

======================================
Homework 3 - MinimumSpanningTree
======================================
Kruskal Total Weight: 6665
Kruskal Time: 0.0021243 seconds
Prim Total Weight: 6665
Prim Time: 0.002231 seconds

======================================
Homework 4 - ShortestPath
======================================
Dijkstra Time: 0.001433 seconds
Bellman-Ford Time: 0.110783 seconds
Floyd-Warshall:
Not suitable for large-scale benchmark.

======================================
Homework 5 - ActivityNetwork
======================================
Topological Sort:
Not suitable for large-scale benchmark.

Critical Path:
Not suitable for large-scale benchmark.

Benchmark Finished
```

#### 100,000 edges
```
Select Benchmark Size
1. 10,000 edges
2. 100,000 edges
3. 1,000,000 edges
Enter choice: 2

======================================
Benchmark Start
======================================
Vertex Count: 10000
Requested Edges: 100000

Generating test data...
Generated Edges: 100000
Generate Time: 0.101098 seconds

Building graph...
Build Graph Time: 0.0206667 seconds

======================================
Homework 1 - GraphAbstract
======================================
InsertEdge Time: 0.0112204 seconds
ExistsEdge Time: 1e-06 seconds

======================================
Homework 2 - GraphOperations
======================================
DFS Time: 0.008501 seconds
BFS Time: 0.003334 seconds
Connected Components Time: 0.0031307 seconds
Biconnected Components:
Not suitable for large-scale benchmark.

======================================
Homework 3 - MinimumSpanningTree
======================================
Kruskal Total Weight: 66441
Kruskal Time: 0.0202752 seconds
Prim Total Weight: 66441
Prim Time: 0.0213643 seconds

======================================
Homework 4 - ShortestPath
======================================
Dijkstra Time: 0.0113344 seconds
Bellman-Ford Time: 9.22818 seconds
Floyd-Warshall:
Not suitable for large-scale benchmark.

======================================
Homework 5 - ActivityNetwork
======================================
Topological Sort:
Not suitable for large-scale benchmark.

Critical Path:
Not suitable for large-scale benchmark.

Benchmark Finished
```

#### 1,000,000 edges
```
Select Benchmark Size
1. 10,000 edges
2. 100,000 edges
3. 1,000,000 edges
Enter choice: 3

======================================
Benchmark Start
======================================
Vertex Count: 100000
Requested Edges: 1000000

Generating test data...
Generated Edges: 1000000
Generate Time: 1.37173 seconds

Building graph...
Build Graph Time: 0.210383 seconds

======================================
Homework 1 - GraphAbstract
======================================
InsertEdge Time: 0.0969528 seconds
ExistsEdge Time: 1e-06 seconds

======================================
Homework 2 - GraphOperations
======================================
DFS Time: 0.0715711 seconds
BFS Time: 0.0262365 seconds
Connected Components Time: 0.036574 seconds
Biconnected Components:
Not suitable for large-scale benchmark.

======================================
Homework 3 - MinimumSpanningTree
======================================
Kruskal Total Weight: 80817
Kruskal Time: 0.219223 seconds
Prim Total Weight: 80817
Prim Time: 0.345554 seconds

======================================
Homework 4 - ShortestPath
======================================
Dijkstra Time: 0.0715787 seconds
Bellman-Ford Time: 824.295 seconds
Floyd-Warshall:
Not suitable for large-scale benchmark.

======================================
Homework 5 - ActivityNetwork
======================================
Topological Sort:
Not suitable for large-scale benchmark.

Critical Path:
Not suitable for large-scale benchmark.

Benchmark Finished
```
### Graph Benchmark Report

#### 設定

- 圖形類型：無向加權圖
- 測資來源：隨機生成
- 測試規模：
  - 10,000 edges
  - 100,000 edges
  - 1,000,000 edges

---

#### 基本資訊

| 邊數 (Edges) | 頂點數 (Vertices) | 生成時間 (s) | 建圖時間 (s) |
|-------------|------------------|-------------|-------------|
| 10,000 | 1,000 | 0.0087899 | 0.0024578 |
| 100,000 | 10,000 | 0.101098 | 0.0206667 |
| 1,000,000 | 100,000 | 1.37173 | 0.210383 |

---

#### 圖形操作 (Graph Operations)

| 邊數 | DFS (s) | BFS (s) | 連通元件 (s) |
|------|--------|--------|-------------|
| 10,000 | 0.0009804 | 0.0004689 | 0.000463 |
| 100,000 | 0.008501 | 0.003334 | 0.0031307 |
| 1,000,000 | 0.0715711 | 0.0262365 | 0.036574 |

---

#### 最小生成樹 (MST)

| 邊數 | Kruskal (s) | Prim (s) |
|------|------------|----------|
| 10,000 | 0.0021243 | 0.002231 |
| 100,000 | 0.0202752 | 0.0213643 |
| 1,000,000 | 0.219223 | 0.345554 |

---

#### 最短路徑 (Shortest Path)

| 邊數 | Dijkstra (s) | Bellman-Ford (s) |
|------|-------------|------------------|
| 10,000 | 0.001433 | 0.110783 |
| 100,000 | 0.0113344 | 9.22818 |
| 1,000,000 | 0.0715787 | 824.295 |

---

#### DFS 與 BFS

- 兩者時間皆隨資料量線性成長
- BFS 在所有測試中略快於 DFS

原因：
- DFS 使用遞迴或 stack，有額外呼叫成本
- BFS 使用 queue，執行較穩定

結論：
> DFS 與 BFS 均為 O(V + E)，但 BFS 實務上略快

---

#### Kruskal 與 Prim

- 小規模時差異不大
- 大規模時 Kruskal 明顯較快

原因：
- Kruskal：排序一次 + Union-Find
- Prim：頻繁操作 Priority Queue（log V）

結論：
> 邊數多時，Kruskal 效能較佳

---

#### Dijkstra 與 Bellman-Ford

- Dijkstra 表現穩定
- Bellman-Ford 在大規模資料下效能急遽下降

原因：
- Dijkstra：O(E log V)
- Bellman-Ford：O(V × E)

結論：
> Bellman-Ford 不適合大型圖，僅用於負權邊情境

---

#### 不適合大型圖的演算法

- Floyd-Warshall（O(V³)）
- Biconnected Components
- Topological Sort（需 DAG）
- Critical Path（需 DAG）

---
- DFS / BFS / Connected Components 具良好擴展性
- Kruskal 在大規模圖中優於 Prim
- Dijkstra 為實務首選最短路徑演算法
- Bellman-Ford 在大型圖中不具實用性

---


## 5.申論及開發報告
在本次實驗中，
可以明顯觀察不同演算法在大規模資料下的差異。

DFS、BFS、Connected Components 等演算法，
由於時間複雜度為 O(n + e)，
在資料量增加時仍能維持穩定表現。

Kruskal 與 Prim 表現也相當穩定，
但仍受到排序與 priority queue 操作影響。

Dijkstra 在非負權重圖中效率良好，
是實務上常用的最短路徑演算法。

Bellman-Ford 則在資料規模增加時明顯變慢，
在 1,000,000 edges 測試中，
執行時間遠高於其他演算法，
顯示其 O(n × e) 的時間複雜度影響非常明顯。

在開發過程中也遇到一些問題：

Bellman-Ford 在大資料下執行時間過長
Floyd-Warshall 因為 O(n³) 無法應用在大規模測試
Activity Network 必須為 DAG 才能正確執行

透過這次 Benchmark，
不只是驗證演算法正確性，
也更清楚理解不同演算法在實際應用上的差異，
以及選擇合適演算法的重要性。