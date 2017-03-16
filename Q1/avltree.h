
#ifndef AVLTREE_H
#define AVLTREE_H
#include "node.h"
#include "Iterator.h"

template <typename E>
class avltree {
public:
    
    Iterator<E> firstEntry();
    Iterator<E> lastEntry();
    Iterator<E> ceilingEntry (int k);
    Iterator<E> floorEntry (int k);
    Iterator<E> lowerEntry (int k);
    Iterator<E> higherEntry (int k);
    int size();
    bool empty();
    Iterator <E> find(int k);
    node <E> * put(int k,E v);
    void erase (node <E> * p);
    void erase (int k);    
    
    
    // Helper functions
    node <E> * max(node <E> *x);
    node <E> * min(node <E> *x);
    node <E> * fin(int k);
    node <E> * predecessor (node <E> *x);
    node <E> *successor (node <E> *x);
    int s(node <E> *t);
    node <E> * leftrotation(node <E> *y);
    node <E> * rightrotation(node <E> *y);
    node <E> * bstinsertion(int k,E v);
    node <E> * bstdeletion(int k);
    void display(node <E> *ptr, int level);
    void dis();
    int hfromleftright(node <E> * x);
    node <E> * largerheightchild(node <E> *x);
    int heightbalance(node <E> * x);
    node <E> * unbalancedgrandchild(node <E> * x);
    node <E> * unbalancedgrandchilddel(node <E> * x);
    avltree();
    virtual ~avltree();

protected:
private:
    node <E> *root;

};

template <typename E>
avltree <E> :: avltree(){
    root=NULL;
}

template <typename E>
avltree <E> :: ~avltree(){

}


template <typename E>
node <E> * avltree <E> :: fin(int k){
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
    return end;
}

template <typename E>
Iterator     <E> avltree <E> :: find(int k){
    node <E> *t=root;
    while (t!=NULL){
        if ((t->key)==k)
            return Iterator<E>(t);
        else if (k<(t->key))
            t=t->left;
        else
            t=t->right;
    }
    node <E> *end = new node <E>;
    end->key=-32768;
    return Iterator<E>(end);
}

template <typename E>
node <E> * avltree <E> :: min(node <E> *x){
    while (x->left!=NULL)
        x=x->left;
        
    return x;
}

template <typename E>
node <E> * avltree <E> :: max(node <E> *x){
    while (x->right!=NULL)
        x=x->right;
        
    return x;
}

template <typename E>
node <E> * avltree <E> :: successor(node <E> *x){
    if (x->right!=NULL)
     return min(x->right);
     
    node <E> *y=x->parent;
    while (y != NULL && x == y->right){
        x = y;
        y = y->parent;
        return y;
    }
    return y;
}

template <typename E>
node <E> * avltree <E> :: predecessor (node <E> *x){
    if (x->left!=NULL)
     return max(x->left);
     
    node <E> *y=x->parent;
    while (y != NULL && x == y->left){
        x = y;
        y = y->parent;
        return y;
    }
    return y;
}

template <typename E>
Iterator<E> avltree <E> :: firstEntry(){
    if (root== NULL){
        node <E> *end = new node <E>;
        end->key=-32768;
        return Iterator<E>(end);
    }
    
    node <E> *t=min (root);
    return Iterator<E>(t);
}

template <typename E>
Iterator<E> avltree <E> :: lastEntry(){
    if (root== NULL){
        node <E> *end = new node <E>;
        end->key=-32768;
        return Iterator<E>(end);
    }
    
    node <E> *t=max (root);
    return Iterator<E>(t);
}

template <typename E>
Iterator<E> avltree <E> :: ceilingEntry (int k){
    node <E> * t=fin(k);
    if (t->key == k)
        return Iterator<E>(t);
    else
        return Iterator<E>(higherEntry(k));
}

template <typename E>
Iterator<E> avltree <E> :: floorEntry (int k){
    node <E> * t=fin(k);
    if (t->key == k)
        return Iterator<E>(t);
    else
        return Iterator<E>(lowerEntry(k));        
}

template <typename E>
Iterator <E> avltree <E> :: lowerEntry (int k){
    E q;
    node <E> * t=fin(k);
    node <E> *u;
    
    if (t->key==-32768){
    t=put(k,q);
    u=predecessor(t);
    erase(t);
    }
    else{
    u=predecessor(t);
    }

    if (u == NULL){
        node <E> *end = new node <E>;
        end->key=-32768;
        return Iterator<E>(end);
    }
    
    return Iterator<E>(u);
}

template <typename E>
Iterator <E> avltree <E> :: higherEntry (int k){
    E q;

    node <E> * t=fin(k);
    node <E> *u;
    
    if (t->key==-32768){
    t=put(k,q);
    u=successor(t);
    erase(t);
    }
    else{
    u=successor(t);
    }

    if (u == NULL){
        node <E> *end = new node <E>;
        end->key=-32768;
        return Iterator<E>(end);
    }
    
    return Iterator<E>(u);
}

template <typename E>
int avltree <E> :: size(){
   return s(root); 
}

template <typename E>
int avltree <E> :: s(node <E> *t){
    if (t==NULL)
        return 0;
    
    return 1+ s(t->left)+s(t->right);
}


template <typename E>
bool avltree <E> :: empty(){
    if (root==NULL)
        return true;
    else
        return false;
}



template <typename E>
void avltree <E> :: erase(node <E> * p) {
    node <E> *z;
    z= bstdeletion(p->key);

    if (z==NULL || z->key==-32768)
        return;
 
    while (1){
   
    node <E> *x= unbalancedgrandchilddel(z);
   
    if (x==NULL){
        return;
        }
        
    node <E> *y=x->parent;
    z=y->parent;
    node <E> *w=z->parent;   
    
        
    if((z->left)==y){
        if((y->left)==x){
            // Case 0
            if(w==NULL){
                root=rightrotation(z);
                root->parent=NULL;
                z=root;
            }
                
            else if((w->left)==z){
                w->left=z=rightrotation(z);
                (w->left)->parent=w;
            }
                
            else{
                w->right=z=rightrotation(z);
                (w->right)->parent=w;  
            }
            
            
        }
        
        else if((y->right)==x){
            // Case 2
            if(w==NULL){
                z->left=leftrotation(y);
                (z->left)->parent=z;
                root=z=rightrotation(z);
                root->parent=NULL;
            }    
                
            else if((w->left)==z){
                z->left=leftrotation(y);
                (z->left)->parent=z;
                w->left=z=rightrotation(z);
                (w->left)->parent=w;
            }
                
            else{
                z->left=leftrotation(y);
                (z->left)->parent=z;
                w->right=z=rightrotation(z);
                (w->right)->parent=w;    
            }            
        }
        
    }
    
    else if ((z->right)==y){
        if((y->left)==x){
            // Case 3
            
            if(w==NULL){
                z->right=rightrotation(y);
                (z->right)->parent=z;
                root=z=leftrotation(z);
                z->parent=NULL;
            }    
             
            else if((w->left)==z){
                z->right=rightrotation(y);
                (z->right)->parent=z;
                w->left=z=leftrotation(z);
                (w->left)->parent=w;
            }
                
            else{
                z->right=rightrotation(y);
                (z->right)->parent=z;
                w->right=z=leftrotation(z);
                (w->right)->parent=w;     
            }
        }
        
        else if((y->right)==x){
            // Case 1
            if(w==NULL){
                root=z=leftrotation(z);
                z->parent=NULL;
            }
            
            else if((w->left)==z){
                w->left=z=leftrotation(z);
                (w->left)->parent=w;
            }
                
            else{
                w->right=z=leftrotation(z);
                (w->right)->parent=w;   
            }
        }
        
    }
    
 }   
 
}

template <typename E>
void avltree <E> :: erase(int k){
    node <E> *x=fin(k);
    erase(x);
}


template <typename E>
void avltree <E> :: dis(){
    display(root, 0);
    cout<<endl<<endl;
}


template <typename E>
void avltree <E> :: display(node <E> *ptr, int level)
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
            cout<< ptr->key<<","<<ptr->data;
            display(ptr->left, level + 1);
        }
    }


template <typename E>
int avltree <E> :: hfromleftright(node <E> *x){
    if(x==NULL)
        return 0;
        
    int left,right;
    if(x->left==NULL)
        left=0;
    else
        left=(x->left)->height;

    if(x->right==NULL)
        right=0;
    else
        right=(x->right)->height;
       
    if(left>=right)
        return 1+left;
    else
        return 1+right;   
}

template <typename E>
node <E> * avltree <E> :: largerheightchild(node <E> *x){
    node <E> *t= new node <E>;
       
    if(x==NULL)
        return t;
        
    int left,right;
    
    if(x->left==NULL)
        left=0;
    else
        left=(x->left)->height;

    if(x->right==NULL)
        right=0;
    else
        right=(x->right)->height;
       
    if (left==0 && right==0){
        return t;   
        }

    if(left>right){
        return x->left;
        }
    else if (right>left)
        return x->right;
    else {
        if (((x->parent->left) != NULL ) && ((x->parent->left) == x))
            return x->left;
        else if (((x->parent->right) != NULL ) && ((x->parent->right)==x))
            return x->right;
    }       
}

template <typename E>
int avltree <E> :: heightbalance(node <E> *x){
    if(x==NULL)
        return 0;
        
    int left,right;
    if(x->left==NULL)
        left=0;
    else
        left=(x->left)->height;

    if(x->right==NULL)
        right=0;
    else
        right=(x->right)->height;
       
    return left-right;
}

template <typename E>
node <E> * avltree <E> :: leftrotation(node <E> *y){
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

    y->height=hfromleftright(y);
    x->height=hfromleftright(x);

    cout<<"After rotation :\n";    
    dis();
    return x;
}



template <typename E>
node <E> * avltree <E> :: rightrotation(node <E> *y){
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

    y->height=hfromleftright(y);
    x->height=hfromleftright(x);

    cout<<"After rotation :\n";
    dis();
    return x;
}


template <typename E>
node <E> * avltree <E> :: bstinsertion(int k,E v){
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
    return x;
}


template <typename E>
node <E> * avltree <E> :: bstdeletion(int k){
    node <E> *x=root;
    
    while(x!=NULL){
        if(k==(x->key)){
            break;
        }
        else if(k<(x->key)){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    
    if(x==NULL){
        node <E> *t=new node <E>;
        cout<<"Item not found \n";      
        return t;
    }    
    
m:    node <E> * y = x->parent;
    
    // Removing a leaf node
    if (x->left==NULL && x->right==NULL){

        if (y==NULL){
        delete x;
        root=NULL;
        return NULL;
        }
        
        
        if(y->left == x)
            y->left=NULL;
        else
            y->right=NULL;
        
        delete x;
        return y;    
    }
    
    // Removing a node with a single child
    if((x->left==NULL && x->right!=NULL) || (x->left!=NULL && x->right==NULL)){
        // Right leaf present, no left leaf
        if (x->left==NULL && x->right!=NULL){
            
            if (y!=NULL){
                if (y->left == x){
                
                    y->left=x->right;
                    x->right->parent=y;
                    delete x;  
                    return y;
                }
                
                else{
                    y->right=x->right;
                    x->right->parent=y;
                    delete x;
                    return y;
                }
           }
           else{
                x->right->parent=y;
                delete x;  
                return y;
           }     
        }
        
        // Left leaf present, no right leaf
        else{
        if(y!=NULL){
            if (y->left == x){
            if (y!=NULL)
                y->left=x->left;
                x->left->parent=y;
                delete x;
                return y;
            }
            
            else{
            if (y!=NULL)
                y->right=x->left;
                x->left->parent=y;
                delete x;
                
                return y;
            }
            }
            else{
                x->left->parent=y;
                delete x;
                return y;
            }
        }
        
    }
    
    // Removing node with two children
    if (x->left!=NULL && x->right!=NULL) {    
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
}


template <typename E>
node <E> * avltree <E> :: unbalancedgrandchilddel(node <E> * x){
    int balance;
    node <E> * t=x;
    while(t!=NULL){
        t->height=hfromleftright(t);
        t=t->parent;
    }
    
    node <E> *y;
    node <E> *z=x;
    while (z!=NULL){

        balance=heightbalance(z);
        if(balance>1 || balance< -1){
            y=largerheightchild(z);
            x=largerheightchild(y);
            return x;
        }
        z=z->parent;
    }

    return NULL;

}



template <typename E>
node <E> * avltree <E> :: unbalancedgrandchild(node <E> * x){
    int balance;
    node <E> * t=x;
    while(t!=NULL){
        t->height=hfromleftright(t);
        t=t->parent;
    }
    node <E> *y;
    if(x==NULL){
        y=NULL;
    }
    else{
        y=x->parent;
    }
    node <E> *z;
    if(y==NULL){
        z=NULL;
    }
    else{
        z=y->parent;
    }

    while (z!=NULL){

        balance=heightbalance(z);
        if(balance>1 || balance< -1){
            return x;
        }
        x=y;
        y=z;
        z=z->parent;
    }
    
    return NULL;

}

template <typename E>
node <E> * avltree <E> :: put(int k,E  v){
    node <E> *t=bstinsertion(k,v);
 
    node <E> *x= unbalancedgrandchild(t);
    if (x==NULL){
            return t;
        }
        
        
    node <E> *y=x->parent;
    
    node <E> *z=y->parent;
    node <E> *w=z->parent;
    

    
    if((z->left)==y){
        if((y->left)==x){
            // Case 0
            if(w==NULL){
                root=rightrotation(z);
                root->parent=NULL;
                return t;
            }
                
            if((w->left)==z){
                w->left=rightrotation(z);
                (w->left)->parent=w;
                return t;
            }
                
            else{
                w->right=rightrotation(z);
                (w->right)->parent=w;  
                return t;   
            }
            
            
        }
        
        else if((y->right)==x){
            // Case 2
            if(w==NULL){
                z->left=leftrotation(y);
                (z->left)->parent=z;
                root=rightrotation(z);
                root->parent=NULL;
                return t;
            }    
                
            if((w->left)==z){
                z->left=leftrotation(y);
                (z->left)->parent=z;
                w->left=rightrotation(z);
                (w->left)->parent=w;
                return t;
            }
                
            else{
                z->left=leftrotation(y);
                (z->left)->parent=z;
                w->right=rightrotation(z);
                (w->right)->parent=w;    
                return t; 
            }            
        }
        
    }
    
    else if ((z->right)==y){
        if((y->left)==x){
            // Case 3
            
            if(w==NULL){
                z->right=rightrotation(y);
                (z->right)->parent=z;
                root=leftrotation(z);
                root->parent=NULL;
                return t;
            }    
             
            if((w->left)==z){
                z->right=rightrotation(y);
                (z->right)->parent=z;
                w->left=leftrotation(z);
                (w->left)->parent=w;
                return t;
            }
                
            else{
                z->right=rightrotation(y);
                (z->right)->parent=z;
                w->right=leftrotation(z);
                (w->right)->parent=w;     
                return t;
            }
        }
        
        else if((y->right)==x){
            // Case 1
            if(w==NULL){
                root=leftrotation(z);
                root->parent=NULL;
                return t;
            }
            
            if((w->left)==z){
                w->left=leftrotation(z);
                (w->left)->parent=w;
                return t;
            }
                
            else{
                w->right=leftrotation(z);
                (w->right)->parent=w;   
                return t;  
            }
        }
        
    }
    

}

    
#endif // AVLTREE_H
