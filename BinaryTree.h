//
// Created by 姜永铭 on 1/5/16.
//

#ifndef XINNUOTEST_BINARYTREE_H
#define XINNUOTEST_BINARYTREE_H

#include <iostream>
#include <stdio.h>
#include "release.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

#define BinNodePosi(T) BinNode<T>*  //节点位置
#define stature(p) ((p)?(p)->height:-1) //节点高度
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x)||HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p)) ? ((p)->parent->rc:(p)->parent->lc))
#define uncle(x) (IsLChild(*(p)) ?  (p)->parent->rc: (p)->parent->lc)
#define FromParentTo(x) /*来自父亲的引用*/\
(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))


typedef enum {RB_RED,RB_BLACK} RBColor;
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit){
    if(!x) return;
    visit(x->data);
    travPre_R(x->lc,visit);
    travPre_R(x->rc,visit);
};
template <typename T, typename VST>
void travPost_R (BinNodePosi(T) x, VST& visit){
    if(!x) return;
    travPost_R(x->lc,visit);
    travPost_R(x->rc,visit);
    visit(x->data);
};

template <typename T, typename VST>
void travIn_R (BinNodePosi(T) x, VST& visit){
    if(!x) return;
    travIn_R(x->lc,visit);
    visit(x->data);
    travIn_R(x->rc,visit);
};
template <typename T>
struct BinNode {
    T data;
    BinNodePosi(T)parent;
    BinNodePosi(T)lc;
    BinNodePosi(T)rc;
    int height;
    int npl;  //左式堆
    RBColor color;

    //构造函数
    BinNode() :
            parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }

    BinNode(T e, BinNodePosi(T)p = NULL, BinNodePosi(T)lc = NULL, BinNodePosi(T)rc = NULL, int h = 0, int l = 1,
            RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }

    int size();

    BinNodePosi(T)insertAsLC(T const &);
    BinNodePosi(T)insertAsRC(T const &);

    BinNodePosi(T)succ();

    template<typename VST>
    void travLevel(VST &);
    template<typename VST>
    void travPre(VST &);
    template<typename VST>
    void travIn(VST &);
    template<typename VST>
    void travPost(VST &);

    bool operator<(BinNode const &bn) {
        return this->data < bn.data;
    }

    bool operator==(BinNode const &bn) {
        return this->data == bn.data;
    }
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
    return  lc = new BinNode(e,this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
    return rc = new BinNode(this,e);
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) s = this;
    if(rc){
        s = rc;
        while(HasLChild(*s)) s = s->lc;
    }else{
        while(IsRChild(*s)) s = s->parent;
    }
    return s;
}


template <typename T>
class BinTree{
protected:
    int _size;
    BinNodePosi(T) _root;
    virtual  int updateHeight(BinNodePosi(T) x);
    void updateHeightAbove(BinNodePosi(T) x);

public:
    BinTree():_size(0),_root(NULL){}
    ~BinTree(){
        if (0<_size){
            remove(_root);
        }
    }

    int size(){
        return _size;
    }

    bool empty() const{
        return _size;
    }

    BinNodePosi(T) root() const { return _root;}
    BinNodePosi(T) insertAtRoot(T const& e);
    BinNodePosi(T) insertAtLC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) insertAtRC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) attachLC(BinNodePosi(T) x, BinTree<T>* &S);
    BinNodePosi(T) attachRC(BinNodePosi(T) x, BinTree<T>* &S);
    int remove(BinNodePosi(T) x);
    BinTree<T>* secede(BinNodePosi(T) x);
    template <typename VST> void traveLevel(VST& visit){
        if (_root) _root->travLevel(visit);
    }
    template <typename VST> void travePre(VST& visit){
        if (_root) _root->travPre(visit);
    }
    template <typename VST> void traveIn(VST& visit){
        if (_root) _root->travIn(visit);
    }
    template <typename VST> void travePost(VST& visit){
        if (_root) _root->travPost(visit);
    }

//    bool operator< (BinTree<T> const& t){
//        return _root && t._root && lt(_root,t._root);
//    }

    bool operator== (BinTree<T> const& t){
        return _root && t._root && _root == t._root;
    }
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
   return x->height = 1 + max(stature(x->lc),stature(x->rc));  //
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
    while (x)  {
        updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAtRoot(T const &e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAtLC(BinNode<T> *x, T const &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::insertAtRC(BinNode<T> *x, T const &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachLC(BinNodePosi(T) x, BinTree<T>* &S) {
    if(x->lc = S->_root) {
       x->lc->parent = x;
    }
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachRC(BinNodePosi(T) x, BinTree<T>* &S) {
    if(x->rc = S->_root) {
        x->rc->parent = x;
    }
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}
template <typename T>
static int removeAt(BinNodePosi(T) x){
    if(!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;

}
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T> *x) {
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    BinTree<T>* S = new BinTree<T>;
    S->_root = x;
    x->parent = NULL;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}

//迭代版 先序遍历
template <typename T,typename VST>
static void visitAlongLeftBranch(BinNodePosi(T)x, VST& visit,Stack<BinNodePosi(T)>& S){
    while (x){
        visit(x);
        S.push(x->rc);
        x = x->lc;
    }
}
template <typename T,typename VST>
void travPre_I2(BinNodePosi(T) x,VST& visit){
    Stack<BinNodePosi(T)>S;
    while (true){
        visitAlongLeftBranch(x,visit,S);
        if(S.empty())break;
        x = S.pop();
    }
}

//迭代版中序遍历
template <typename T>
static void goAlongLeftBranch(BinNodePosi(T)x,Stack<BinNodePosi(T)>&S){
    while (x){
        S.push(x);
        x = x->lc;
    }
}
template <typename T,typename VST>
void travIn_I1(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)> S;
    while  (true){
        goAlongLeftBranch(x,S);
        if(S.empty()) break;

        x = S.pop();
        visit(x->data);
        x = x->rc;
    }
}
template <typename T,typename VST>
void travIn_I2(BinNodePosi(T)x,VST& visit){
    Stack<BinNodePosi(T)>S;
    while(true){
        if (x){
            S.push(x);
            x = x->lc;
        }
        else if(!S.empty()) {
            x = S.pop();
            visit(x->data);
            x=x->rc;
        }
        else
            break;
    }
}
template <typename T,typename VST>
void travIn_I3(BinNodePosi(T)x,VST& visit){
    bool backtrack = false;
    while(true){
        if(!backtrack&&HasLChild(*x))
            x = x->lc;
        else {
            visit(x->data);
            if(HasRChild(*x)){
                x = x->rc;
                backtrack = false;
            } else{
                if (!(x = x->succ())) break;
                backtrack = true;
            }
        }
    }
}

template <typename T> template <typename VST>
void BinNode<T>::travIn(VST& vist) {
    switch (1){
        case 1: travIn_I1(this,vist);break;
        case 2: travIn_I2(this,vist);break;
        case 3: travIn_I3(this,vist);break;
        default:travIn_R(this,vist);break;
    }
}

//后序遍历
template <typename T>
static void gotoHLVFL(Stack<BinNodePosi(T)>& S){
    while (BinNodePosi(T) x = S.top()){
        if (HasLChild(*x)){
            if(HasRChild(*x)) {
                S.push(x->rc);
            }
            S.push(x->lc);
        }
    }
    S.pop();
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit){
    Stack<BinNodePosi(T)>S;
    if(x) S.push(x);
    while(!S.empty()){
        if(S.top()!=x->parent)
            gotoHLVFL(S);
        x = S.pop();
        visit(x->data);
    }
}

//层次遍历
template <typename T,typename VST>
void BinNode<T>::travLevel(VST& visit) {
    Queue<BinNodePosi(T)>Q;
    Q.enqueue(this);
    while(!Q.empty()){
        BinNodePosi(T) x= Q.dequeue();
        visit(x->data);
        if(HasLChild(*x)) Q.enqueue(x->lc);
        if(HasRChild(*x)) Q.enqueue(x->rc);
    }
}

#endif //XINNUOTEST_BINARYTREE_H
