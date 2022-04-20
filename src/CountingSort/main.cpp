/**
 COUNTINSORT(A, B, k)
    let C be a new Array

    for i = 0 to k
        C[i] = 0
    
    for j = 1 to A.length
        C[A[j]] = C[A[j]] + 1

    for i = 1 to k
        C[i] = C[i-1] + C[i]

    for j = A.length downto 1
        B[C[A[j]]] = A[j]
        C[A[j]] = C[A[j]] - 1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printArr(vector<int>& A) {
    for(const auto & k : A) {
        std::cout << k << " ";
    }
    std::cout << std::endl;
}

void countingSort(vector<int>& A, vector<int>& B, int k) {
    vector<int> C(k, 0);

    for(int i = 0; i < A.size(); ++i) {
        C[A[i]] = C[A[i]] + 1;
    }

    printArr(C);

    for(int i = 1; i < k; ++i) {
        C[i] = C[i-1] + C[i];
    }

    printArr(C);

    for(int i = A.size() - 1; i >= 0; --i) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]] = C[A[i]] - 1;
    }
}

int main() {
    vector<int> A = {2, 5, 3, 0, 2, 3, 0, 3};
    int k = 5;
    vector<int> B(A.size(), 0);

    countingSort(A, B, k+1);
    printArr(B);

    return 0;
}

