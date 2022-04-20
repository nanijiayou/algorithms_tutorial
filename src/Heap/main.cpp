#include <iostream>
#include <vector>

using namespace std;
int parent(int i) {
    return (i - 1) / 2;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

void heapify(vector<int> &A, int heapSize, int i) {
    int l = left(i);
    int r = right(i);

    int largest = i;
    if(l < heapSize && A[l] > A[i]) largest = l;
    if(r < heapSize && A[r] > A[largest]) largest = r;

    cout<<"heapSize=" << heapSize << " i=" << i << " left=" << l << " right=" << r << " largest=" << largest << endl;

    if(largest != i) {
        swap(A[i], A[largest]);
        heapify(A, heapSize, largest);
    }
}

void buildMaxHeap(vector<int> &A) {
    int len = A.size();
    for (int i = len / 2 - 1; i >= 0; --i) {
        heapify(A, len, i);
    }
}

void heapSort(vector<int> &A) {
    buildMaxHeap(A);
    int n = A.size();
    for(int i = n - 1; i >= 0; --i) {
        swap(A[i], A[0]);
        heapify(A, i, 0);
    }
}

int main() {
    vector<int> test { 1, 3, 7, 5, 9 };
    heapSort(test);
    return 0;
}
