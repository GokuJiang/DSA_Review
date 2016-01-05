//
// Created by 姜永铭 on 1/5/16.
//

#ifndef XINNUOTEST_STACK_H
#define XINNUOTEST_STACK_H

#include "Vector.h"
template <typename T>
class Stack:public Vector<T>{
public:
    void push(T const& e){
        insert(size(),e);
    }
    T pop(){
        return remove(size()-1);
    }
    T& top(){
        return (*this)[size()-1];
    }
};
#endif //XINNUOTEST_STACK_H
