//
// Created by 姜永铭 on 1/9/16.
//

#ifndef XINNUOTEST_QUADLISTNODE_H
#define XINNUOTEST_QUADLISTNODE_H

#include "Entry.h"
#define QlistNodePosi(T) QuadlistNode<T>*
template <template T> struct QuadlistNode {
    T entry;
    QlistNodePosi(T) pred;
    QlistNodePosi(T) succ;
    QlistNodePosi(T) above;
    QlistNodePosi(T) below;
    QuadlistNode(T e = T(),  QlistNodePosi(T) p = NULL, QlistNodePosi(T) s = NULL,
                 QlistNodePosi(T) a = NULL, QlistNodePosi(T) b = NULL ):
            entry(e),pred(p),succ(s),above(a),below(b){}
    QlistNodePosi(T) insertAsSuccAbove(T const& e , QlistNodePosi(T) b = NULL);
};

#endif //XINNUOTEST_QUADLISTNODE_H
