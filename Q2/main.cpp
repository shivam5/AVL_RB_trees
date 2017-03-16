#include "avltree.h"
#include <fstream>

using namespace std;

int main(){
    avltree <int> M;
    
   ifstream fin;
    int n, target,x,i;
    
    cout<<"Enter how many nunmbers\n";
    cin>>n;
    cout<<"Enter target sum\n";
    cin>>target;
        
    fin.open("input.txt");
    
    for(i=0;i<n;i++){
        fin>>x;
        cout<<x<<endl;
        M.put(x,x);
    }
    
    fin.close();

    M.dis();    


    if (!M.targetsum(target)){
        cout<<"No such pair found with target = "<<target;
    }
}
