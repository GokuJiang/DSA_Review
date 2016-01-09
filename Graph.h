//
// Created by Administrator on 2016/1/8.
//

#ifndef XINNUOTEST_GRAPH_H
#define XINNUOTEST_GRAPH_H

#include "Stack.h"
typedef enum{UNDISCOVERED,DISCOVERED,VISITED};
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD};

template <typename Tv, typename Te> //顶点边类型
class Graph {
private:
    void reset();
    void BFS(int, int&);
    void DFS(int, int&);
    void BCC(int, int&, Stack<int>&);
    bool Tsort(int,int&,Stack<Tv>&);

    template <typename PU> void PFS(int, PU); //连通域优先级搜索框架
public:
    int n;
    virtual int insert(Tv const&) = 0;
};
#endif //XINNUOTEST_GRAPH_H
