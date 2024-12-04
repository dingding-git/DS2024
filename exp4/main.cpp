#include "../exp4/Graph.cpp"
int main() {
    GraphMatrix<string, string> graph;

    // 插入顶点
    graph.insert("X");
    graph.insert("Y");
    graph.insert("Z");
    graph.insert("P");
    graph.insert("Q");

    // 插入边 (边名, 权重, 起点索引, 终点索引)
    graph.insert("XY", 2, 0, 1);
    graph.insert("XZ", 5, 0, 2);
    graph.insert("YZ", 1, 1, 2);
    graph.insert("YP", 3, 1, 3);
    graph.insert("ZP", 2, 2, 3);
    graph.insert("PQ", 4, 3, 4);
    graph.insert("ZQ", 7, 2, 4);

    // 深度优先搜索
    cout << "Depth-First Search (DFS) starting from vertex X:\n";
    graph.dfs(0); // 从顶点 X 开始深度优先遍历
    for (int i = 0; i < graph.n; i++) {
        cout << "Vertex " << graph.vertex(i) << ": ";
        cout << "Discover Time = " << graph.dTime(i) << ", ";
        cout << "Finish Time = " << graph.fTime(i) << ", ";
        cout << "Parent = " << (graph.parent(i) != -1 ? graph.vertex(graph.parent(i)) : "None") << endl;
    }

    // 广度优先搜索
    cout << "\nBreadth-First Search (BFS) starting from vertex X:\n";
    graph.bfs(0); // 从顶点 X 开始广度优先遍历
    for (int i = 0; i < graph.n; i++) {
        cout << "Vertex " << graph.vertex(i) << ": ";
        cout << "Distance = " << graph.dTime(i) << ", ";
        cout << "Parent = " << (graph.parent(i) != -1 ? graph.vertex(graph.parent(i)) : "None") << endl;
    }

    // Dijkstra 算法计算最短路径
    cout << "\nShortest paths from vertex X using Dijkstra:\n";
    graph.dijkstra(0);

    // Prim 算法生成最小生成树
    cout << "\nMinimum Spanning Tree using Prim's algorithm starting from vertex X:\n";
    graph.prim(0);

    return 0;
}
