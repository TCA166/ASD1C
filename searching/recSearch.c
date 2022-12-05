#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Returns 1 or True if input array contains s using linear search with recursion
int recSearch(int* input, int start, int end, int s){
    if(start == end){
        return input[start] == s;
    }
    int mid = (end + start) / 2;
    //we divide the array in two and then try to recursively do the same on the two parts
    return recSearch(input, start, mid, s) || recSearch(input, mid + 1, end, s);
}

//---Driver code for the searching algorythm---

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
    int res = recSearch(input, 0, i2, target);
    printf("%d", res);
    free(input);
    return 0;
}