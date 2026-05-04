# Homework 2 - Graph

## 組員
- 41143138 陳韋綸
- 41143111 吳宗祐

---

## 專案介紹
本專案為資料結構 Homework 2 作業，使用 C++ 實作 Graph（圖形）相關資料結構與演算法。

內容包含圖形表示法、圖形走訪、最小生成樹、最短路徑以及活動網路等主題。

---

## 功能內容

### Graph Abstract Data Type（圖形抽象資料型態）
- Adjacency Matrix（鄰接矩陣）
- Linked Adjacency Lists（鏈結式鄰接串列）
- Array Adjacency Lists（陣列式鄰接串列）
- Directed Graph（有向圖）
- Undirected Graph（無向圖）
- Weighted Graph（加權圖）
- Unweighted Graph（非加權圖）
- Insert Vertex（插入頂點）
- Insert Edge（插入邊）
- Delete Vertex（刪除頂點）
- Delete Edge（刪除邊）
- Edge Existence Check（邊存在檢查）
- Number of Vertices（頂點數量）
- Number of Edges（邊數量）

### Elementary Graph Operations（圖形基本操作）
- Depth First Search（DFS 深度優先搜尋）
- Breadth First Search（BFS 廣度優先搜尋）
- Connected Components（連通元件）
- Biconnected Components（雙連通元件）

### Minimum Cost Spanning Trees（最小生成樹）
- Kruskal’s Algorithm
- Prim’s Algorithm

### Shortest Paths and Transitive Closure（最短路徑）
- Single Source Shortest Path（單源最短路徑）
- All-Pairs Shortest Paths（全點對最短路徑）

### Activity Networks（活動網路）
- Activity on Vertex（AOV 網路）
- Activity on Edge（AOE 網路）

### Test Data Generator (測資生成)
- 自動生成 Graph 測資
- 支援 Directed/Undirected (有向/無向)
- 支援 Weighted/Unweighted (加權/非加權)

### Benchmark（效能測試）
- 自動生成測資並測試演算法
- 支援不同規模測試：
  - 10,000 edges
  - 100,000 edges
  - 1,000,000 edges
- 顯示不同演算法執行時間
- 驗證資料規模（edge 數量輸出）
---

## 開發環境

### 軟體環境
- C++
- Visual Studio Code
- g++
- GitHub

### 硬體設備
- Windows 11
- 處理器	Intel(R) Core(TM) i5-14400F   2.50 GHz
- 已安裝記憶體(RAM)	32.0 GB
- 儲存體	1.86 TB SSD XPG GAMMIX S70 BLADE
- 顯示卡	NVIDIA GeForce RTX 4070 (12 GB)
- 系統類型	64 位元作業系統，x64 型處理器


---

## 編譯方式

使用 g++ 編譯 C++ 程式。

```bash
g++ *.cpp -o output
```

---

## 專案架構

```text
README.md

HW2/
├── 01_GraphAbstract/
│   ├── bin/
│   │   └── GraphAbstract.exe
│   │
│   ├── doc/
│   │   └── report.md
│   │
│   └── src/
│       └── GraphAbstract.cpp
│
├── 02_GraphOperations/
│   ├── bin/
│   │   └── GraphOperations.exe
│   │
│   ├── doc/
│   │   └── report.md
│   │
│   └── src/
│       └── GraphOperations.cpp
│
├── 03_MinimumSpanningTree/
│   ├── bin/
│   │   └── MinimumSpanningTree.exe
│   │
│   ├── doc/
│   │   └── report.md
│   │
│   └── src/
│       └── MinimumSpanningTree.cpp
│
├── 04_ShortestPath/
│   ├── bin/
│   │   └── ShortestPath.exe
│   │
│   ├── doc/
│   │   └── report.md
│   │
│   └── src/
│       └── ShortestPath.cpp
│
├── 05_ActivityNetwork/
│   ├── bin/
│   │   └── ActivityNetwork.exe
│   │
│   ├── doc/
│   │   └── report.md
│   │
│   └── src/
│       └── ActivityNetwork.cpp
│
├── TestDataGenerator/
│   ├── bin/
│   │   └── TestDataGenerator.exe
│   │
│   └── src/
│       └── TestDataGenerator.cpp
│
└── Benchmark/
    ├── bin/
    │   └── Benchmark.exe
    │
    ├── doc/
    │   └── report.md
    │
    └── src/
        └── Benchmark.cpp
```