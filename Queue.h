//
// Created by 姜永铭 on 1/5/16.
//

#ifndef XINNUOTEST_QUEUE_H
#define XINNUOTEST_QUEUE_H

#include "List.h"
template <typename T>
class Queue:public List<T>{
public:
    void enqueue(T const& e){
        insertAsLast(e);
    }

    T dequeue(){
        return  remove(first());
    }

    T& front(){
        return first()->data;
    }
};
#endif //XINNUOTEST_QUEUE_H
