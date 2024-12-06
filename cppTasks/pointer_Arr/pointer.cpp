#include <iostream>

using namespace std;

double* allocateArray(int size){
    return new double[size];
}

void fillArray(double* array, int size){
    cout << "Enter: " << size << endl;
    for(int i=0; i < size; i++){
        cin >> array[i];
    }
}

void displayArray(const double* array, int size){
    cout << "Array elements: " << endl;
    for(int i=0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

void freeArray(double* array){
    delete[] array;
}

int main(){

    double* array = nullptr;
    int size = 0;
    char choice;

    do{
        cout << "Enter size of array: ";
        cin >> size;

        array = allocateArray(size);
        fillArray(array, size);

        displayArray(array, size);

        freeArray(array);
        array = nullptr;

        cout << "Create new array? (y/n): ";
        cin >> choice;
    }while (choice == 'y' || choice == 'Y');

    cout << "Work finished" << endl;
    return 0;
}

//array[nullptr] -> allocate [] [] [] -> array[3, 4, 5] -> [3,4,5] -> [nullptr] -> y/n char y/n