//
// Created by 姜永铭 on 1/9/16.
//

#ifndef XINNUOTEST_GRAPHMATRIX_H
#define XINNUOTEST_GRAPHMATRIX_H

#include "Vector.h"
#include "Graph.h"

template <typename Tv>struct Vertex{
    Tv data;
    int inDegree,outDegree;
    VStatus status;
    int dTime,fTime;
    int parent;
    int priority;
    Vertex(Tv const& d = (Tv)0):
            data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
            dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

template <typename Te> struct Edge{
    Te data;
    int weight;
    EType type;
    Edge(Te const& d, int w):data(d),weight(w),type(UNDETERMINED){}
};

template <typename Tv,typename Te>
class GraphMatrix:public Graph<Tv,Te>{
private:
    Vector<Vertex<Tv>>V; //向量
    Vector<Vector<Edge<Te>*>>E; //邻接矩阵
public:
    GraphMatrix(){
        n = e =0;
    }
    ~GraphMatrix(){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                delete E[j][k];
            }
        }
    }

    //顶点基本操作
    virtual Tv& vertex(int i ){
        return  V[i].data;
    }

    virtual int inDegree(int i ){
        return V[i].inDegree;
    }
    virtual int outDegree(int i){
        return V[i].outDegree;
    }

    virtual int firstNbr(int i){
        return next(i,n);
    }
    virtual int nextNbr(int i, int j){
        while((-1 < j) && (!exists(i,--j)));
        return j;
    }

    virtual VStatus& status(int i) {
        return V[i].status;
    }

    virtual int& dTime(int i){
        return V[i].dTime;
    }
    virtual int& fTime(int i){
        return V[i].fTime;
    }
    virtual int& parent(int i){
        return V[i].parent;
    }

    virtual int& priority(int){
        return V[i].priority;
    }

    //顶点动态操作
    virtual int insert(Tv const& vertex){
        for(int j = 0; j < n; j++){
            E[j].insert(NULL); //Vector<Edge<Te>*>的insert,各个顶点留一条潜在关联边
            n++;
        }
        E.insert(Vector<Edge<Te>*>(n,n,(Edge<Te>*)NULL));//创建新顶点对应的边向量
        return V.insert(Vertex<Tv>(vertex));
    }

    virtual Tv remove(int i){
        for(int j = 0; j < n; j++){
            if(exists(i,j)){
                delete E[i][j];
                V[j].inDegree--;
            }
        }
        E.remove(i);
        n--;
        Tv vBak = vertex(i);
        V.remove(i);
        for(int j = 0; j < n; j++){
            if(Edge<Te>* e = E[j].remove(i)){
                delete e;
                V[i].outDegree--;
            }
        }
        return vBak;
    }

    //边的确认
    virtual bool exits(int i, int j){
        return (0 <= i)&&(i < n)&&(0 <= j)&& (j< n) && E[i][j]!=NULL;
    }

    virtual EType& type(int i, int j){
        return E[i][j]->type;
    }
    virtual Te& edge(int i, int j){
        return E[i][j]->data;
    }
    virtual int& weight(int i, int j){
        return E[i][j]->weight;
    }

    virtual void insert(Te const& edeg,int w, int i, int j){
        if(exits(i,j)) return;
        E[i][j] = new Edge<Te> (edge,w);
        e++;
        V[i].outDegree++;
        V[i].inDegree++;
    }

    virtual Te remove(int i, int j){
        Te eBak = edge(i,j);
        delete E[i][j];
        E[i][j] = NULL;
        e--;
        V[i].outDegree--;
        V[i].inDegree--;
        return eBak;
    }
};

#endif //XINNUOTEST_GRAPHMATRIX_H
