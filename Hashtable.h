//
// Created by 姜永铭 on 1/9/16.
//

#ifndef XINNUOTEST_HASHTABLE_H
#define XINNUOTEST_HASHTABLE_H

#include "Dictionary.h"
#include "Bitmap.h"
#include "Entry.h"
#include "release.h"

template <typename K,typename V>
class Hashtable:public Dictionary{
private:
    Entry<K,V>** ht;
    int M;
    int N;
    Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
    int probe4Hit(const K& k);
    int probe4Free(const K& k);
    void rehash();

public:
    Hashtable(int c = 5);
    ~Hashtable();
    int size() const{
        return N;
    }

    bool put(K,V);
    V* get(K k);
    bool remove(K k);
};

static size_t hasCode(char c){
    return (size_t) c;
}
static size_t hasCode(int k){
    return (size_t) k;
}
static size_t hasCode(long long i){
    return (size_t)((i >> 32) + (int)i);
}
static size_t hasCode(char s[]){
    int h = 0;
    for(size_t n = strlen(s),i = 0; i < n ; i++){
        h = (h<<5)|(h>>27);
        h += (int)s[i];
    }
    return (size_t)h;
}

template <typename K,typename V>
Hashtable<K,V>::Hashtable(int c) {
    M = primeNLT(c, 1048576, "bitmap.txt" );
    N = 0;
    ht = new Entry<K,V>*[M];
    memset(ht,0, sizeof(Entry<K,V>*) * M);
    lazyRemoval = new Bitmap(M);

}

int primeNLT(int c, int n, char* file){
    Bitmap B(file,n);
    while(c<n)
        if(B.test(c)) c++;
        else return c;
    return c;
}
template <typename K,typename V>
Hashtable<K,V>::~Hashtable() {
    for(int i = 0; i < M; i++){
        if(ht[i]) release(ht[i]);
    }
    release(ht);
    release(lazyRemoval);
}

template <typename K,typename V>
V* Hashtable<K,V>::get(K k) {
    int r = probe4Hit(k);
    return ht[r] ? &(ht[r]->value) : NULL;
}
template <typename K,typename V>
int Hashtable<K,V>::probe4Hit(const K &k) {
    int r = hasCode(k) % M;
    while ((ht[r]&&(k != ht[r]->key )) || (!ht[r] && lazilyRemoved(r)) )
        r = (r+1) % M;
    return r;
}
template <typename K,typename V>
bool Hashtable<K,V>::remove(K k) {
    int r = probe4Hit(k);
    if(!ht[r]) return false;
    release(ht[r]);
    ht[r] = NULL;
    markAsRemoved(r);
    N--;
    return true;
}
#endif //XINNUOTEST_HASHTABLE_H
