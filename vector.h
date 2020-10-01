/**
 *  MIT License
 *  Copyright (c) 2020 Davide Fassio
 */

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

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

int isEqual(int cnt, ...){
    if(cnt < 1){ exit(EXIT_FAILURE); }
    if(cnt == 1) { return 1; }
    va_list args;
    va_start(args, cnt);
    int i, j, c, l = va_arg(args, Vector*)->length;
    for(i = 1; i < cnt; ++i){
        if(l != va_arg(args, Vector*)->length){ return 0; }
    }
    va_end(args);
    for(i = 0; i < l; ++i){
        va_start(args, cnt);
        c = va_arg(args, Vector*)->data[i];
        for(j = 1; j < cnt; ++j){
            if(c != va_arg(args, Vector*)->data[i]){ return 0; }
        }
        va_end(args);
    }
    return 1;
}

Vector* sum(int cnt, ...){
    if(cnt < 1){ exit(EXIT_FAILURE); }
    else if(cnt == 1){
        Vector *tmp = (Vector*) malloc(sizeof(Vector)); init(tmp);
        push_int(tmp, 0);
        va_list args;
        va_start(args, cnt);
        Vector *t = va_arg(args, Vector*);
        int i;
        for(i = 0; i < t->length; ++i){ tmp->data[0] += t->data[i]; }
        return tmp;
    }
    else{
        va_list args;
        va_start(args, cnt);
        int i, j, l = va_arg(args, Vector*)->length;
        for(i = 1; i < cnt; ++i){
            if(l != va_arg(args, Vector*)->length){ exit(EXIT_FAILURE); }
        }
        va_end(args);
        Vector *tmp = (Vector*) malloc(sizeof(Vector)); init(tmp);
        set_size(tmp, l);
        for(i = 0; i < l; ++i){
            push_int(tmp, 0);
            va_start(args, cnt);
            for(j = 0; j < cnt; ++j){
                tmp->data[i] += va_arg(args, Vector*)->data[i];
            }
            va_end(args);
        }
        return tmp;
    }
}

void print(Vector *v, FILE *f){
    if(v->length < 1){ return; }
    int i;
    fprintf(f, "%d", v->data[0]);
    for(i = 1; i < v->length; ++i){
        fprintf(f, " %d", v->data[i]);
    }
    fprintf(f, "\n");
}

#endif // VECTOR_H_INCLUDED
