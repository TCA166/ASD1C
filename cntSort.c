#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Returns a sorted array using the count sort algorythm.
//Count sort has T(n)=O(n + K), K=maximum value in array
int* cntSrt(int* input, int arrLen, int maxVal){
    int* counts = calloc(maxVal, sizeof(int));
    //count the occurences of ints of different values
    for(int i = 0; i < arrLen; i++){
        int val = input[i];
        counts[val]++;
    }
    int x = 0;
    //and now simply output
    for(int i = 0; i < maxVal + 1; i++){
        for(int n = counts[i]; n > 0; n--){
            input[x] = i;
            x++;
        }
    }
    free(counts);
    return input;
}

int max(int* input, int arrLen){
    int max = input[0];
    for(int i = 1; i < arrLen; i++){
        if(input[i] > max){
            max = input[i];
        }
    }
    return max;
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
    input = cntSrt(input, i2, max(input, i2));
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