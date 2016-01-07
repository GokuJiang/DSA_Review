//
// Created by 姜永铭 on 1/6/16.
//

#ifndef XINNUOTEST_AVL_H
#define XINNUOTEST_AVL_H
#include"BST.h"
template <typename T>
class AVL:public BST<T> {
public:
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
};

#define Balanced(x) (stature((x).lc) == stature((x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2 ))

#define tallerChild(x) (\
    stature((x)->lc) > stature((x)->rc) ? (x)->lc : (\
    stature((x)->lc) < stature((x)->rc) ? (x->rc) : (\
    IsLChild(*(x)) ? (x)->lc : (x)->rc \
    )\
    )\
)

template <typename T> BinNodePosi(T) AVL<T>::insert(const T &e) {
    BinNodePosi(T) & x = search(e);
    if(x) return x;
    BinNodePosi(T) xx = x = new BinNode<T>(e,_hot);
    _size++;
    for(BinNodePosi(T) g = _hot; g ;g = g->parent){
        if (!AvlBalanced(*g)) {
            FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else{
            updateHeightAbove(g);
        }
    }
    return xx;
}

template <typename T>
bool AVL<T>::remove(const T &e) {
    BinNodePosi(T) & x = search(e);
    if(!x) return false;

    removeAt(x,_hot);
    _size--;
    for(BinNodePosi(T) g = _hot; g; g = g->parent){
        if(!AvlBalanced(*g))
            g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
        updateHeightAbove(g);
    }
    return true;
}


#endif //XINNUOTEST_AVL_H
#endif //XINNUOTEST_AVL_H
