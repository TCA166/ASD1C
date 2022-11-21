#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

int* mrgSrt(int* arr, int arrLen);

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
    input = mrgSrt(input, i2);
    printArr(input, i2);
    free(input);
    return 0;
}
//Returns an array of ints sorted with the merge sort algorythm. The time complexity is O(nlogn)
//Because T(n) = 2T(n/2) + θ(n)
int* mrgSrt(int* input,int i2){
    if(i2 == 1){ //if the length is one then do nothing
        return input;
    }
    else if(i2 == 2){ //if length is two then sorts
        if(input[0] > input[1]){
            int el = input[0];
            input[0] = input[1];
            input[1] = el;
        }
        else{
            return input;
        }   
    }
    //the length is > 2 so we have to divide
    int sizeA = i2/2;
    int sizeB = i2 - sizeA;
    int* arrA = calloc(sizeA, sizeof(int));
    memcpy(arrA, input, sizeA * sizeof(int));
    int* arrB = calloc(sizeB, sizeof(int));
    memcpy(arrB, input + sizeA, sizeB * sizeof(int));
    arrA = mrgSrt(arrA, sizeA);
    arrB = mrgSrt(arrB, sizeB);
    //and now we have to merge
    int a = 0, b = 0, i = 0;
    //we compare elements from both arrays at the same time as many times as possible
    while(a < sizeA && b < sizeB){
        if(arrA[a] > arrB[b]){
            input[i] = arrB[b];
            b++;
        }
        else{
            input[i] = arrA[a];
            a++;
        }
        i++;
    }
    //We make sure that no element was left behind
    while(a < sizeA){
        input[i] = arrA[a];
        a++;
        i++;
    }
    while(b < sizeB){
        input[i] = arrB[b];
        b++;
        i++;
    }
    return input;
}
//Displays all numeric values in array
void printArr(int* arr, int arrLen){
    for(int i = 0; i < arrLen; i++){
        printf("%d ", arr[i]);
    }
}


