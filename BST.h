//
// Created by 姜永铭 on 1/6/16.
//

#ifndef XINNUOTEST_BST_H
#define XINNUOTEST_BST_H

#include "BinaryTree.h"

template <typename T>
class BST:public BinTree<T> {
protected:
    BinNodePosi(T) _hot;
    BinNodePosi(T) connect34(
       BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),
       BinNodePosi(T),BinNodePosi(T),BinNodePosi(T),BinNodePosi(T));
    BinNodePosi(T) rotateAt (BinNodePosi(T) v);

public:
    virtual BinNodePosi(T)& search(const T& e);
    virtual BinNodePosi(T) insert(const T& e);
    virtual bool remove(const T& e);
};

template <typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot){
    if(!v||(e == v->data)){
        return v;
    }
    hot = v;
    return searchIn(((e < v->data)? v->lc: v->rc),e,hot);
}
template <typename T>
BinNodePosi(T)& BST<T>::search(const T &e) {
    return searchIn(_root,e,_hot=NULL);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T &e) {
    BinNodePosi(T)& x = search(e);
    if (x)  return x;
    x = new BinNode<T>(e,_hot);
    _size++;
    updateHeightAbove(x);
    return x;
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T)& hot){
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;
    if(!HasLChild(*x)){
        succ = x = x->rc;
    }
    else if (!HasRChild(*x)){
        succ = x = x->lc;
    }
    else {
        w = w->succ();
        swap(x->data,w->data);
        BinNodePosi(T) u = w->parent;
        ((u == x)? u->rc:u->lc) = succ = w->rc;
    }
    hot = w->parent;
    if (succ) succ->parent = hot;
    release(w->data);
    release(w);
    return succ;
}
template <typename T>
bool BST<T>::remove(const T& e) {
    BinNodePosi(T)& x = search(e);
    if(!x) return false;
    removeAt(x,_hot);
    _size--;
    updateHeightAbove(_hot);
    return true;
}
template <typename T>
BinNodePosi(T) BST<T>::connect34(
        BinNodePosi(T)a ,BinNodePosi(T) b,BinNodePosi(T) c,
        BinNodePosi(T) T0 ,BinNodePosi(T) T1 ,BinNodePosi(T) T2 ,BinNodePosi(T)T3
    ){
        a->lc = T0; if(T0) T0->parent = a;
        a->rc = T1; if(T1) T1->parent = a;
        c->lc = T2; if(T2) T2->parent = c;
        c->rc = T3; if(T3) T3->parent = c;
        b->lc = a;  a->parent = b;
        b->rc = c;  c->parent = b;
}

template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) {
    BinNodePosi(T) p = v->parent; //父亲节点
    BinNodePosi(T) g = p->parent; //祖父节点
    if(IsLChild(*p)){ /*zig*/
        if(IsLChild(*v)){ /*zig-zig*/
            p->parent = g->parent;
            return connect34(v,p,g,v->lc,v->rc,p->rc,g->rc);
        }
        else{ /*zig-zag*/
            v->parent = g->parent;
            return connect34(p,v,g,p->lc,v->lc,v->rc,g->rc);
        }
    }
    else{ /*zag*/
        if(IsRChild(*v)){ /*zag-zag*/
            p->parent = g->parent;
            return connect34(g,p,v,g->lc,p->lc,v->lc,v->rc);
        }
        else{ /*zag-zig*/
            v->parent = g->parent;
            return connect34(g,v,p,g->lc,v->lc,v->rc,p->rc);
        }
    }
}
#endif //XINNUOTEST_BST_H
