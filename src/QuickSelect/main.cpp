#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &A, int p, int r) {
	int pivot = A[r];
	int i = p - 1;
	for(int j = p; j < r; ++j) {
		if(A[j] <= pivot) swap(A[++i], A[j]);
	}
	swap(A[i+1], A[r]);
	return i + 1;
}

int pandomizedPartition(vector<int> &A, int p, int r) {
	int i = rand() % (r - p + 1) + p;
	swap(A[r], A[i]);
	return partition(A, p, r);
}

int randomizedSelect(vector<int> &A, int p, int r, int i) {
    if(i > 0 && i <= r - p + 1) {
	    if(p == r) return A[p];
	    int q = pandomizedPartition(A, p, r);
	    int k = q - p + 1;
	    if(i == k) return A[q];
	    else if(i < k) return randomizedSelect(A, p, q-1, i);
	    else return randomizedSelect(A, q + 1, r, i - k);
    } else {
        return -1;
    } 
}

int selectK(vector<int> &A, int k) {
	int n = A.size();
    return randomizedSelect(A, 0, n - 1, k);
}

int main() {
    vector<int> test { 1, 3, 7, 5, 9 };
    int n = test.size(), k = 2;
    int ans = selectK(test, k);
	cout << "the " << k << " element is " << ans << endl;
    return 0;
}