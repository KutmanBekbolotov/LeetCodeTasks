#include <stdlib.h>

int countOne(int n){
    int count = 0;
    long long factor = 1;

    while(n / factor > 0){
        long long higher = n / (factor * 10);
        long long current = (n / factor) % 10;
        long long lower = n % factor;

        if(current == 0){
            count += higher * factor;
        }else if(current == 1){
            count += higher * factor + lower + 1;
        }else{
            count += (higher + 1) * factor;
        }

        factor *= 10;
    }

    return count;
}

int main(){
    int n1 = 13;
    int n2 = 0;

    printf("Вход: n = %d\nВыход: %d\n", n1, countDigitOne(n1)); 
    printf("Вход: n = %d\nВыход: %d\n", n2, countDigitOne(n2));

    return 0;
}