#include <stdio.h>

int main(){
    int arr[] = {3, 1, 1, 5, 7, 3};
    int n = 6;
    int isUniq;

    printf("Uniq numbers: \n");

    for(int i=0; i<n; i++){
        isUniq = 1;

        for(int j=0; j<n; j++){
            if( i != j && arr[i] == arr[j]){
                isUniq = 0;
                break;
            }
        }
        if(isUniq){
            
        }
    }
    printf("\n");
    return 0;
}