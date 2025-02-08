#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int closestSum = INT_MAX;
    int minDiff = INT_MAX;
    
    for (int i = 0; i < nums.size() - 2; i++) {
        int left = i + 1, right = nums.size() - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            int diff = abs(sum - target);
            
            if (diff < minDiff) {
                minDiff = diff;
                closestSum = sum;
            }
            
            if (sum < target) {
                left++;
            } else if (sum > target) {
                right--;
            } else {
                return sum;
            }
        }
    }
    return closestSum;
}

int main() {
    vector<int> nums1 = {-1, 2, 1, -4};
    int target1 = 1;
    cout << "Result 1: " << threeSumClosest(nums1, target1) << endl;
    
    vector<int> nums2 = {0, 0, 0};
    int target2 = 1;
    cout << "Result 2: " << threeSumClosest(nums2, target2) << endl;
    
    return 0;
}
