#include "avltree.h"
#include <stdlib.h>

using namespace std;

int main(){
    avltree <int> M;
    int ans,k;
    int v;
    
    for(int i=0;i<30;i++){
         M.put(i,i);
    }
    M.dis();

while(ans!=13){     
    cout<<"\n\n1. First Entry\n2. Last Entry\n3. Ceiling Entry of k\n";
    cout<<"4. Floor Entry of k\n5. Lower Entry of k\n6. Higher Entry of k\n";
    cout<<"7. Size of the tree\n8. Is tree Empty?\n9. Find an element\n";
    cout<<"10. Insert element\n11. Delete a key\n12. Display\n13. Exit\n";
                
    cout<<"Enter your choice: \n";
    cin>>ans;
    
    switch(ans){
    case 1:
        cout<<(*(M.firstEntry()))->key<<endl;
        break;
    case 2:
        cout<<(*(M.lastEntry()))->key<<endl;
        break;
    case 3:
        cout<<"Enter a key\n";
        cin>>k;
        cout<<(*(M.ceilingEntry(k)))->key<<endl;
        break;
    case 4:
        cout<<"Enter a key\n";
        cin>>k;
        cout<<(*(M.floorEntry(k)))->key<<endl;
        break;
    case 5:
        cout<<"Enter a key\n";
        cin>>k;
        cout<<(*(M.lowerEntry(k)))->key<<endl;
        break;
    case 6:
        cout<<"Enter a key\n";
        cin>>k;
        cout<<(*(M.higherEntry(k)))->key<<endl;
        break;
    case 7:
        cout<<M.size()<<endl;        
        break;
    case 8:
        if(!M.empty())
            cout<<"Tree is not empty\n";    
        break;
    case 9:
        cout<<"Enter a key to be searched\n";
        cin>>k;
        cout<<(*(M.find(k)))->key<<","<<(*(M.find(k)))->data<<endl;
        break;
    case 10:
        cout<<"Enter key and value\n";
        cin>>k;
        cin>>v;
        M.put(k,v);
        M.dis();
        break;
    case 11:
        cout<<"Enter a key to be deleted\n";
        cin>>k;
        M.erase(k);
        M.dis();
        break;
    case 12:
        M.dis();
        break;
    case 13:
        break;
    default :
        cout<<"Enter correct option\n";
        break;                
    }
    }

}
