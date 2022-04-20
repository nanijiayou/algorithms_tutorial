#include <iostream>
#include <vector>
using namespace std;

int Partition(vector<int> &A, int p, int r) {
	int pivot = A[r];
	int i = p - 1;
	for(int j = p; j < r; ++j) {
		if(A[j] <= pivot) swap(A[++i], A[j]);
	}
	swap(A[i+1], A[r]);
	return i + 1;
}

int RandomizedPartition(vector<int> &A, int p, int r) {
	int i = rand() % (r - p + 1) + p;
	swap(A[r], A[i]);
	return Partition(A, p, r);
}

int RandomizedSelect(vector<int> &A, int p, int r, int i) {
    if(i > 0 && i <= r - p + 1) {
	    if(p == r) return A[p];
	    int q = RandomizedPartition(A, p, r);
	    int k = q - p + 1;
	    if(i == k) return A[q];
	    else if(i < k) return RandomizedSelect(A, p, q-1, i);
	    else return RandomizedSelect(A, q + 1, r, i - k);
    } else {
        return -1;
    } 
}

int main() {
    vector<int> test { 1, 3, 7, 5, 9 };
    int n = test.size();
    int ans = RandomizedSelect(test, 0, 4, 5);
    return 0;
}