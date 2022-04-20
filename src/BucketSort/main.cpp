#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printArr(vector<float>& A) {
    for(const auto & k : A) {
        std::cout << k << " ";
    }
    std::cout << std::endl;
}

void InsertionSort(vector<float> &A) {
    for(int i = 1; i < A.size(); ++i) {
        float key = A[i];
        int j = i - 1;
        while(j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}

// bucket_size: 桶容量
void BUCKKETSORT(vector<float> &A, int bucket_size) {
    int N = A.size();
    float max = *max_element(A.begin(), A.end());
    float min = *min_element(A.begin(), A.end());

    // 桶的个数
    int bucket_count = (max - min) / bucket_size + 1;

    // 创建空桶
    vector<float> b[bucket_count];

    // 将元素放入不同的桶中
    for(int i = 0; i < N; ++i) {
        int idx = (A[i] - min) / bucket_size;
        b[idx].push_back(A[i]);
    }

    int idx = 0;
    for(int i = 0; i < bucket_count; ++i) {
        // 对每一个不是空的桶排序
        if(!b[i].empty()) sort(b[i].begin(), b[i].end());
        // 合并所有的桶
        for(int j = 0; j < b[i].size(); ++j)
            A[idx++] = b[i][j];
    }
}

int main() {
    // vector<float> test = {0.1234, 0.3434, 0.565, 0.656, 0.665, 0.897};
    vector<float> test = {9.8 , 0.6 , 10.1 , 1.9 , 3.07 , 3.04 , 5.0 , 8.0 , 4.8, 7.68};
    BUCKKETSORT(test, 1);
    printArr(test);
    return 0;
}
