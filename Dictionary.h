//
// Created by 姜永铭 on 1/9/16.
//

#ifndef XINNUOTEST_DICTIONARY_H
#define XINNUOTEST_DICTIONARY_H
template <typename K, typename V>
struct Dictionary{
    virtual int size() const = 0;
    virtual bool put(K,V) = 0;
    virtual V* get(K k) = 0;
    virtual bool remove(K k) = 0;
};
#endif //XINNUOTEST_DICTIONARY_H
