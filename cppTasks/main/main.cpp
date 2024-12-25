//Массив: [3, 5, 1, 10, 2, 7]
//Максимальная куча: [10, 5, 7, 3, 2, 1]

#include <iostream>
#include <vector>
#include <algorithm>

void heapify(std::vector<int>& heap, int n, int i){

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


    if(left < n && heap[left] > heap[largest])
        largest = left;

    if(right < n && heap[right] > heap[right])
        largest = right;

    if(largest != i){
        std::swap(heap[i], heap[largest]);

        heapify(heap, n, largest);
    }
}

void buildHeap(std::vector<int>& heap){
    int n = heap.size();

    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(heap, n, i);
    }
}

int main(){
    std::vector<int> heap = {3, 5, 1, 10, 2, 7};

    buildHeap(heap);

    std::cout << "Max heap: ";
    for(int num : heap){
        std::cout << num << " ";
    }

    return 0;
}
