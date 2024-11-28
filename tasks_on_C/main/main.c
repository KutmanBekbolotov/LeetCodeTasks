#include <stdio.h>

int main() {
    int N;

    printf("enter number: ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Positive only\n");
        return 1;
    }

    int a = 0, b = 1;

    printf("First number of sequence %d : ", N);
    for (int i = 1; i <= N; i++) {
        printf("%d ", a);  
        int next = a + b; 
        a = b;       
        b = next;
    }
    printf("\n"); 

    return 0;
}
