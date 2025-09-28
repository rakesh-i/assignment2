#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<chrono>
#include<string>
#include<algorithm>
using namespace std;
namespace fs = std::filesystem;

void bubbleSort(vector<int>&a){
    int n = a.size();
    for(int i=0; i<n; i++){
        int swapped = 0;
        for(int j=1; j<n-i; j++){
            if(a[j-1]>a[j]){
                swap(a[j-1], a[j]);
                swapped = 1;
            }
        }
        if(!swapped){
            break;
        }
    }
}

void insertionSort(vector<int>&a){
    for (int i = 1; i < a.size(); ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

void merge(vector<int>&a, int left, int mid, int right){
    int n1 = mid - left+1;
    int n2 = right - mid; 

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>&a, int start, int end){
    if(start>=end){
        return;
    }
    int mid = start+(end-start)/2;
    mergeSort(a, start ,mid);
    mergeSort(a, mid+1, end);
    merge(a, start, mid, end);
}

void heapify(vector<int>& a, int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest]){
        largest = l;
    }

    if (r < n && a[r] > a[largest]){
        largest = r;
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a){
    int n = a.size();

    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

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

int partition(vector<int>& a, int low, int high, int variant) {
    int pivotIdx;
    if (variant == 1){ 
        pivotIdx = high;
    } 
    else if(variant == 2){
        pivotIdx = low;
    } 
    else{ 
        pivotIdx = low + rand() % (high - low + 1);
    }

    swap(a[pivotIdx], a[high]);
    int pivot = a[high];

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<int>& a, int low, int high, int variant) {
    if (low < high) {
        int pi = partition(a, low, high, variant);
        quickSort(a, low, pi - 1, variant);
        quickSort(a, pi + 1, high, variant);
    }
}


vector<int> readArrayFile(string name){
    ifstream inFile(name);
    if (!inFile) {
        cout<<"Error opening file!"<<endl;
    }

    vector<int> a;
    int x;
    while (inFile>>x) {
        a.push_back(x);
        
    }
    cout<<endl;
    inFile.close();
    return a;
}

long analyseAlgo(vector<int>&a, int algo){
    int n = a.size();
    switch (algo)
    {
    case 1:{//bubble sort
        auto timeStart = chrono::high_resolution_clock::now();
        bubbleSort(a);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);

        return duration.count();    
        break;
    }
    case 2:{//insertion sort
        auto timeStart = chrono::high_resolution_clock::now();
        insertionSort(a);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);

        return duration.count();
        break;
    }
    case 3:{//merge sort
        auto timeStart = chrono::high_resolution_clock::now();
        mergeSort(a, 0, n-1);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);

        return duration.count();
        break;
    }
    
    case 4:{//heap sort
        auto timeStart = chrono::high_resolution_clock::now();
        heapSort(a);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);

        return duration.count();
        break;
    }
    case 5:{//radix sort
        auto timeStart = chrono::high_resolution_clock::now();
        radixSort(a);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);

        return duration.count();
        break;
    }
    case 6:{//quick sort last ele pivot
        auto timeStart = chrono::high_resolution_clock::now();
        quickSort(a, 0, n-1, 1);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);
        return duration.count();
        break;
    }
    case 7:{//quick sort first ele pivot
        auto timeStart = chrono::high_resolution_clock::now();
        quickSort(a, 0, n-1, 2);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);

        return duration.count();
        break;
    }
    case 8:{//quick sort random ele pivot
        auto timeStart = chrono::high_resolution_clock::now();
        quickSort(a, 0, n-1, 3);
        auto timeEnd = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);

        return duration.count();
        break;
    }
    default:
        break;
    }

}

void printArray(vector<int>&a){
    for(auto i: a){
        cout<<i<<" ";
    }
    cout<<endl;
}

void generateArray(vector<int> &a, string name){
    ofstream outFile(name);
    if(!outFile){
        cout<<"Error creating file"<<endl;
    }
    else{
        for(int i=0; i<a.size(); i++){
            outFile<<a[i]<<" ";
        }
    }
    outFile.close();
}

void reverse(vector<int>&a){
    int n = a.size();
    for(int i=0; i<n/2; i++){
        swap(a[i], a[n-1-i]);
    }
}


int main() {
    srand(time(0));

    vector<pair<string, string>> arrayTypes = {
        {"RandomArrays", "Random"},
        {"SortedArrays", "Sorted"},
        {"ReversedSortedArrays", "Reversed"}
    };

    ofstream outFiles[8][3];
    for (int algoID = 1; algoID <= 8; algoID++) {
        for (int t = 0; t < arrayTypes.size(); t++) {
            string filename = "Algo" + to_string(algoID) + "_" + arrayTypes[t].second + ".csv";
            outFiles[algoID - 1][t].open(filename);
            outFiles[algoID - 1][t]<<"InputSize,Time(us)\n";
        }
    }

    for (int t = 0; t < arrayTypes.size(); t++) {
        string folder = arrayTypes[t].first;
        cout<< "Processing folder: "<<folder<<endl;

        vector<pair<int, string>> files;
        try {
            for (const auto& entry : fs::directory_iterator(folder)) {
                if (entry.is_regular_file()) {
                    string pathName = folder + "/" + entry.path().filename().string();
                    string fileName = entry.path().filename().string();
                    fileName.erase(fileName.size() - 4);
                    int fileNum = stoi(fileName);
                    files.push_back({fileNum, pathName});
                }
            }
            sort(files.begin(), files.end());

            for (const auto& name : files) {
                vector<int> a = readArrayFile(name.second);
                int n = a.size();

                for (int algoID = 1; algoID <= 8; algoID++) {
                    if ((algoID == 1 || algoID == 2) && n > 15000&&arrayTypes[t].second!="Sorted") continue;
                    // if ((algoID == 1 || algoID == 2) && n > 15000&&arrayTypes[t].second=="Sorted") continue;
                    if ((algoID == 6 || algoID == 7) &&
                        (arrayTypes[t].second != "Random") && n > 15000) continue;

                    long long totalTime = 0;

                    for (int run = 0; run < 3; run++) {
                        vector<int> temp = a; 
                        int time = analyseAlgo(temp, algoID);
                        totalTime += time;
                    }
                    int avgTime = totalTime / 3;

                    cout<<"Algo "<<algoID<<" on"<<n<<" elements ("<< arrayTypes[t].second <<") avg time: "<<avgTime<<" us"<<endl;

                    outFiles[algoID - 1][t]<<n<<","<<avgTime<<"\n";
                }
            }

        } catch (const std::exception& e) {
            cerr<<"Error: "<<e.what()<<endl;
        }
    }

    for (int algoID = 1; algoID <= 8; algoID++)
        for (int t = 0; t < arrayTypes.size(); t++)
            outFiles[algoID - 1][t].close();

    cout<<"Complete"<<endl;
    return 0;
}