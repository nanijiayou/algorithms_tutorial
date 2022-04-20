#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; ++j) {
        if(A[j] <= x) swap(A[++i], A[j]);
    }
    swap(A[i+1], A[r]);
    return i + 1;
}

int randomPartiton(vector<int>& A, int p, int r) {
    int i = rand() % (r - p + 1) + p;
    swap(A[i], A[r]);
    return partition(A, p, r);
}

void randomQuickSort(vector<int>& A, int p, int r) {
    if(p < r) {
        int q = randomPartiton(A, p, r);
        randomQuickSort(A, p, q - 1);
        randomQuickSort(A, q + 1, r);
    }
}

int main() {
    vector<int> test { 1, 3, 7, 5, 9 };
    int n = test.size();
    randomQuickSort(test, 0, n-1);
    return 0;
}