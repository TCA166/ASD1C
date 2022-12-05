#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Returns an array of ints sorted with the merge sort algorythm. The time complexity is O(nlogn)
//Because T(n) = 2T(n/2) + θ(n)
int* mrgSrt(int* input,int i2){
    if(i2 == 1){ //if the length is one then do nothing and just return
        return input;
    }
    //Here you could also do rudimentary sorting though that would make the algorythm not canonical
    //the length is > 1 so we have to divide
    int sizeA = i2 / 2; //size of the left side
    int sizeB = i2 - sizeA; //size of the right side
    //initialise the arrays
    int* arrA = calloc(sizeA, sizeof(int));
    memcpy(arrA, input, sizeA * sizeof(int));
    int* arrB = calloc(sizeB, sizeof(int));
    memcpy(arrB, input + sizeA, sizeB * sizeof(int));
    //recursion
    arrA = mrgSrt(arrA, sizeA);
    arrB = mrgSrt(arrB, sizeB);
    //and now we have to merge
    int a = 0, b = 0, i = 0;
    //we compare elements from both arrays at the same time as many times as possible
    while(a < sizeA && b < sizeB){ //while we havent reached the end of either arr
        //compare an element from A and B and swap accordingly
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
    free(arrA);
    free(arrB);
    return input;
}

//---Driver code for the sort algorythm---

void printArr(int* arr, int arrLen);

int main(){
    //Array of ints with size i2
    int* input = calloc(1, sizeof(int));
    //String prototype that gets converted to int and then reset
    char* strProt = calloc(1, sizeof(char));
    char c; //currently read char from stdin
    int i = 0; //currently read column id from stdin
    int i2 = 0; //Array length
    while(c != EOF) //While there are still chars to be read read them
    {
        c = fgetc(stdin);
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
    input = mrgSrt(input, i2);
    printArr(input, i2);
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