#include <iostream>
#include <string>

using namespace std;

int romanToInt(string s){

    char romanSymbols[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int romanValues[] = {1, 5, 10, 50, 100, 500, 1000};

    int result = 0;
    int prevValue = 0;

        for (int i = s.length() - 1; i >= 0; i--) {
        int currentValue = 0;
        for (int j = 0; j < 7; j++) {
            if (s[i] == romanSymbols[j]) {
                currentValue = romanValues[j];
                break;
            }
        }


        if (currentValue < prevValue) {
            result -= currentValue;
        } else {
            result += currentValue;
        }
        prevValue = currentValue;
    }
    return result;
}

int main(){
    string roman;
    cout << "Введите римскую цифру"<< endl;
    cin >> roman;
    int integerValue = romanToInt(roman);
    return 0;
}