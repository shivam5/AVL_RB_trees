#ifndef REDBLACK_H
#define REDBLACK_H
#include "node.h"
#include <vector>

template <typename E>
class redblack {
public:
    node <E> * insert(int k,E v);
    node <E> * search(int k);
    void remove (node <E> * p);
    void remove (int k);    
    int numberofleaves();
    int height ();
    int bheight();
    vector <int> list (int a, int b);
 
    node <E> *successor (node <E> *x);    
    int h (node <E> *t);    
    void n(node <E> *t, int &number);
    node <E> * min(node <E> *x);
    node <E> * max(node <E> *x);
    node <E> * leftrotation(node <E> *y);
    node <E> * rightrotation(node <E> *y);
    node <E> * bstinsertion(int k,E v);    
    void display(node <E> *ptr, int level);
    void dis();

    redblack();
    virtual ~redblack();

protected:
private:
    node <E> *root;

};



template <typename E>
redblack <E> :: redblack(){
    root=NULL;
}

template <typename E>
redblack <E> :: ~redblack(){
    
}

template <typename E>
node <E> * redblack <E> :: successor(node <E> *x){
    
    if (x==NULL)
        return NULL;
        
        
    if (x->right!=NULL)
     return min(x->right);
     
    node <E> *y=x->parent;
    while (y != NULL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

template <typename E>
vector <int> redblack <E> :: list (int a, int b){
    node <E> *x=min(root);
    vector <int> v;
    
    while (x!=NULL){
        if (x->key>a && x->key<b){
            v.push_back(x->key);            
        }
        x=successor(x);
    }
    
    return v;    

}

template <typename E>
int redblack <E> :: height (){
    return h(root);
}

template <typename E>
int redblack <E> :: h (node <E> *t){
    if (t==NULL)
        return 0;
        
    int left,right;
    
    left=h(t->left);
    right=h(t->right);
    
    if(left>=right)
        return 1+left;
    else
        return 1+right;
}


template <typename E>
int redblack <E> :: bheight(){
    int h=0;
    node <E> *t=root;
    if (t==NULL)
        return 0;
    
    else{
        while (t!=NULL){
            if (t->colour==0)
                h++;
            t=t->left;
        } 
    }
    
    return h;
}


template <typename E>
void redblack <E> :: n( node <E> *t, int &number){    
    if(t==NULL)
        return;
    
    n(t->left, number);
    
    if(t->left==NULL && t->right==NULL)
        number++;
        
    n(t->right, number); 
}


template <typename E>
int redblack <E> :: numberofleaves(){    
    int number = 0;
    n(root,number);
    return number; 
}

template <typename E>
node <E> * redblack <E> :: search(int k){
    node <E> *t=root;
    while (t!=NULL){
        if ((t->key)==k)
            return t;
        else if (k<(t->key))
            t=t->left;
        else
            t=t->right;
    }
    node <E> *end = new node <E>;
    end->key=-32768;
    cout<<"Item not found\n";
    return end;

}

template <typename E>
node <E> * redblack <E> :: min(node <E> *x){
    while (x->left!=NULL)
        x=x->left;
        
    return x;
}

template <typename E>
node <E> * redblack <E> :: max(node <E> *x){
    while (x->right!=NULL)
        x=x->right;
        
    return x;
}

template <typename E>
void redblack <E> :: remove(node <E> * p) {
    node <E> *x;
    node <E> *b;
    node <E> *a;
    node <E> *c;
    node <E> *d;
    node <E> *y;
    

    x=search(p->key);
    
    
    if(x->key==-32768){
        return;
    }    
        
m:      
    y = x->parent;
    
    
        if (x==root && y==NULL && x->left==NULL && x->right==NULL){
            root=NULL;
            delete x;
            return;
        }
        
    
    // Removing a leaf node
    if (x->left==NULL && x->right==NULL){
    
                
        
        // Leaf node with red colour
        if (x->colour==1){
            if(y->left == x){
                y->left=NULL;
            }
            else if (y->right==x){
                y->right=NULL;
            }
            delete x;
            return;    
        }
        // Leaf node with blackk colour
        else if (x->colour == 0){
            if(y->left == x){
                y->left=NULL;
                b=y->right;
            }
            else if (y->right ==x){
                y->right=NULL;
                b=y->left;
            }

            delete x;
        }
    
    }
    // y is the parent of x if it is black
    
    // Removing a node with a single child, node will always be black
    else if((x->left==NULL && x->right!=NULL) || (x->left!=NULL && x->right==NULL)){
        
        // Right leaf present, no left leaf
        if (x->left==NULL && x->right!=NULL){
            node <E> *t=min(x->right);
            int temp=x->key;
            x->key=t->key;
            t->key=temp;
            x=t;
        }
        
        // Left leaf present, no right leaf
        else{
            node <E> *t=max(x->left);
            int temp=x->key;
            x->key=t->key;
            t->key=temp;
            x=t;            
            
        }
        
        goto m;
        
    }
    
    // Removing node with two children
    else if (x->left!=NULL && x->right!=NULL) {    
        node <E> *t=min (x->right);
        int temp=t->key;
        E temp2 = t->data;
        t->key=x->key;
        t->data = x->data;
        x->key=temp;
        x->data = temp2;
        x=t;
        goto m;    
    }
    
    
    //
    // BST DELETE ENDS
    //
    //
    

// If black leaf is deleted
// Then the parent y is with us.
// Rebalancing
 
    a=y;
     
    while (1) {
    
    // b is the left child of a
    if (a->left==b){
        
        //b is the left child of a, a is red
        if (a->colour==1){
            //b is the left child of a, a is red, b is black
            if (b->colour==0){
                // b is the left child of a, a is red, b is black, c=b->left is red
                if (b->left!=NULL && b->left->colour==1){
                c=b->left;
                   // node <E> *w=a->parent;
                
                a->colour=0;
                b->colour=1;
                c->colour=0;
                
            
                z: 
                node <E> *w=a->parent;

                if(w==NULL){
                    root=rightrotation(a);
                    root->parent=NULL;
                    return;
                }
                    
                else if((w->left)==a){
                    w->left=rightrotation(a);
                    (w->left)->parent=w;
                    return;
                }
                    
                else if ((w->right)==a){
                    w->right=rightrotation(a);
                    (w->right)->parent=w;  
                    return;
                    
                }
                
                
                }
                
                // b is the left child of a, a is red, b is black, c=b->right is red
                else if(b->right!=NULL && b->right->colour==1){
                c=b->right;
                //node <E> *w=a->parent;
                
                a->colour=0;
                b->colour=0;
                c->colour=1;
                
                y: 
                node <E> *w=a->parent;
                if(w==NULL){
                    a->left=leftrotation(b);
                    a->left->parent=a;
                    root=rightrotation(a);
                    root->parent=NULL;
                    return;
                }
                    
                else if((w->left)==a){
                    a->left=leftrotation(b);
                    a->left->parent=a;
                    w->left=rightrotation(a);
                    (w->left)->parent=w;
                    return;
                }
                    
                else{
                    a->left=leftrotation(b);
                    a->left->parent=a;
                    w->right=rightrotation(a);
                    (w->right)->parent=w;  
                    return;
                }
                
                }
                // b is the left child of a, a is red, b is black, both b children are black
                else{
                    b->colour=1;
                    a->colour=0;
                    return;
                
                } 
                
            }
            
        } // a is red ends
        
        // b is the left child of a, a is black
        else if (a->colour==0){
            if (b->colour==0){
                // b is the left child of a, a is black, b is black, c=b->left is red
                if (b->left!=NULL && b->left->colour==1){
                    c=b->left;
                    c->colour=0;
                    a->left=rightrotation(b);
                    a->left->parent=a;
                    b=a->left;
                    c=b->right;    
                    goto y;
                    
                }
                // b is the left child of a, a is black, b is black, c=b->right is red
                else if(b->right!=NULL && b->right->colour==1){
                    c=b->right;
                    c->colour=0;
                    goto y;
                    
                }
                // b is the left child of a, a is black, b is black, both b children are black
                else{                
                    b->colour=1;
                } 
                
            }
            //b is the left child of a, a is black, b is red
            else if (b->colour==1){
            
                
                // b is the left child of a, a is black, b is red, c=b->right is black
                if(b->right!=NULL && b->right->colour==0){
                    c=b->right;
                    //b is the left child of a, a is black, b is red, c=b->right is black, d=c->left is red
                    if (c->left!=NULL && c->left->colour==1){
                        d=c->left;
                        d->colour=0;    
                        goto y;
                    
                    }
                    //b is the left child of a, a is black, b is red, c=b->right is black, d=c->right is red
                    else if(c->right!=NULL && c->right->colour==1){
                        d=c->right;
                        d->colour=0;
                        b->right=leftrotation(c);
                        b->right->parent=b;
                        c=b->right;
                        d=c->left;
                        goto y;
                        
                    }
                    //b is the left child of a, a is black, b is red, c=b->right is black, d= both c children are black
                    else{
                    
                        b->colour=0;
                        c->colour=1;
                        goto z;
                    
                        
                    }
                }
                
                
                // b is the left child of a, a is black, b is red, c=both children are black
                else {
                    b->colour=0;
                    return;
                
                }
                
            }
        
        } // a is black ends
    }
    
    // b is the right child of a
    else if (a->right==b){
                //b is the right child of a, a is red
        if (a->colour==1){
            //b is the right child of a, a is red, b is black
            if (b->colour==0){
                // b is the right child of a, a is red, b is black, c=b->left is red
                if (b->left!=NULL && b->left->colour==1){
                   // node <E> *w=a->parent;
                c=b->left;
                a->colour=0;
                b->colour=0;
                c->colour=1;
                
                z1: 
                node <E> *w=a->parent;
                 if(w==NULL){
                    a->right=rightrotation(b);
                    a->right->parent=a;
                    root=leftrotation(a);
                    root->parent=NULL;
                    return;
                }
                    
                else if((w->left)==a){
                    a->right=rightrotation(b);
                    a->right->parent=a;
                    w->left=leftrotation(a);
                    (w->left)->parent=w;
                    return;
                }
                    
                else{
                    a->right=rightrotation(b);
                    a->right->parent=a;
                    w->right=leftrotation(a);
                    (w->right)->parent=w;  
                    return;
                }
               
                }
                // b is the right child of a, a is red, b is black, c=b->right is red
                else if(b->right!=NULL && b->right->colour==1){
                //node <E> *w=a->parent;
                c=b->right;
                a->colour=0;
                b->colour=1;
                c->colour=0;
                
                y1: 
                node <E> *w=a->parent;
                
                
                if(w==NULL){
                    root=leftrotation(a);
                    root->parent=NULL;
                    return;
                }
                    
                else if((w->left)==a){
                    w->left=leftrotation(a);
                    (w->left)->parent=w;
                    return;
                }
                    
                else{
                    w->right=leftrotation(a);
                    (w->right)->parent=w;  
                    return;
                }
 
                
                }
                // b is the right child of a, a is red, b is black, both b children are black
                else{
                    b->colour=1;
                    a->colour=0;
                    return;
                
                } 
                
            }
        } // a is red ends
        
        // b is the right child of a, a is black
        else if (a->colour==0){
            if (b->colour==0){
                // b is the right child of a, a is black, b is black, c=b->left is red
                if (b->left!=NULL && b->left->colour==1){
                    c=b->left;
                    c->colour=0;
                    a->right=rightrotation(b);
                    a->right->parent=a;
                    b=a->right;
                    c=b->right;    
                    goto y1;
                    
                }
                // b is the right child of a, a is black, b is black, c=b->right is red
                else if(b->right!=NULL && b->right->colour==1){
                    c=b->right;
                    c->colour=0;
                    goto y1;
                    
                }
                // b is the right child of a, a is black, b is black, both b children are black
                else {
                    b->colour=1;
                   
                } 
                
            }
            //b is the right child of a, a is black, b is red
            else if (b->colour==1){
            
                //b is the right child of a, a is black, b is red, c=b->left is black
                if (b->left!=NULL && b->left->colour==0){
                    c=b->left;
                    //b is the right child of a, a is black, b is red, c=b->left is black, d=c->left is red
                    if (c->left!=NULL && c->left->colour==1){
                        d=c->left;
                        d->colour=0;    
                        b->left=rightrotation(c);
                        b->left->parent=b;
                        c=b->left;
                        d=c->right;
                        goto z1;
                      
                    }
                    //b is the right child of a, a is black, b is red, c=b->left is black, d=c->right is red
                    else if(c->right!=NULL && c->right->colour==1){
                        d=c->right;
                        d->colour=0;                        
                        goto z1;

                    }
                    //b is the right child of a, a is black, b is red, c=b->left is black, d= both c children are black
                    else{
                         b->colour=0;
                        c->colour=1;
                        goto y1;

                    }
                }
                                
                // b is the right child of a, a is black, b is red, c=both children are black
                else {
                    b->colour=0;
                    return;
                }
                
            }
        
        } // a is black ends
    }// b is the right child ends
 
 // Calculate
 // a,b,etc
 
 x=a;
 if (a==root)
    return;
 a=a->parent;
 if (a->left==x)
    b=a->right;
 else
    b=a->left;
 
 } // While loop ends
    
 
} // Remove ends

template <typename E>
void redblack <E> :: remove(int k){
    node <E> *x=search(k);
    remove(x);
}


template <typename E>
void redblack <E> :: dis(){
    display(root, 0);
    cout<<endl<<endl;
}


template <typename E>
void redblack <E> :: display(node <E> *ptr, int level)
    {
        int i;
        if (ptr!=NULL)
        {
            display(ptr->right, level + 1);
            cout<<("\n");
            if (ptr == root)
            cout<<"Root->";
            for (i = 0; i < level && ptr != root; i++)
                cout<<"        ";
            cout<< ptr->key<<",(";
            if (ptr->colour==0)
                cout<<"B)";
            else if (ptr->colour==1)
                cout<<"R)";
            display(ptr->left, level + 1);
        }
    }


template <typename E>
node <E> * redblack <E> :: leftrotation(node <E> *y){
    cout<<"Performing left rotation on "<<y->key<<endl;
    cout<<"Before rotation :\n";
    dis();

    node <E> *x=y->right;
    
    node <E> *t;
    if(x==NULL){
        t=NULL;
    }
    else{
        t=x->left;
    }
    
    x->left=y;
    if(t!=NULL)
        t->parent=y;
    y->parent=x;
    y->right=t;

    cout<<"After rotation :\n";    
    dis();
    return x;
}



template <typename E>
node <E> * redblack <E> :: rightrotation(node <E> *y){
    cout<<"Performing right rotation on "<<y->key<<endl;
    cout<<"Before rotation :\n";
    dis();

    node <E> *x=y->left;
    
    node <E> *t;
    if(x==NULL){
        t=NULL;
    }
    else{
        t=x->right;
    }
    

    x->right=y;
    if(t!=NULL)
        t->parent=y;
    y->parent=x;
    y->left=t;

    cout<<"After rotation :\n";
    dis();
    return x;

}


template <typename E>
node <E> * redblack <E> :: bstinsertion(int k,E v){
    node <E> *x=root;
    node <E> *y=NULL;
    
    while(x!=NULL){
        if(k==(x->key)){
            x->data=v;
            return NULL;
        }
        else if(k<(x->key)){
            y=x;
            x=x->left;
        }
        else{
            y=x;
            x=x->right;
        }
    }
    
    //Make root
    if(y==NULL){
        x= new node <E>;
        x->key=k;
        x->data=v;
        
        root=x;
        x->parent=NULL;
    }

    //Make a new node and insert there
    else if(x==NULL){
        x= new node <E>;
        x->key=k;
        x->data=v;
        
        x->parent=y;
        if(k<(y->key))
            y->left=x;
        else
            y->right=x;        
    }
    
    else{
        node <E> *t=new node <E>;
        t->key=-32768;
        return t;
    }
    return x;
}


template <typename E>
node <E> * redblack <E> :: insert(int k,E  v){
    node <E> *x=bstinsertion(k,v);
    
    if (x->key==-32768)
        return x;
        
    x->colour=1;
    node <E> *y=x;
    node <E> *a=x->parent;
    
    // First entry, no parent of x
    if (a==NULL){
        x->colour=0;
        return y;
        }
        
    // Black parent no problem
    if (a->colour==0)
        return y;
    
    //Red parent problem
    while(1){
    a=x->parent;
    
    // Black parent no problem
    if (a->colour==0)
        return y;
    
    if (a->colour==1){
        node <E> *b=a->parent;
        node <E> *c;        
        node <E> *w=b->parent;
        
        // a is the left child of b
        if (b->left == a){
            
            c=b->right;
            if (c==NULL){
                c= new node <E>;
                c->colour=0;
                }
            // a is the left child of b and c is black colour
            
            // the key is the right child of a
            if (a->right==x){
                b->left=leftrotation(a);
                b->left->parent=b;
                x=a;
                a=b->left;
            }
            
            if (c->colour==0){
                if(w==NULL){
                    root=rightrotation(b);
                    root->parent=NULL;
                    a->colour=0;
                    b->colour=1;
                    return y;
                }
                    
                if((w->left)==b){
                    w->left=rightrotation(b);
                    (w->left)->parent=w;
                    a->colour=0;
                    b->colour=1;
                    return y;
                }
                    
                else{
                    w->right=rightrotation(b);
                    (w->right)->parent=w;  
                    a->colour=0;
                    b->colour=1;
                    return y;   
                }
            
            }
            
            // a is the left child of b and c is red coloured
            else{
                a->colour=0;
                b->colour=1;
                c->colour=0;
                
                if (b->parent ==NULL){
                    b->colour=0;
                    return y;
                }
                x=b;
            } 
            
        }
        
        // a is the right child of b
        else{
            c=b->left;
            
            // the key is the left child of a
            if (a->left==x){
                b->right=rightrotation(a);
                b->right->parent=b;
                x=a;
                a=b->right;
            }
            
            if (c==NULL){
                c= new node <E>;
                c->colour=0;
                }
            //a is the right child of b and c is black colour
            if (c->colour==0){
                if(w==NULL){
                    root=leftrotation(b);
                    root->parent=NULL;
                    a->colour=0;
                    b->colour=1;
                    return y;
                }
                    
                if((w->left)==b){
                    w->left=leftrotation(b);
                    (w->left)->parent=w;
                    a->colour=0;
                    b->colour=1;
                    return y;
                }
                    
                else{
                    w->right=leftrotation(b);
                    (w->right)->parent=w;  
                    a->colour=0;
                    b->colour=1;
                    return y;   
                }
            
            
            }
            
            //a is the right child of b and c is red coloured
            else{
                a->colour=0;
                b->colour=1;
                c->colour=0;
                
                if (b->parent ==NULL){
                    b->colour=0;
                    return y;
                }
                x=b;  
            } 
            
        }
    
    }
    }
    


        
return y;

}

    
#endif // REDBLACK_H
