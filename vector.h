/**
 *  MIT License
 *  Copyright (c) 2020 Davide Fassio
 */

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <string.h>

typedef struct{
    float *data;
    size_t capacity;
    size_t length;
}Vector;

Vector* init(Vector *v){
    if(v == NULL){
        v = (Vector*) malloc(sizeof(Vector));
        if(v == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    v->data = (float*) malloc(sizeof(float));
    if(v->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    v->capacity = 1;
    v->length = 0;
    return v;
}

void push_flt(Vector *v, float n){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    if(v->length < v->capacity){
        v->data[v->length] = n;
        ++v->length;
    }
    else{
        v->capacity *= 2;
        
        v->data = realloc(v->data, sizeof(float)*v->capacity);
        if(v->data == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        
        v->data[v->length] = n;
        ++v->length;
    }
}

void push_arr(Vector *v, float *arr, size_t n){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    if(arr == NULL){
        printf("The pointer to float points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    if(v->length + n < v->capacity){
        size_t i;
        for(i = 0; i < n; ++i){
            v->data[v->length+i] = arr[n];
        }
        v->length += n;
    }
    else{
        do{
            v->capacity *= 2;
        } while(v->capacity < n + v->length);
        
        v->data = realloc(v->data, sizeof(float)*v->capacity);
        if(v->data == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        
        size_t i;
        for(i = 0; i < n; ++i){
            v->data[v->length+i] = arr[i];
        }
        v->length += n;
    }
}

void insert_flt(Vector *v, float n, size_t pos){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    if(pos > v->length){
        printf("Index out of range.\n");
        exit(EXIT_FAILURE);
    }
    
    if(pos == v->length){
        push_flt(v, n);
    }
    else{
        size_t i;
        push_flt(v, v->data[v->length-1]);
        for(i = v->length-2; i > pos; --i){
            v->data[i] = v->data[i-1];
        }
        v->data[pos] = n;
    }
}

void insert_arr(Vector *v, float *arr, size_t s, size_t f){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    if(s > v->length){
        printf("Index out of range.\n");
        exit(EXIT_FAILURE);
    }
    
    if(s == v->length){
        push_arr(v, arr, f-s);
    }
    else{
        size_t i;
        
        for(i = 0; i < f-s; ++i){
            push_flt(v, v->data[v->length-1]);
        }
        for(i = s; i < f; ++i){
            v->data[i+f-s] = v->data[i];
            v->data[i] = arr[i-s];
        }
    }
}

Vector* vecrand(size_t num, float min, float max){
    srand((unsigned int) time(0));
    
    Vector *tmp = (Vector*) malloc(sizeof(Vector));
    if(tmp == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->data = (float*) malloc(sizeof(float)*num);
    if(tmp->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->capacity = tmp->length = num;
    
    size_t i;
    for(i = 0; i < num; ++i){
        tmp->data[i] = min + (rand()/(float) RAND_MAX) * (max - min);
    }
    
    return tmp;
}

void pop(Vector *v, size_t n){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    v->length = (v->length > n) ? v->length - n : 0;
}

void set_size(Vector *v, size_t cap){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    if(cap < 1){
        printf("The capacity must be greater than 0.\n");
        return;
    }
    
    if(v->capacity == cap){
        return;
    }
    
    v->data = realloc(v->data, sizeof(float)*cap);
    if(v->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    v->capacity = cap;
    if(v->length > cap){
        v->length = cap;
    }
}

void shrink(Vector *v){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t l = v->length;
    if(v->length == 0){
        l = 1;
    }
    
    v->data = realloc(v->data, sizeof(float)*l);
    if(v->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    v->capacity = l;
}

Vector* veccpy(Vector *v){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    Vector *tmp = (Vector*) malloc(sizeof(Vector));
    if(tmp == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->data = (float*) malloc(sizeof(float)*v->capacity);
    if(tmp->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->capacity = v->capacity;
    tmp->length = v->length;
    size_t i;
    for(i = 0; i < v->length; ++i){
        tmp->data[i] = v->data[i];
    }
    
    return tmp;
}

int isEqual(size_t cnt, ...){
    if(cnt < 1){
        printf("The number of parameters must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }
    if(cnt == 1) {
        return 1;
    }
    
    va_list args;
    va_start(args, cnt);
    float c;
    size_t i, j, l = va_arg(args, Vector*)->length;
    
    for(i = 1; i < cnt; ++i){
        if(l != va_arg(args, Vector*)->length){
            return 0;
        }
    }
    va_end(args);
    
    for(i = 0; i < l; ++i){
        va_start(args, cnt);
        c = va_arg(args, Vector*)->data[i];
        for(j = 1; j < cnt; ++j){
            if(c != va_arg(args, Vector*)->data[i]){
                return 0;
            }
        }
        va_end(args);
    }
    
    return 1;
}

Vector* sum(size_t cnt, ...){
    if(cnt < 1){
        printf("The number of parameters must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }
    else if(cnt == 1){
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        push_flt(tmp, 0);
        
        va_list args;
        va_start(args, cnt);
        Vector *t = va_arg(args, Vector*);
        size_t i;
        for(i = 0; i < t->length; ++i){
            tmp->data[0] += t->data[i];
        }
        
        return tmp;
    }
    else{
        va_list args;
        va_start(args, cnt);
        size_t i, j, l = va_arg(args, Vector*)->length;
        for(i = 1; i < cnt; ++i){
            if(l != va_arg(args, Vector*)->length){
                printf("The vectors must have the same length.\n");
                exit(EXIT_FAILURE);
            }
        }
        va_end(args);
        
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        set_size(tmp, l);
        
        for(i = 0; i < l; ++i){
            push_flt(tmp, 0);
            va_start(args, cnt);
            for(j = 0; j < cnt; ++j){
                tmp->data[i] += va_arg(args, Vector*)->data[i];
            }
            va_end(args);
        }
        
        return tmp;
    }
}

Vector* sub(size_t cnt, ...){
    if(cnt < 1){
        printf("The number of parameters must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }
    else if(cnt == 1){
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        
        va_list args;
        va_start(args, cnt);
        Vector *t = va_arg(args, Vector*);
        push_flt(tmp, t->data[0]);
        size_t i;
        for(i = 1; i < t->length; ++i){
            tmp->data[0] -= t->data[i];
        }
        
        return tmp;
    }
    else{
        va_list args;
        va_start(args, cnt);
        size_t i, j, l = va_arg(args, Vector*)->length;
        for(i = 1; i < cnt; ++i){
            if(l != va_arg(args, Vector*)->length){
                printf("The vectors must have the same length.\n");
                exit(EXIT_FAILURE);
            }
        }
        va_end(args);
        
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        set_size(tmp, l);
        
        for(i = 0; i < l; ++i){
            va_start(args, cnt);
            push_flt(tmp, va_arg(args, Vector*)->data[i]);
            for(j = 1; j < cnt; ++j){
                tmp->data[i] -= va_arg(args, Vector*)->data[i];
            }
            va_end(args);
        }
        
        return tmp;
    }
}

Vector* mult(size_t cnt, ...){
    if(cnt < 1){
        printf("The number of parameters must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }
    else if(cnt == 1){
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        push_flt(tmp, 1);
        
        va_list args;
        va_start(args, cnt);
        Vector *t = va_arg(args, Vector*);
        size_t i;
        for(i = 0; i < t->length; ++i){
            tmp->data[0] *= t->data[i];
        }
        
        return tmp;
    }
    else{
        va_list args;
        va_start(args, cnt);
        size_t i, j, l = va_arg(args, Vector*)->length;
        for(i = 1; i < cnt; ++i){
            if(l != va_arg(args, Vector*)->length){
                printf("The vectors must have the same length.\n");
                exit(EXIT_FAILURE);
            }
        }
        va_end(args);
        
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        set_size(tmp, l);
        
        for(i = 0; i < l; ++i){
            push_flt(tmp, 1);
            va_start(args, cnt);
            for(j = 0; j < cnt; ++j){
                tmp->data[i] *= va_arg(args, Vector*)->data[i];
            }
            va_end(args);
        }
        
        return tmp;
    }
}

Vector* divide(size_t cnt, ...){
    if(cnt < 1){
        printf("The number of parameters must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }
    else if(cnt == 1){
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        
        va_list args;
        va_start(args, cnt);
        Vector *t = va_arg(args, Vector*);
        push_flt(tmp, t->data[0]);
        size_t i;
        for(i = 1; i < t->length; ++i){
            tmp->data[0] /= t->data[i];
        }
        
        return tmp;
    }
    else{
        va_list args;
        va_start(args, cnt);
        size_t i, j, l = va_arg(args, Vector*)->length;
        for(i = 1; i < cnt; ++i){
            if(l != va_arg(args, Vector*)->length){
                printf("The vectors must have the same length.\n");
                exit(EXIT_FAILURE);
            }
        }
        va_end(args);
        
        Vector *tmp = (Vector*) malloc(sizeof(Vector));
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        init(tmp);
        set_size(tmp, l);
        
        for(i = 0; i < l; ++i){
            va_start(args, cnt);
            push_flt(tmp, va_arg(args, Vector*)->data[i]);
            for(j = 1; j < cnt; ++j){
                tmp->data[i] /= va_arg(args, Vector*)->data[i];
            }
            va_end(args);
        }
        
        return tmp;
    }
}

void ksum(Vector *v, float k){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t i;
    for(i = 0; i < v->length; ++i){
        v->data[i] += k;
    }
}

void kmult(Vector *v, float k){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t i;
    for(i = 0; i < v->length; ++i){
        v->data[i] *= k;
    }
}

void kpow(Vector *v, float k){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t i;
    for(i = 0; i < v->length; ++i){
        v->data[i] = pow(v->data[i], k);
    }
}

float dot_prod(Vector *v1, Vector *v2){
    if(v1 == NULL){
        printf("The pointer to vector (v1) points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    if(v2 == NULL){
        printf("The pointer to vector (v2) points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    if(v1->length != v2->length){
        printf("The vectors must have the same length.\n");
        exit(EXIT_FAILURE);
    }
    
    float sum = 0;
    size_t i;
    for(i = 0; i < v1->length; ++i){
        sum += (v1->data[i] * v2->data[i]);
    }
    
    return sum;
}

int stdcomp(const void *a, const void *b){
    float x = *(float*)a - *(float*)b;
    if(x < 0){ return -1; }       // a < b
    else if(x == 0){ return 0; }  // a = b
    else{ return 1; }             // a > b
}

void sort(Vector *v, int (*func)(const void*, const void*)){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    qsort(v->data, v->length, sizeof(float), func);
}

void reverse(Vector *v){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t i;
    float tmp;
    
    for(i = 0; i < v->length / 2; ++i){
        tmp = v->data[i];
        v->data[i] = v->data[v->length-i-1];
        v->data[v->length-i-1] = tmp;
    }
}

float max(Vector *v){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t i;
    float max = FLT_MIN;
    
    for(i = 0; i < v->length; ++i){
        if(v->data[i] > max){
            max = v->data[i];
        }
    }
    return max;
}

float min(Vector *v){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t i;
    float min = FLT_MAX;
    
    for(i = 0; i < v->length; ++i){
        if(v->data[i] < min){
            min = v->data[i];
        }
    }
    return min;
}

void print(Vector *v, FILE *f){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    if(f == NULL){
        fprintf(stderr, "The pointer to file points to NULL.\n");
    }
    
    if(v->length < 1){
        return;
    }
    
    size_t i;
    fprintf(f, "%f", v->data[0]);
    for(i = 1; i < v->length; ++i){
        fprintf(f, " %f", v->data[i]);
    }
}

void println(Vector *v, FILE *f){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    if(f == NULL){
        fprintf(stderr, "The pointer to file points to NULL.\n");
    }
    
    if(v->length < 1){
        return;
    }
    
    size_t i;
    fprintf(f, "%f", v->data[0]);
    for(i = 1; i < v->length; ++i){
        fprintf(f, " %f", v->data[i]);
    }
    fprintf(f, "\n");
}

void debug(Vector *v, FILE *f){
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }
    if(f == NULL){
        fprintf(stderr, "The pointer to file points to NULL.\n");
    }
    
    fprintf(f, "Vector pointer: %p\n", v);
    fprintf(f, "Data pointer: %p\n", v->data);
    fprintf(f, "Capacity: %zu. Length: %zu\n", v->capacity, v->length);
    size_t i;
    fprintf(f, "%f", v->data[0]);
    for(i = 1; i < v->length; ++i){
        fprintf(f, " %f", v->data[i]);
    }
    fprintf(f, "\n");
}

#endif // VECTOR_H_INCLUDED
