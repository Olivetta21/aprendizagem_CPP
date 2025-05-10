#include <iostream>
using namespace std;

void testar(int t){
    int* vet = new int[t];
    
    for (int i=0; i<t; i++){
        vet[i]=(i+1)*10;
    }
    
    for (int i=0; i<t; i++){
        cout<<vet[i]<<"\n";
    }
    
    delete[] vet;
    vet = nullptr;
}

int main (){
    int t;
    cout<<"tamanwwho do vetor: ";
    cin>>t;
    testar(t);
    


}