#include "redblack.h"
#include <stdlib.h>

using namespace std;

int main(){
    redblack <int> M;
    int ans,k,a,b,i;
    int v;
    vector <int> u;

    for(int i=0;i<30;i++){
         M.insert(i,i);
    }
    M.dis();


while(ans!=9){     
    cout<<"1. Insert element\n2. Delete a key\n3. Search\n";
    cout<<"4. Number of Leaves\n5. Height of the tree\n6. Black Height of the tree\n";
    cout<<"7. List of Keys between a and b\n8. Display tree\n9. Exit\n";
                
    cout<<"Enter your choice: \n";
    cin>>ans;
    
    switch(ans){

    case 1:
        cout<<"Enter key and value to be inserted\n";
        cin>>k;
        cin>>v;
        M.insert(k,v);
        M.dis();
        break;
    case 2:
        cout<<"Enter a key to be deleted\n";
        cin>>k;
        M.remove(k);
        M.dis();
        break;
    case 3:
        cout<<"Enter a key to be searched\n";
        cin>>k;
        cout<<M.search(k)->key<<","<<M.search(k)->data<<endl;
        break;
    case 4:
        cout<<M.numberofleaves()<<endl;
        break;
    case 5:
        cout<<M.height()<<endl;
        break;
    case 6:
        cout<<M.bheight()<<endl;
        break;
    case 7:
        cout<<"Enter a and b:\n";
        cin>>a>>b;
        u=M.list(a,b);    
        for(i=0;i<u.size();i++)
        cout<<u[i]<<" ";
        cout<<endl;    
        break;
    case 8:
        M.dis();
        break;
    case 9:
        break;
    default :
        cout<<"Enter correct option\n";
        break;                
    }
    }


}
