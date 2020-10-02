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

typedef struct{
    float *data;
    size_t capacity;
    size_t length;
}Vector;

void init(Vector *v){
    v->data = (float*) malloc(sizeof(float));
    if(v->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    v->capacity = 1;
    v->length = 0;
}

void push_float(Vector *v, float n){
    if(v->length < v->capacity){
        v->data[v->length] = n;
        ++v->length;
    }
    else{
        v->capacity *= 2;
        float *tmp = (float*) malloc(sizeof(float)*v->capacity);
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        size_t i;
        for(i = 0; i < v->length; ++i){
            tmp[i] = v->data[i];
        }
        tmp[i] = n;
        ++v->length;
        
        free(v->data);
        v->data = tmp;
    }
}

void push_arr(Vector *v, float *arr, size_t n){
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
        
        float *tmp = (float*) malloc(sizeof(float)*v->capacity);
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        
        size_t i;
        for(i = 0; i < v->length; ++i){
            tmp[i] = v->data[i];
        }
        for(i = 0; i < n; ++i){
            tmp[v->length+i] = arr[i];
        }
        v->length += n;
        
        free(v->data);
        v->data = tmp;
    }
}

void pop(Vector *v, size_t n){
    v->length = (v->length > n) ? v->length - n : 0;
}

void set_size(Vector *v, size_t cap){
    if(cap < 1){
        printf("The capacity must be greater than 0.\n");
        return;
    }
    if(v->capacity < cap){
        v->capacity = cap;
        float *tmp = (float*) malloc(sizeof(float)*cap);
        if(tmp == NULL){
            printf("An error occurred during allocation of memory.\n");
            exit(EXIT_FAILURE);
        }
        
        size_t i;
        for(i = 0; i < v->length; ++i){
            tmp[i] = v->data[i];
        }
        
        free(v->data);
        v->data = tmp;
    }
    else if(v->capacity > cap){
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
}

void shrink(Vector *v){
    v->data = realloc(v->data, sizeof(float)*v->length);
    if(v->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    v->capacity = v->length;
}

Vector* veccpy(Vector *v){
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
        push_float(tmp, 0);
        
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
            push_float(tmp, 0);
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
        push_float(tmp, t->data[0]);
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
            push_float(tmp, va_arg(args, Vector*)->data[i]);
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
        push_float(tmp, 1);
        
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
            push_float(tmp, 1);
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
        push_float(tmp, t->data[0]);
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
            push_float(tmp, va_arg(args, Vector*)->data[i]);
            for(j = 1; j < cnt; ++j){
                tmp->data[i] /= va_arg(args, Vector*)->data[i];
            }
            va_end(args);
        }
        
        return tmp;
    }
}

Vector* ksum(Vector *v, float k){
    Vector *tmp = (Vector*) malloc(sizeof(Vector));
    if(tmp == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->data = (float*) malloc(sizeof(float)*v->length);
    if(tmp->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->capacity = v->length;
    tmp->length = v->length;
    size_t i;
    for(i = 0; i < v->length; ++i){
        tmp->data[i] = v->data[i] + k;
    }
    
    return tmp;
}

Vector* kmult(Vector *v, float k){
    Vector *tmp = (Vector*) malloc(sizeof(Vector));
    if(tmp == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->data = (float*) malloc(sizeof(float)*v->length);
    if(tmp->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->capacity = v->length;
    tmp->length = v->length;
    size_t i;
    for(i = 0; i < v->length; ++i){
        tmp->data[i] = v->data[i] * k;
    }
    
    return tmp;
}

Vector* kpow(Vector *v, float k){
    Vector *tmp = (Vector*) malloc(sizeof(Vector));
    if(tmp == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->data = (float*) malloc(sizeof(float)*v->length);
    if(tmp->data == NULL){
        printf("An error occurred during allocation of memory.\n");
        exit(EXIT_FAILURE);
    }
    
    tmp->capacity = v->length;
    tmp->length = v->length;
    size_t i;
    for(i = 0; i < v->length; ++i){
        tmp->data[i] = pow(v->data[i], k);
    }
    
    return tmp;
}

int dot_prod(Vector *v1, Vector *v2){
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

void print(Vector *v, FILE *f){
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

#endif // VECTOR_H_INCLUDED
