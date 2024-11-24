#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

char* getPermutation(int n, int k) {

    int* numbers = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }

    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[n] = '\0'; 

    k--; 

    for (int i = 0; i < n; i++) {
        int fact = factorial(n - 1 - i); 
        int index = k / fact;            
        result[i] = numbers[index] + '0';
        k %= fact;                      

        for (int j = index; j < n - 1 - i; j++) {
            numbers[j] = numbers[j + 1];
        }
    }

    free(numbers);
    return result;
}

int main() {
    int n, k;
    printf("Введите n: ");
    scanf("%d", &n);
    printf("Введите k: ");
    scanf("%d", &k);

    char* permutation = getPermutation(n, k);
    printf("k-я перестановка: %s\n", permutation);

    free(permutation);  
    return 0;
}
