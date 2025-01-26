#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, S;
    cin >> n >> S;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int max_length = 0;   
    int current_sum = 0; 
    int left = 0;     

    for (int right = 0; right < n; ++right) {
        current_sum += arr[right];

        while (current_sum > S && left <= right) {
            current_sum -= arr[left];
            left++;
        }

        max_length = max(max_length, right - left + 1);
    }

    cout << max_length << endl;

    return 0;
}