//
// Created by Administrator on 2016/1/8.
//

#ifndef XINNUOTEST_GRAPH_H
#define XINNUOTEST_GRAPH_H

#include "Stack.h"
#include "Queue.h"
typedef enum{UNDISCOVERED,DISCOVERED,VISITED}VStatus;
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD}EType;

template <typename Tv, typename Te> //顶点边类型
class Graph {
private:
    void reset(){
        for(int i = 0; i < n; i++){
            status(i) = UNDISCOVERED;
            dTime(i) = -1;
            fTime(i) = -1;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for (int j = 0; j <n ; j++) {
                if(exists(i,j))type(i,j) = UNDETERMINED;
            }
        }
    }
    void BFS(int, int&);
    void DFS(int, int&);
    void BCC(int, int&, Stack<int>&);
    bool Tsort(int,int&,Stack<Tv>*;

    template <typename PU> void PFS(int, PU); //连通域优先级搜索框架
public:
    int n; //顶点总数
    virtual int insert(Tv const&) = 0;
    virtual Tv remove(int) = 0;
    virtual Tv& vertex(int) = 0;
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0;
    virtual int nextNbr(int,int) = 0;
    virtual VStatus& status (int) = 0;
    virtual int& dTime(int) = 0;
    virtual int& fTime(int) = 0;
    virtual int& parent(int) = 0;
    virtual int& priority(int) = 0;

    //e
    int e; //边总数
    virtual bool exists(int ,int) =0;
    virtual void insert(Te const&, int, int, int) = 0;
    virtual Te remove(int,int) = 0;
    virtual EType& type(int,int) = 0;
    virtual Te& edge(int, int) = 0;
    virtual int& weight(int,int) = 0;

    //算法
    void bfs(int);
    void dfs(int);
    void bcc(int);
    Stack<Tv>* tSort(int);
    void prim(int);
    void dijkstra(int);
    template <typename PU>void pfs(int,PU);
};

template <typename Tv,typename Te>
void Graph<Tv,Te>::bfs(int s) {
    reset();
    int clock = 0;
    int v = s;
    do
        if(UNDISCOVERED == status(v)){
            BFS(v,clock);
        }
    while (s!=(v=(++v %n )));
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::BFS(int v, int & clock) {
    Queue<int>Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);
    while(!Q.empty()){
        int v = Q.dequeue();
        dTime(v) = ++clock;
        for(int u = firstNbr(v); -1 < u; u = nextNbr(v,u)){
            if(UNDISCOVERED == status(u)){
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v,u) = TREE;
                parent(u) = v;
            }
            else{
                type(v,u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}
template <typename Tv, typename Te>
void Graph<Tv,Te>::dfs(int s) {
    reset();
    int clock = 0;
    int v = s;
    do
        if(UNDISCOVERED == status(v)){
            DFS(v,clock);
        }
    while(s!=(v=(++v%n)));
}
template <typename Tv, typename Te>
void Graph<Tv,Te>::DFS(int v, int &clock) {
    dTime(v) = ++clock;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v,u)) {
        switch (status(u)){
            case UNDISCOVERED:
                type(v,u)= TREE;
                parent(u) = v;
                DFS(u,clock);
                break;
            case DISCOVERED:
                type(v,u) = BACKWARD;
                break;
            default:
                type(v,u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

template <typename Tv,typename Te>
Stack<Tv>* Graph<Tv,Te>::tSort(int s) {
    reset();
    int clock;
    int v = s;
    Stack<Tv>* S = new Stack<Tv>;
    do{
        if(UNDISCOVERED == status(v)){
            if(!Tsort(v,clock,S)){
                while (!S->empty()){
                    S->pop();
                    break;
                }
            }
        }
    }while (s!=(v=++v % n));
    return S;
}

template <typename Tv,typename Te>
bool Graph<Tv,Te>::Tsort(int v, int &clock, Stack<Tv> *S){
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for(int u = firstNbr(v); -1 < u; u = nextNbr(v,u)){
        switch(status(u)){
            case UNDISCOVERED:
                parent(u) = v;
                type(v,u) = TREE;
                if(!Tsort(u,clock,S))
                    return false;
                break;
            case DISCOVERED:
                type(v,u) = BACKWARD;
                return false;
            default:
                type(v,u) = (dTime(v) < dTime(u))? FORWARD : CROSS;
        }
    }
    status(v) = VISITED;
    S->push(vertex(v));
    return true;
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::bcc(int s) {
    reset();
    int clock = 0;
    int v = s;
    Stack<int>S;
    do
        if(UNDISCOVERED == status(v)){
            BCC(v,clock,S);
            S.pop();
        }
    while(s!=(v=(++v%n)));
}

#define hca(x) (fTime(x))
template <typename Tv,typename Te>
void Graph<Tv,Te>::BCC(int v, int &clock, Stack<int>& S) {
    hca(v) = dTime(v) = ++clock;
    status(v) = DISCOVERED;
    S.push(v);
    for(int u = firstNbr(v); -1 < u; u = nextNbr(v,u)){
        switch (status(u)){
            case UNDISCOVERED:
                parent(u) = v;
                type(v,u) = TREE;
                BCC(u,clock,S);
                if(hca(u)<dTime(v)){
                    hca(v) = min(hca(v),hca(u));
                }
                else{
                    while(v != S.pop());
                    S.push(v);
                }
                break;
            case DISCOVERED:
                type(v,u) = BACKWARD;
                if(u!=parent(v)) hca(v) = min(hca(v),hca(u));
                break;
            default:
                type(v,u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
}
#undef hca

template <typename Tv, typename Te, typename PU>
void Graph<Tv,Te>::pfs(int s, PU prioUpdater) {
    reset();
    int v = s;
    do
        if(UNDISCOVERED == status(v)){
            PFS(v,prioUpdater);
        }
    while (s!=(v=(++v%n)));
}

template <typename Tv, typename Te, typename PU>
void Graph<Tv,Te>::PFS(int s, PU prioUpdater) {
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;
    while(true){
        for(int w = firstNbr(s); -1 < w; w = nextNbr(s,w)){
            prioUpdater(this,s,w);
        }
        for(int shortest = INT_MAX , w = 0; w < n; w++){
            if (UNDISCOVERED == status(w)){
                if(shortest > priority(w)){
                    shortest = priority(w);
                    s = w;
                }
            }
        }
        if(VISITED == status(s)) break;
        status(s) =VISITED;
        type(parent(s),s) = TREE;
    }
}

template <typename Tv,typename Te>
struct PrimePU {
    virtual void operator()(Graph<Tv,Te>*g,int uk,int v){
        if (UNDISCOVERED == g->status(v)){
            if(g->priority(v) > g->weight(uk,v)){
                g->priority(v) = g->weight(uk,v);
                g->parent(v) = uk;
            }
        }
    }
};
template <typename Tv,typename Te>
struct DijkstraPU {
    virtual void operator() (Graph<Tv,Te>*g,int uk,int v){
        if (UNDISCOVERED == g->status(v)){
            if(g->priority(v) > g->priority(uk) + g->weight(uk,v)){
                g->priority(v) = g->priority(uk) + g->weight(uk,v);
                g->parent(v) = uk;
            }
        }
    }
};


#endif //XINNUOTEST_GRAPH_H
