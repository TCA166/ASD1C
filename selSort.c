#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int findMin(int *arr, int arrLen, int startId);

/*Returns a sorted arr array of arrLen length using the select sort algorithm.
Select sort has O(n^2) because it has two embedded loops*/
int* selSrt(int* input, int arrLen){
    int* resultArr = calloc(arrLen, sizeof(int));
    int i2 = arrLen; //arr Length
    for(int i = 0; i < i2; i++){
        int minId = findMin(input, arrLen, i); //find the smallest element
        resultArr[i] = input[minId]; //write that smallest element to the result array
        input[minId] = input[i]; //overwrite that smallest element so that it doesn't get selected again
    }
    free(input);
    return resultArr;
}
//Returns the Id of the smallest element in array
int findMin(int *arr, int arrLen, int startId){
    //We skip the first element in iteration and just assume it's the smallest for now
    int min = startId; //Id of the smallest element
    for(int i = startId + 1; i < arrLen; i++){ //foreach element we check if its smaller
        if(arr[i] < arr[min]){
            min = i; //if it is we change the mini
        }
    }
    return min;
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
    input = selSrt(input, i2);
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