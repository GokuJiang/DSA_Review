//
// Created by 姜永铭 on 1/5/16.
//

#ifndef XINNUOTEST_RELEASE_H
#define XINNUOTEST_RELEASE_H

#include <typeinfo>
template <typename T>
struct Cleaner{
    static void clean(T x){
#ifdef _DEBUG
    static int n = 0;
        if(7 > strlen(typeid(T).name())) {
            printf("\t<%s>[%d]=",typid(T).name(),++n);
            printf(x);
            printf("purged\n");
        }
#endif
    }
};

template <typename T> struct Cleaner<T*> {
    static void clean(T* x){
        if(x) {delete x;}
#ifdef _DEBUG
         static int n = 0;
        printf("\t<%s>[%d]released\n",typid(T*).name(),++n);
#endif
    }
};

template <typename T>
void release(T x){
    Cleaner<T>::clean(x);
}

#endif //XINNUOTEST_RELEASE_H
