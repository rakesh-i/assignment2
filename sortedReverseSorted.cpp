#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

void radixSort(vector<int>& arr) {
    int n = arr.size();
    if(n == 0) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    for(int exp = 1; maxVal/exp > 0; exp *= 10) {
        vector<int> output(n);
        int count[10] = {0};

        for(int i = 0; i < n; i++)
            count[(arr[i]/exp)%10]++;

        for(int i = 1; i < 10; i++)
            count[i] += count[i-1];

        for(int i = n-1; i >= 0; i--) {
            int digit = (arr[i]/exp)%10;
            output[count[digit]-1] = arr[i];
            count[digit]--;
        }

        arr = output;
    }
}


vector<int> readArrayFile(const string& filename) {
    ifstream inFile(filename);
    vector<int> arr;
    int x;
    while(inFile >> x){
        arr.push_back(x);
    }
    return arr;
}

void writeArrayFile(const vector<int>& arr, const string& filename) {
    ofstream outFile(filename);
    for(int x : arr){
        outFile<<x<< " ";
    }
    outFile.close();
}

int main() {
    string randomFolder = "RandomArrays";
    string sortedFolder = "SortedArrays";
    string reversedFolder = "ReversedSortedArrays";

    system(("mkdir -p " + sortedFolder).c_str());
    system(("mkdir -p " + reversedFolder).c_str());

    for(int i = 0; i <= 10000; i += 1000){
        string randFile = randomFolder + "/" + to_string(i) + ".txt";
        vector<int> arr = readArrayFile(randFile);

        radixSort(arr);

        string sortedFile = sortedFolder + "/" + to_string(i) + ".txt";
        writeArrayFile(arr, sortedFile);

        vector<int> revArr = arr;
        reverse(revArr.begin(), revArr.end());
        string revFile = reversedFolder + "/" + to_string(i) + ".txt";
        writeArrayFile(revArr, revFile);

        cout<<"generated for n = "<<i<<endl;
    }

    cout<<"generated successfully"<<endl;
    return 0;
}
