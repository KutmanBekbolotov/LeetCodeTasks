#include <stdio.h>

int main(){
    int arr[] = {1, 2, 3, 4};
    arr[0] *= 2;
    arr[3] *= 2;

    printf("%d\n", arr[0]);
    printf("%d\n", arr[3]);

    return 0;
}