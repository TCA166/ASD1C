#include <stdlib.h>
#include <stdio.h>
//List element structure. The next and prev attributes should hold the pointers to the next and previous elements accordingly or NULL
//The head attribute should point to the listHeader struct. The value attribute should hold a pointer to any value
struct listElement{
    struct listElement* next; //Pointer to the next element in list or NULL
    struct listElement* prev; //Pointer to the previous element in list or NULL
    struct listHeader* head; //pointer to the listHeader or NULL
    void* value; //Value of the list element or NULL
};
//List header structure. Essentially a wrapper for a linked list of listElements.
struct listHeader{
    struct listElement* firstElement; //First listElement in list or NULL if length=0
    struct listElement* lastElement; //Last listElement in list
    unsigned int length; //Length of the linked list >=0
};
//Returns a listHeader struct properly initialised for both standalone functioning and under listHeader
struct listHeader* listInit(){
    struct listHeader* list = malloc(sizeof(struct listHeader));
    list->firstElement = NULL;
    list->lastElement = NULL;
    list->length = 0;
    return list;
}
//Returns a properly initialised listElement struct
struct listElement* elementInit(void* value){
    struct listElement* newElement = malloc(sizeof(struct listElement));
    newElement->next = NULL; 
    newElement->prev = NULL; 
    newElement->head = NULL; 
    newElement->value = value;
    return newElement;
}
//Properly links a new element in a linked list
void fitElement(struct listElement* prev, struct listElement* next, struct listElement* new){
    new->prev = prev;
    if(prev != NULL){
        prev->next = new;
    }
    new->next = next;
    if(next != NULL){
        next->prev = new;
    }
}
//Properly unlinks an element in a linked list
void unfitElement(struct listElement* element){
    if(element->prev != NULL){
        element->prev->next = element->next;
    }
    if(element->next != NULL){
        element->next->prev = element->prev;
    }
    element->prev = NULL;
    element->next = NULL;
}
//Appends a given element to the list at the end.
void appendElement(struct listHeader* list, struct listElement* newElement){
    newElement->head = list;
    //then we properly handle the old last element
    struct listElement* oldLastElement = list->lastElement;
    fitElement(oldLastElement, NULL, newElement);
    if(oldLastElement != NULL){
        oldLastElement->next = newElement;
    }
    //If list length is zero then we need to assign the firstElement attribute
    if(list->length == 0){
        list->firstElement = newElement;
    }
    else{
        list->lastElement->next = newElement;
    }
    list->lastElement = newElement;
    list->length++;
}
//Returns an element with the given index in the linked list
struct listElement* getElement(struct listHeader* list, int index){
    if(index > list->length || index < 0){
        perror("List index out of range\n");
        return NULL;
    }
    struct listElement* element;
    if(index > list->length / 2){ //Index is closer to the end than to the beggining
        element = list->lastElement;
        for(int i = list->length - index - 1; i > 0; i--){
            element = element->prev;
        }
        
    }
    else{ //Index is closer to the start
        element = list->firstElement;
        for(int i = index; i > 0; i--){
            element = element->next;
        }
    }
    return element;
}
//Inserts a given newElement at the given index with the previous element being moved forward
struct listElement* insertElement(struct listHeader* list, int index, struct listElement* newElement){
    struct listElement* curElement = getElement(list, index);
    if(curElement == NULL){ //Error handling
        return NULL;
    }
    list->length++;
    newElement->head = list;
    fitElement(curElement->prev, curElement, newElement);
    if(curElement == list->firstElement){
        list->firstElement = newElement;
    }
    return newElement;
}
//Removes an element from the given list under the given index and then returns it
struct listElement* removeElement(struct listHeader* list, int index){
    struct listElement* elementToBeRemoved = getElement(list, index);
    if(list->firstElement == elementToBeRemoved){
        list->firstElement = elementToBeRemoved->next;
    }
    if(list->lastElement == elementToBeRemoved){
        list->lastElement == elementToBeRemoved->prev;
    }
    unfitElement(elementToBeRemoved);
    list->length--;
    elementToBeRemoved->head = NULL;
    return elementToBeRemoved;
}
//Returns an array of void pointers containing values of all accesible linked list elements
void** toArr(struct listHeader* list){
    void** arr = calloc(list->length, sizeof(void*));
    struct listElement* curElement = list->firstElement;
    for(int i = 0; i < list->length; i++){
        arr[i] = malloc(sizeof(void*));
        arr[i] = curElement->value;
        if(curElement->next == NULL){
            break;
        }
        curElement = curElement->next;
    }
    return arr;
}
//Returns a newly created linked listB header from all list elements beyond the element marked by index.
struct listHeader* listSplit(struct listHeader* listA, int index){
    if(index > listA->length || index < 0){
        perror("List index out of range\n");
        return NULL;
    }
    struct listHeader* listB = listInit();
    struct listElement* curElement = getElement(listA, index);
    listB->firstElement = curElement->next;
    listB->lastElement = listA->lastElement;
    listB->length = listA->length - index;
    listA->lastElement = curElement;
    listA->length = index + 1;
    return listB;
}
//Frees all elements following the startElement in list.
struct listElement* freeElements(struct listElement* startElement){
    if(startElement->next != NULL){
        free(freeElements(startElement->next));
    }
    if(startElement->prev == NULL){
        free(startElement);
    }
    return startElement;
}
//Frees all memory associated with the list in any capacity and returns the length of the freed list.
int freeList(struct listHeader* list){
    freeElements(list->firstElement);
    int len = list->length;
    free(list);
    return len;
}
int main(){
    struct listHeader* list = listInit();
    appendElement(list, elementInit("pierwszy"));
    appendElement(list, elementInit("drugi"));
    appendElement(list, elementInit("trzeci"));
    insertElement(list, 0, elementInit("zerowy"));
    free(removeElement(list, 0)); //removed elements aren't freed automatically so they must be freed after removal
    freeList(list);
}