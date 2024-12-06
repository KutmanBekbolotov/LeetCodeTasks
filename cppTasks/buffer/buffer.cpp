#include <iostream>

using namespace std;

void fillArr(int* ptrArr, int sizeOfArr);
void showArr(int* ptrArr, int sizeOfArr);
void swapDataInCells(int* ptrArr, int sizeOfArr);

int main(){
    int sizeOfArray = 12;
    int* pArrForSwap = new int[sizeOfArray];

    fillArr(pArrForSwap, sizeOfArray);
    showArr(pArrForSwap, sizeOfArray);
    swapDataInCells(pArrForSwap, sizeOfArray);
    showArr(pArrForSwap, sizeOfArray);

    delete[] pArrForSwap;
    return 0;
}

void fillArr(int* ptrArr, int sizeOfArr){
    for(int i = 0; i < sizeOfArr; i++){
        ptrArr[i] = i * 10;
    }
}

void showArr(int* ptrArr, int sizeOfArr){
    for(int i = 0; i < sizeOfArr; i++){
        cout << ptrArr[i] << " ";
    }
    cout << endl << endl;
}

void swapDataInCells(int* ptrArr, int sizeOfArr){
    int bufferVar = 0;
    for(int i = 0; i < sizeOfArr - 1; i += 2){
        bufferVar = ptrArr[i];
        ptrArr[i] = ptrArr[i + 1];
        ptrArr[i + 1] = bufferVar;
    }

