#include <iostream>
#include <vector>

using namespace std;

vector<int> rotLeft(vector<int>& a, int d) {
    int n = a.size();
    d = d % n;  
    vector<int> result(a.begin() + d, a.end());  
    result.insert(result.end(), a.begin(), a.begin() + d);  
    return result;
}

int main() {
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    vector<int> result = rotLeft(a, d);
    
    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}
