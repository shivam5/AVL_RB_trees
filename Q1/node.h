#ifndef NODE_H
#define NODE_H

#include<iostream>

using namespace std;

// Class for node (Used in making the avl tree)
template <typename E>
class node {
public:
    int key;
    E data;
    int height;
    node <E> *parent;
    node <E> *left;
    node *right;

    node();
    virtual ~node();

protected:
private:
};

template <typename E>
node <E>::node()
{
    key=-32768;
    //data=NULL;
    height=1;
    parent=left=right=NULL;
}


template <typename E>
node <E>::~node()
{
    //dtor
}


#endif // NODE_H
