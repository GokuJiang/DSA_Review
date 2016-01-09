//
// Created by 姜永铭 on 1/9/16.
//

#ifndef XINNUOTEST_SKIPLIST_H
#define XINNUOTEST_SKIPLIST_H

#include "List.h"
#include "Entry.h"
#include "Quadlist.h"
#include "Dictionary.h"
template <typename K, typename V>
class Skiplist:public Dictionary<K,V>,public List< Quadlist<Entry<K,V>>* > {
protected:
    bool skipSearch (
            ListNode<Quadlist<Entry<K,V>>*>* &qlist,
            QuadlistNode<Entry<K,V>>* &p,
            K& k
    );

public:
    int size() const {
        return empty() ? 0 : last()->data->size();
    }
    int level() {
        return List::size();
    }
    bool put(K,V);
    V* get(K k);
    bool remove(K k);

};
template <typename K, typename V>
V* Skiplist<K,V>::get(K k) {
    if(empty()){
        return  NULL;
    }
    ListNode<Quadlist<Entry<K,V>>*>* qlist = first();
    QuadlistNode<Entry<K,V>>* p = qlist->data->first();
    return skipSearch(qlist,p,k) ? &(p->entry->value):NULL;
}
template <typename K, typename V>
bool Skiplist<T,V>::skipSearch (
        ListNode<Quadlist<Entry<K,V>>*>* &qlist,
        QuadlistNode<Entry<K,V>>* &p,
        K& k
) {
    while(true){
        while(p->succ && (p->entry.key <= k)){
            p = p->succ;
        }
        p = p->pred;
        if(p->pred && (k == p->entry.key)) return true;

        qlist = qlist->succ;
        if(!qlist->succ) return false;

        p = (p->pred) ? p->below:qlist->data->first();
    }
}

template <typename K, typename V>
bool Skiplist<K,V>::put(K k, V v) {
    Entry<K,V> e = Entry<K,V>(k,v);
    if(empty()){
        insertAsFirst(new Quadlist<Entry<K,V>>);
    }
    ListNode<Quadlist<Entry<K,V>>*>* qlist = first();
    QuadlistNode<Entry<K,V>>* p = qlist->data->first();
    if(skipSearch(qlist,p,k)){
        while(p->below) p = p->below;
    }
    qlist = last();
    QuadlistNode<Entry<K,V>>* b = qlist->data->insertAfterAbove(e,p);
    while(rand() & 1){
        while(qlist->data->vaild(p) && !p->above) p = p->pred;

        if(!qlist->data->vaild(p)){
            if(qlist == first())
                insertAsFirst(new Quadlist<Entry<K,V>>);
            p = qlist->pred->data->first()->pred;
        }
        else{
            p = p->above;
        }
        qlist = qlist->pred;
        b = qlist->data->insertAfterAbove(e,p,b);
    }
    return true;
}
#endif //XINNUOTEST_SKIPLIST_HV*
