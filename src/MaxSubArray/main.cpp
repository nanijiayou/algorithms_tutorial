/*
FIND-MAXIMUM-SUBARRAY(A, low, high)
    if low == high
        return (low, hight, A[low])
    else mid = (low + high) / 2
        (left-low, left-high, left-sum) = FIND-MAXIMUM-SUBARRAY(A, low, mid)
        (right-low, right-high, right-sum) = FIND-MAXIMUM-SUBARRAY(A, mid+1, high)
        (cross-low, cross-high, cross-sum) = FIND-MAX-CROSSING-SUBARRAY(A, low, mid, high)

        if(left-sum >= right-sum && left-sum >= cross-sum)
            return (left-low, left-high, left-sum)
        elseif(right-sum >= left-sum && right-sum >= cross-sum)
            return (right-low, right-high, right-sum)
        else return (cross-low, cross-high, cross-sum)

FIND-MAX-CROSSING-SUMBARRAY(A, low, mid, high)
    left-sum = -Infty
    sum = 0;
    for i = mid downto low
        sum = sum + A[i]
        if(sum > left-sum)
            left-sum = sum
            max-left = i
    right-sum = -Infty
    sum = 0
    for j = mid + 1 to high
        sum = sum + A[j]
        if(sum > right-sum)
            right-sum = sum
            right-max = j
    return (max-left, max-right, left-sum + right-sum)
*/

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// 分治解决最大子数组问题
tuple<int, int, int> FindMaxCrossingSubarray(vector<int> &A, int low, int mid, int high)
{
    int leftSum = INT_MIN, leftMax = mid;
    int sum = 0;
    for (int i = mid; i >= low; --i) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            leftMax = i;
        }
    }

    int rightSum = INT_MIN, rightMax = mid + 1;
    sum = 0;
    for (int j = mid + 1; j <= high; ++j) {
        sum += A[j];
        if (sum > rightSum) {
            rightSum = sum;
            rightMax = j;
        }
    }
    return {leftMax, rightMax, leftSum + rightSum };
};

tuple<int, int, int> FindMaximumSubarray(vector<int> &A, int low, int high) {
    cout << "Input: low=" << low << " high=" << high << endl;
    if(low == high) return {low, high, A[low]};
    else {
        int mid = low + ((high - low) >> 1);
        int leftLow, leftHigh, leftSum;
        tie(leftLow, leftHigh, leftSum) = FindMaximumSubarray(A, low, mid);
        cout << "left side: low=" << leftLow << " high=" << leftHigh << " sum=" << leftSum << endl;

        int rightLow, rightHigh, rightSum;
        tie(rightLow, rightHigh, rightSum) = FindMaximumSubarray(A, mid + 1, high);
        cout << "right side: low=" << rightLow << " high=" << rightHigh << " sum=" << rightSum << endl;

        int corssLow, crossHigh, crossSum;
        tie(corssLow, crossHigh, crossSum) = FindMaxCrossingSubarray(A, low, mid, high);
        cout << "corss both side: low=" << corssLow << " high=" << crossHigh << " sum=" << crossSum << endl;

        if(leftSum >= rightSum && leftSum >= crossSum) {
            return {leftLow, leftHigh, leftSum};
        } else if(rightSum >= leftSum && rightSum >= crossSum) {
            return {rightLow, rightHigh, rightSum};
        } else {
            return {corssLow, crossHigh, crossSum};
        }
    }
}

int main() {
    vector<int> test = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    // int l, h, s;
    int leftLow, leftHigh, leftSum;
    tie(leftLow, leftHigh, leftSum) = FindMaxCrossingSubarray(test, 0, 2, 4);
    cout << leftLow << "==" << leftHigh << "==" << leftSum << "==" << endl;

    int low, high, sum;
    tie(low, high, sum) = FindMaximumSubarray(test, 0, test.size() - 1);

    cout << low << "==" << high << "==" << sum << endl;
    return 0;
}
