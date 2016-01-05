#include<stdio.h>
#include<iostream>
#include "Vector.h"
#include "List.h"
#include "BinaryTree.h"
using namespace std;

void visit(int a){
    cout<<a<<" ";
}

int main() {
    int testData[15] = {12,45,23,87,56,23,134,93,4,98,33,44,6,2,56};
    BinTree<int>Bin;
    Bin.insertAtRoot(testData[0]);

    cout<<Bin.root()->data<<endl;
//    BinTree<int>* BinLeft;
//    Bin.attachLC(Bin.root(),BinLeft);
    //List Test
//    List<int> L;
//    for(int i = 0; i<15; i++){
//        L.insertAsLast(testData[i]);
//    }
//
//    ListNode<int> *p;
//    p = L.first();
//    cout<<p->data<<endl;
//    L.sort();
//    while(p!=L.last()->succ){
//        cout<<p->data<<" ";
//        p = p->succ;
//    }
//    cout<<endl;

    //L.traverse(visit);
    return 0;
}

