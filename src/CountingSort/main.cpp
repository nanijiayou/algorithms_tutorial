#include <iostream>
#include <vector>
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
    // vector<int> test { 1, 3, 7, 5, 9 };
    // countingSort(test);
    return 0;
}
