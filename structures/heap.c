#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Set value that represents heap node that hasn't been set yet
#define none INT_MIN

//Heap data structure
struct heap{
    int size;
    int* arr;
};
//Returns the right children id in heap like array
int getHeapRightIndex(int i){
    return (i + 1) * 2;
}
//Returns the left children id in heap like array
int getHeapLeftIndex(int i){
    return (i + 1) * 2 - 1;
}
//Returns the parent element id in heap like array
int getHeapParentIndex(int i){
    if(i == 0){
        return 0;
    }
    if(i % 2 != 0){
        i++;
    }
    i = i / 2;
    return i--;
}
//Returns a properly initialised heap
struct heap* heapInit(int root){
    struct heap* h = malloc(sizeof(struct heap));
    h->size = 1;
    h->arr = calloc(3, sizeof(int));
    h->arr[0] = root;
    h->arr[1] = none;
    h->arr[2] = none;
    return h;
}
//Mounts a new value to the heap as the right value of the node under the given index
void mountRight(struct heap* heap, int val, int index){
    int right = getHeapRightIndex(index);
    int newSize = getHeapRightIndex(right) + 1;
    if(heap->size < newSize){
        heap->size = newSize;
        heap->arr = realloc(heap->arr, newSize * sizeof(int));
    }
    heap->arr[right] = val;
    heap->arr[getHeapRightIndex(right)] = none;
    heap->arr[getHeapLeftIndex(right)] = none;
}
//Mounts a new value to the heap as the left value of the node under the given index
void mountLeft(struct heap* heap, int val, int index){
    int left = getHeapLeftIndex(index);
    int newSize = getHeapRightIndex(left) + 1;
    if(heap->size < newSize){
        heap->size = newSize;
        heap->arr = realloc(heap->arr, newSize * sizeof(int));
    }
    heap->arr[left] = val;
    heap->arr[getHeapLeftIndex(left)] = none;
    heap->arr[getHeapRightIndex(left)] = none;
}
//Mounts a new value to the heap assuming the heap is a binary heap using the index as root
void mountBin(struct heap* heap, int val, int index){
    if(val == none){
        return;
    }
    if(val > heap->arr[index]){
        if(heap->arr[getHeapRightIndex(index)] == none){
            mountRight(heap, val, index);
        }
        else{
            mountBin(heap, val, getHeapRightIndex(index));
        }
    }
    else{
        if(heap->arr[getHeapLeftIndex(index)] == none){
            mountLeft(heap, val, index);
        }
        else{
            mountBin(heap, val, getHeapLeftIndex(index));
        }
    }
}
//Returns 1 or True and 0 or False if the heap is binary
int isBin(struct heap* heap, int index){
    if(heap->arr[getHeapRightIndex(index)] != none){
        if(heap->arr[index] > heap->arr[getHeapRightIndex(index)] || !isBin(heap, getHeapRightIndex(index))){
            return 0;
        }
    }
    if(heap->arr[getHeapLeftIndex(index)] != none){
        if(heap->arr[index] < heap->arr[getHeapLeftIndex(index)] || !isBin(heap, getHeapLeftIndex(index))){
            return 0;
        }
    }
    return 1;
}
//Mounts a new value to the heap assuming the heap is a max heap
void mountMax(struct heap* heap, int val, int index){
    if(val <= none){
        return;
    }
    if(val > heap->arr[index]){
        int newVal = heap->arr[index];
        heap->arr[index] = val;
        if(newVal != none){
            mountMax(heap, newVal, index);
        }
        else{
            int newSize = getHeapRightIndex(index) + 1;
            if(newSize > heap->size){
                heap->size = newSize;
                heap->arr = realloc(heap->arr, newSize * sizeof(int));
            }
            heap->arr[getHeapLeftIndex(index)] = none;
            heap->arr[getHeapRightIndex(index)] = none;
        }
    }
    else{
        if(val > heap->arr[getHeapRightIndex(index)]){
            mountMax(heap, val, getHeapRightIndex(index));
        }
        else{
            mountMax(heap, val, getHeapLeftIndex(index));
        }
    }
}
//Returns 1 or True and 0 or False if the heap is max heap
int isMax(struct heap* heap, int index){
    if(heap->arr[getHeapLeftIndex(index)] != none){
        if(heap->arr[index] < heap->arr[getHeapLeftIndex(index)] || !isMax(heap, getHeapLeftIndex(index))){
            return 0;
        }
    }
    if(heap->arr[getHeapRightIndex(index)] != none){
        if(heap->arr[index] < heap->arr[getHeapRightIndex(index)] || !isMax(heap, getHeapRightIndex(index))){
            return 0;
        }
    }
    return 1;
} 
//Returns the heap node to type max
void maxHeapify(struct heap* heap, int index){
    int left = getHeapLeftIndex(index);
    int right = getHeapRightIndex(index);
    int largest = index;
    if(heap->arr[left] != none){
        if(heap->arr[left] > heap->arr[index]){
            largest = left;
        }
        else{
            largest = index;
        }
    }
    if(heap->arr[right] != none){
        if(heap->arr[right] > heap->arr[index]){
            largest = right;
        }
    }
    if(largest != index){
        int val = heap->arr[largest];
        heap->arr[largest] = heap->arr[index];
        heap->arr[index] = val;
        maxHeapify(heap, largest);
    }
}
//Totally rebuild the heap from an unsorted array
void rebuildMaxHeap(struct heap* heap, int index){
    for(int i = heap->size - 1; i >= 0; i--){
        if(heap->arr[i] != none){
            maxHeapify(heap, i);
        }
    }
}
//Prints the contents of the heap using the KLP scheme
void printHeap(struct heap* heap, int index){
    if(heap->arr[index] != none){
        printf("%d, ", heap->arr[index]);
        printHeap(heap, getHeapLeftIndex(index));
        printHeap(heap, getHeapRightIndex(index));
    }
}
/*
int main(){
    struct heap* heap = heapInit(69);
    mountMax(heap, 420, 0);
    mountMax(heap, 16, 0);
    mountMax(heap, 100, 0);
    printHeap(heap, 0);
    printf("%d\n", isMax(heap, 0));
    heap->arr[2] = -1;
    printHeap(heap, 0);
    printf("%d\n", isMax(heap, 0));
    maxHeapify(heap, 0);
    printHeap(heap, 0);
    printf("%d\n", isMax(heap, 0));
    rebuildMaxHeap(heap, 0);
    printHeap(heap, 0);
    printf("%d\n", isMax(heap, 0));
}
*/