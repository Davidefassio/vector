/**
 *  MIT License
 *  Copyright (c) 2020 Davide Fassio
 */

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

/**
 * Functions' prototype:
 *   - void init(Vector*)
 *   - void push_int(Vector*, int)
 *   - void pop(Vector*, int)
 *   - void set_size(Vector*, int)
 *   - void shrink(Vector*)
 *   - int isEqual(Vector*, Vector*)
 *   - Vector* sum(Vector*, Vector*)
 *   - void print(Vector*)
 */

typedef struct{
    int *data;
    int capacity;
    int length;
}Vector;

void init(Vector *v){
    v->data = (int*) malloc(sizeof(int));
    v->capacity = 1;
    v->length = 0;
}

void push_int(Vector *v, int n){
    if(v->length < v->capacity){
        v->data[v->length] = n;
        ++v->length;
    }
    else{
        v->capacity *= 2;
        int *tmp = (int*) malloc(sizeof(int)*v->capacity), i;
        for(i = 0; i < v->length; ++i){ tmp[i] = v->data[i]; }
        tmp[i] = n;
        ++v->length;
        free(v->data);
        v->data = tmp;
    }
}

void pop(Vector *v, int n){
    v->length = (v->length > n) ? v->length - n : 0;
}

void set_size(Vector *v, int cap){
    if(cap < 1){ return; }
    if(v->capacity < cap){
        v->capacity = cap;
        int *tmp = (int*) malloc(sizeof(int)*cap), i;
        for(i = 0; i < v->length; ++i){ tmp[i] = v->data[i]; }
        free(v->data);
        v->data = tmp;
    }
    else if(v->capacity > cap){
        v->data = realloc(v->data, sizeof(int)*cap);
        v->capacity = cap;
        if(v->length > cap){ v->length = cap; }
    }
}

void shrink(Vector *v){
    v->data = realloc(v->data, sizeof(int)*v->length);
    v->capacity = v->length;
}

int isEqual(Vector *v1, Vector *v2){
    if(v1->length != v2->length){ return 0; }
    int i;
    for(i = 0; i < v1->length; ++i){
        if(v1->data[i] != v2->data[i]){ return 0; }
    }
    return 1;
}

Vector* sum(Vector *v1, Vector *v2){
    if(v1->length != v2->length){ exit(EXIT_FAILURE); }
    Vector *tmp = (Vector*) malloc(sizeof(Vector)); init(tmp);
    set_size(tmp, v1->length);
    int i;
    for(i = 0; i < v1->length; ++i){
        push_int(tmp, v1->data[i] + v2->data[i]);
    }
    return tmp;
}

void print(Vector *v){
    // printf("Capacity: %d, Length: %d\n", v->capacity, v->length); // DEBUG
    int i;
    printf("[ ");
    for(i = 0; i < v->length; ++i){
        printf("%d ", v->data[i]);
    }
    printf("]\n");
}


#endif // VECTOR_H_INCLUDED
