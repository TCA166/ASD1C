#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Returns 1 or True if s is present in input using binary search.
int binSearch(int* input, int l,int r, int s){
    //printf("%d %d", l, r);
    int len = r - l + 1;
    if(len == 1){
        if(input[l] == s){
            return 1;
        }
        else{
            return 0;
        }
    }
    int mid = (l + r) / 2; //find the middle element
    //printf("Mid: %d", mid);
    if(input[mid] == s){ //check if the middle element is the one we are looking for
        return 1;
    }
    else if(input[mid] > s){
        //we take the lower part of the array
        r = mid - 1;
    }
    else{
        //we take the higher part of the array
        l = mid + 1;
    }
    return binSearch(input, l, r, s);   
}

//---Driver code for the sort algorythm---

void printArr(int* arr, int arrLen);

int* qkSort(int* input, int arrLen);

int main(){
    //Array of ints with size i2
    int* input = calloc(1, sizeof(int));
    //String prototype that gets converted to int and then reset
    char* strProt = calloc(1, sizeof(char));
    char c; //currently read char from stdin
    int i = 0; //currently read column id from stdin
    int i2 = -1; //Array length
    int target; //the first input element is the element we search for
    while(c != EOF) //While there are still chars to be read read them
    {
        c = fgetc(stdin);
        if(c == ' '){ //if that char is reset everything and add a new value to result arr
            strProt = realloc(strProt, (i + 1) * sizeof(char));
            strProt[i] = '\0'; //end the string properly
            i = 0; //reset the counter
            input = realloc(input, (i2 + 1) * sizeof(int));
            if(i2 > -1){
                input[i2] = atoi(strProt); //convert to int and assign to proper element in result arr
            }
            else{
                target = atoi(strProt);
            }
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
    if(strProt[0] != '\0'){ //if strlen isnt empty at loop end do as if we found a break
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
    //printArr(input, i2);
    input = qkSort(input, i2);
    //printArr(input, i2);
    int res = binSearch(input, 0, i2 - 1, target);
    printf("%d", res);
    free(input);
    return 0;
}
//Displays all numeric values in array
void printArr(int* arr, int arrLen){
    for(int i = 0; i < arrLen; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
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