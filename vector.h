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

void push_float(Vector *v, float n){
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
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }

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
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }

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
    if(v == NULL){
        printf("The pointer to vector points to NULL.\n");
        exit(EXIT_FAILURE);
    }

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

void debug(Vector *v){
    printf("Vector pointer: %p\n", v);
    printf("Data pointer: %p\n", v->data);
    printf("Capacity: %u. Length: %u\n", v->capacity, v->length);
    size_t i;
    printf("%f", v->data[0]);
    for(i = 1; i < v->length; ++i){
        printf(" %f", v->data[i]);
    }
    printf("\n");
}

#endif // VECTOR_H_INCLUDED
