#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

void generateArray(int n, string name){
    ofstream outFile(name);
    if(!outFile){
        cout<<"Error creating file"<<endl;
    }
    else{
        for(int i=0; i<n; i++){
            outFile<<(rand()%n)<<" ";
        }
    }
    outFile.close();
}

int main(){
    string folder1 = "RandomArrays";
    system(("mkdir -p " + folder1).c_str());
    srand(time(0));
    for(int i=0; i<=1000000; i+=1000){
        string name = folder1 +"/" + to_string(i) + ".txt";
        // uncomment the line below
        // generateArray(i, name);
        cout<<"generated array of size "<<i<<endl;
    }
    cout<<"complete"<<endl;
    return 0;
}