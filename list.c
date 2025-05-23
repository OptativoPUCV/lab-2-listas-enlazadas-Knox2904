#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* l = malloc(sizeof(List)) ;
    if(l == NULL) exit(EXIT_FAILURE) ;  

    l->head = NULL ; 
    l->tail = NULL ;
    l->current = NULL ;     

     return l;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL ; 

    return list->current->data;
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL ;

    list->current = list->current->next ;    
    return list->current->data;
}

void * lastList(List * list) {

    if(list == NULL || list->current == NULL || list->tail == NULL) return NULL ;

    list->current = list->tail ; 
    return list->current->data;
}

void * prevList(List * list) {

    if(list == NULL || list->current == NULL || list->current->prev == NULL) return NULL ;  

    list->current = list->current->prev ; 
    return list->current->data;
}

void pushFront(List * list, void * data) {

    Node* newNode = createNode(data) ;
    if(newNode==NULL) exit(EXIT_FAILURE) ; 

    newNode->next = list->head;
    if(list->head != NULL){
        list->head->prev = newNode ; 
    }
    else list->tail = newNode ; 

    list->head = newNode ;
    newNode->prev = NULL ;  

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {

    if(list ==  NULL || list->current == NULL) return ;

    Node* newNode = createNode(data) ;
    if(newNode == NULL) exit(EXIT_FAILURE) ;

    newNode->prev= list->current ; 
    newNode->next = list->current->next ; 

    if(list->current->next != NULL){
        list->current->next->prev = newNode ; 
    }
    else list->tail = newNode ; 

    list->current->next = newNode ; 
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list == NULL || list->current == NULL)  return NULL ;    

    Node* temp = list->current ;
    void* datoK = list->current->data ; 
    if(temp->prev != NULL){
        temp->prev->next = temp->next ;
    }
    else list->head = temp->next ;

    if(temp->next != NULL){
        temp->next->prev = temp->prev ;
    }
    else list->tail = temp->prev ;

    list->current = temp->next ;
    free(temp) ; 

    return datoK;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}