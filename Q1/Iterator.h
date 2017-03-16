#ifndef ITERATOR_H
#define ITERATOR_H

#include<iostream>

using namespace std;

#include"node.h"

template <typename E>
class Iterator{
        private : 
                node<E> *p;
        public :
                Iterator(node<E> *q)
                {
                        p = q;
                }
                node<E>* &operator *()
                {
                        return p;
                }
};

#endif // ITERATOR_H
