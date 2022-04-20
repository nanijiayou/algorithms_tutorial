#include <iostream>
#include <vector>
using namespace std;

void printArr(vector<int>& A) {
    vector<int>::iterator iter = A.begin();
    while(iter != A.end()) {
        cout << *iter;
        iter++;
    }
    cout << endl;
}

int partition(vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; ++j) {
        if(A[j] <= x) swap(A[++i], A[j]);
    }
    swap(A[i+1], A[r]);
    return i + 1;
}

int randomPartition(vector<int> &A, int p, int r) { 
    int i = rand() % (r - p + 1) + p;
    swap(A[r], A[i]);
    return partition(A, p, r);
}

void quickSort(vector<int> &A, int p, int r) {
    if(p < r) {
        int pivot = randomPartition(A, p, r);
        quickSort(A, p, pivot - 1);
        quickSort(A, pivot + 1, r);
    }
}

void sort(vector<int> &A) {
    int n = A.size();
    quickSort(A, 0, n-1);
}

int main() {
    vector<int> test { 1, 7, 3, 5, 9, 6, 8};
    sort(test); 
    printArr(test);
    return 0;
}