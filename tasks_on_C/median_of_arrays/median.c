#include <stdio.h>
#include <limits.h>  
#include <math.h>   

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {

    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }

    int totalLen = m + n;
    int halfLen = (totalLen + 1) / 2;
    int low = 0, high = m;

    while (low <= high) {
        int partition1 = (low + high) / 2;
        int partition2 = halfLen - partition1;

        int maxLeft1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
        int minRight1 = (partition1 == m) ? INT_MAX : nums1[partition1];
        int maxLeft2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
        int minRight2 = (partition2 == n) ? INT_MAX : nums2[partition2];

        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            if (totalLen % 2 == 0) {
                return (double)(fmax(maxLeft1, maxLeft2) + fmin(minRight1, minRight2)) / 2.0;
            } else { 
                return (double)fmax(maxLeft1, maxLeft2);
            }
        } else if (maxLeft1 > minRight2) {
            high = partition1 - 1;
        } else {
            low = partition1 + 1;
        }
    }

    return -1.0;
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    int m = sizeof(nums1) / sizeof(nums1[0]);
    int n = sizeof(nums2) / sizeof(nums2[0]);

    double median = findMedianSortedArrays(nums1, m, nums2, n);
    printf("Медиана: %.2f\n", median);

    return 0;
}
