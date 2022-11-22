#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

int* qkSort(int* arr, int arrLen);

void printArr(int* arr, int arrLen);

int main(){
    //Array of ints with size i2
    int* input = calloc(1, sizeof(int));
    //String prototype that gets converted to int and then reset
    char* strProt = calloc(1, sizeof(char));
    char c; //currently read char from stdin
    int i = 0; //currently read column id from stdin
    int i2 = 0; //Array length
    while(read(STDIN_FILENO, &c, 1) > 0) //While there are still chars to be read read them
    {
        if(c == ' '){ //if that char is reset everything and add a new value to result arr
            strProt = realloc(strProt, (i + 1) * sizeof(char));
            strProt[i] = '\0'; //end the string properly
            i = 0; //reset the counter
            input = realloc(input, (i2 + 1) * sizeof(int));
            input[i2] = atoi(strProt); //convert to int and assign to proper element in result arr
            i2++;
            strProt = realloc(strProt, 1 * sizeof(char)); //wipe the prototype string
            strProt[0] = '\0';
        }
        else{
            strProt = realloc(strProt, (i + 1) * sizeof(char));
            strProt[i] = c;
            i++;
        }
        
    }
    if(strlen(strProt)){ //if strlen isnt empty at loop end do as if we found a break
        strProt = realloc(strProt, (i + 1) * sizeof(char));
        strProt[i] = '\0';
        i = 0;
        input = realloc(input, (i2 + 1) * sizeof(int));
        input[i2] = atoi(strProt);
        i2++;
        strProt = realloc(strProt, 1 * sizeof(char));
        strProt[0] = '\0';
    }
    free(strProt);
    //Input handled and we are ready to sort
    printf("\n");
    input = qkSort(input, i2);
    printArr(input, i2);
    free(input);
    return 0;
}
//Returns a sorted int array using the quick sort algorythim (Hoare’s Partition Scheme)
//Avg and optimistic T(n)=O(nlogn); Pesymistic T(n)=O(n^2) and occurs if the array is sorted
int* qkSort(int* input, int arrLen){
    if(arrLen <= 1){ //if the array is only an element long
        return input; //just break out
    }
    int l = 0; //left pointer - starts at the left and moves right
    int r = arrLen - 1; //right pointer - starts at the end and moves left
    int pivotId = arrLen / 2; //pivotId - in this case the middle element
    int pivot = input[pivotId];
    while(1){ //as long the two pointers dont meet
        //move the left pointer until we find an element smaller that pivot
        while(input[l] < pivot){ 
            l++; 
        }
        //move the right pointer until we find a larger element than pivot
        while(input[r] > pivot){
            r--;
        }
        if(l >= r){ //if the two pointers met while moving
            break; //break out
        }
        //swap the values if we didnt break out
        int n = input[l];
        input[l] = input[r];
        input[r] = n;
    }
    //create the left array
    int* arrL = calloc(r, sizeof(int));
    memcpy(arrL, input, r * sizeof(int));
    arrL = qkSort(arrL, r); //recursion
    //create the right array
    int* arrR = calloc(arrLen - r, sizeof(int));
    memcpy(arrR, input + r + 1, (arrLen - r - 1) * sizeof(int));
    arrR = qkSort(arrR, arrLen - r - 1); //recursion
    //now merge
    memcpy(input, arrL, (r) * sizeof(int));
    memcpy(input + r + 1, arrR, (arrLen - r - 1) * sizeof(int));
    //free the right and left arrays
    free(arrL);
    free(arrR);
    return input;
}
//Displays all numeric values in array
void printArr(int* arr, int arrLen){
    for(int i = 0; i < arrLen; i++){
        printf("%d:%d ", i, arr[i]);
    }
    printf("\n");
}


