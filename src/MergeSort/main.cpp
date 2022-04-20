#include <iostream>
#include <vector>

using namespace std;
void printArr(vector<int> &A) {
    for(const auto & k : A) {
        std::cout << k << "-";
    }
    std::cout << std::endl;
    std::cout << "-----merge-----" << std::endl;
}

void MERGE(vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q;
    std::cout << "merge with: " << p << "-" << q << "-" << r << std::endl;
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    for(int i = 0; i < n1; ++i) {
        L[i] = A[p + i];
    }
    L[n1] = INT_MAX;
    printArr(L);

    for(int j = 0; j < n2; ++j) {
        R[j] = A[q + j + 1];
    }
    R[n2] = INT_MAX;
    printArr(R);

    int i = 0, j = 0, k = 0;
    for(k = p; k <= r; ++k) {
        if(L[i] < R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
    printArr(A);
}

void MERGESORT(vector<int>& A, int p, int r) {
    if(p < r) {
        int q = (p + r) / 2;
        std::cout << "start divide" << std::endl;
        MERGESORT(A, p, q);
        MERGESORT(A, q + 1, r);
        std::cout << "end divide" << std::endl;

        std::cout << "start merge: " << p << "-" << q << "-" << r << std::endl;
        MERGE(A, p, q, r);
    }
}


int main() {
    vector<int> test { 1, 3, 7, 5, 9 };
    int n = test.size();
    MERGESORT(test, 0, n-1);    
    printArr(test);
    return 0;
}
