#include <stdio.h>
#include <limits.h>

int max(int a, int b, int c) {
    if (a > b && a > c) return a;
    if (b > c) return b;
    return c;
}

int helper(int* nums, int left, int right) {
    if (left == right) {
        return nums[left];
    }

    int mid = (left + right) / 2;

    int left_sum = helper(nums, left, mid);
    int right_sum = helper(nums, mid + 1, right);

    int left_max = INT_MIN;
    int right_max = INT_MIN;
    int temp_sum = 0;

    for (int i = mid; i >= left; i--) {
        temp_sum += nums[i];
        if (temp_sum > left_max) {
            left_max = temp_sum;
        }
    }

    temp_sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        temp_sum += nums[i];
        if (temp_sum > right_max) {
            right_max = temp_sum;
        }
    }

    int cross_sum = left_max + right_max;

    return max(left_sum, right_sum, cross_sum);
}

int maxSubArray(int* nums, int numsSize) {
    return helper(nums, 0, numsSize - 1);
}
