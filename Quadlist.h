//
// Created by 姜永铭 on 1/9/16.
//

#ifndef XINNUOTEST_QUADLIST_H
#define XINNUOTEST_QUADLIST_H

#include "QuadlistNode.h"
template <typename T>
class Quadlist{
private:
    int _size;
    QlistNodePosi(T) header;
    QlistNodePosi(T) trailer;
protected:
    void init();
    int clear();

public:
    Quadlist(){
        init();
    }

    ~Quadlist(){
        clear();
        delete header;
        delete trailer;
    }

    Rank size() const {
        return _size;
    }
    bool empty() const{
        return _size <= 0;
    }
    QlistNodePosi(T) first() const {
        return header->succ;
    }
    QlistNodePosi(T) last() const {
        return trailer->pred;
    }
    bool vaild(QlistNodePosi(T) p){
        return p &&(trailer != p)&&(header != p);
    }

    T remove(QlistNodePosi(T) p);
    QlistNodePosi(T) insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T)b = NULL);

    void traverse(void(*)(T&));
    template <typename VST&> void traverse(VST&);
};

template <typename T>
void Quadlist<T>::init() {
    header = new QuadlistNode<T>;
    trailer = new QuadlistNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    header->above = trailer->above = NULL;
    header->below = trailer->below = NULL;
    _size = 0;
}

#endif //XINNUOTEST_QUADLIST_H
