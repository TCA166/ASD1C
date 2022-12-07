#include <stdlib.h>
#include <stdio.h>
//Stack type structure
//Handled by pushToStack() and popFromStack()
struct stack
{
    void** elements; //Pointer array with pointers to different values
    int length; //Length of the stack
    void* top; //Pointer to the last pushed to the stack value
};
//Returns a properly initialised stack struct
struct stack* initStack(){
    struct stack* newStack = malloc(sizeof(struct stack));
    newStack->length = 0;
    newStack->top = NULL;
    newStack->elements = calloc(0, sizeof(void*));
    return newStack;
}
//Adds an element to stack at the top
void pushToStack(struct stack* stack, void* element){
    stack->elements = realloc(stack->elements, (stack->length + 1) * sizeof(void*));
    stack->elements[stack->length] = element;
    stack->top = element;
    stack->length++;
}
//Returns the newly removed element from stack
void* popFromStack(struct stack* stack){
    if(stack->top == NULL){
        return NULL;
    }
    void* element = stack->top;
    stack->length--;
    stack->elements = realloc(stack->elements, stack->length * sizeof(void*));
    if(stack->length > 0){
        stack->top = stack->elements[stack->length - 1];
    }
    else{
        stack->length = 0;
        stack->top = NULL;
    }
    return element;
}
//Reverses the given stack
void reverseStack(struct stack* stack){
    if(stack->top == NULL){
        return;
    }
    int arrLen = stack->length;
    void** values = calloc(arrLen, sizeof(void*));
    while(stack->top != NULL){
        values[stack->length - 1] = popFromStack(stack);    
    }
    printf("%s, %s\n", values[0], values[1]);
    for(int i = 0; i < arrLen; i++){
        pushToStack(stack, values[i]);
    }
    free(values);
}
//Frees all memory held up by the stack itself not the elements
void freeStack(struct stack* stack){
    /* //This doesnt work because those pointers might be pointers to non heap memory
    for(int i = 0; i < stack->length; i++){
        free(stack->elements[i]);
    }*/
    free(stack->elements);
    free(stack);
}
/*
int main(){
    struct stack* stack = initStack();
    pushToStack(stack, "test");
    pushToStack(stack, "test2");
    printf("%s, %s\n", stack->elements[0], stack->elements[1]);
    reverseStack(stack);
    printf("%s, %s", stack->elements[0], stack->elements[1]);
    freeStack(stack);
}*/