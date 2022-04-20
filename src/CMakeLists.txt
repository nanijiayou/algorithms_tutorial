cmake_minimum_required(VERSION 3.14)
project("impls")

# 版本检查
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# c++ 11
set(CMAKE_CXX_STANDARD 11)

# 源文件list
set(algoList)

# base datastruct
LIST(APPEND algoList
    BST
    Heap
    DisjointSet
    SparseTable)

# DC & Linear
LIST(APPEND algoList
    MergeSort
    BucketSort
    QuickSort
    QuickSelect
    MaxSubArray
    CountingSort)

# tree
LIST(APPEND algoList
    SegementTree
    Treap
    FHQTreap
    SplayTree)

# graph part
LIST(APPEND algoList
    GraphAdj
    Starts
    BFS
    DFS
    TopologicalSort
    SCC
    Bridges
    Cutpoints
    Tarjan
    MST
    Kruskal
    Prim
    LCA
    SPFA
    KSP
    BellmanFord
    Dijkstra
    DiffConstraints
    FloydWarshall
    Johnson
    EdmondsKarp
    FordFulkerson
    PushRelabel)


LIST(APPEND algoList
    Compose
    Premutation)


foreach(X IN LISTS algoList)
    add_executable(${X} ${X}/main.cpp)
    message(STATUS "add ${X}/main.cpp")
endforeach()
