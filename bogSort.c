#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int* bogSort(int* arr, int arrLen);

int isSorted(int* input, int arrLen);

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
    input = bogSort(input, i2);
    free(input);
    return 0;
}
//Returns a sorted array using the bogo sort algorythm.
//Optimistic T(n)=O(n) and pesymistic T(n)=O(9^n) but theoreticly bogosort can take forever
int* bogSort(int* input, int arrLen){
    srand(time(NULL)); //initialise rng
    int n = 0;
    while(!isSorted(input, arrLen)){
        //shuffle the array
        for(int i = 0; i < arrLen; i++){
            int num = (rand() % arrLen);
            int t = input[num];
            input[num] = input[i];
            input[i] = t;
        }
        n++;
        printArr(input, arrLen);
    }
    printf("\nNum of iterations: %d\n", n);
    return input;
}
//Returns 1 if the input array is sorted in a rising manner and 0 if the opposite is true
int isSorted(int* input, int arrLen){
    for(int i = 1; i < arrLen; i++){
        if(input[i] < input[i - 1]){
            return 0;
        }
    }
    return 1;
}
//Displays all numeric values in array
void printArr(int* arr, int arrLen){
    printf("\r");
    for(int i = 0; i < arrLen; i++){
        printf("%d ", arr[i]);
    }
    //printf("\n");
}


