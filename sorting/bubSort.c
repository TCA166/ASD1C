#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//Returns a sorted array using the bubble sort algorythm
//Bubble sort has T(n)=O(n^2), but is significantly worse than selection sort even though both have the same T(n)
int* bubSort(int* input, int arrLen){
    for(int i = 0; i < arrLen; i++){ //Do the inner loop as many times as there are elements in array
        for(int n = 0; n < arrLen - 1; n++){ //Foreach element in array
            if(input[n] > input[n + 1]){ //If the current element is larger than the next one
                //swap
                int x = input[n];
                input[n] = input[n + 1];
                input[n + 1] = x; 
            }
        }
    }
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
    input = bubSort(input, i2);
    free(input);
    return 0;
}
//Displays all numeric values in array
void printArr(int* arr, int arrLen){
    printf("\r");
    for(int i = 0; i < arrLen; i++){
        printf("%d ", arr[i]);
    }
    //printf("\n");
}


