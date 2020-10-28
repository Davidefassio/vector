/**
 *  MIT License
 *  Copyright (c) 2020 Davide Fassio
 */

#ifndef GENVECTOR_H
#define GENVECTOR_H

#include <stdlib.h>

/**
 *  Define the struct holding the vector.
 *  Parameters:
 *   - n => name of the struct;
 *   - t => type of elements in data.
 */
#define defvec(n, t) \
typedef struct{ \
t *data; \
size_t size; \
size_t capacity; \
size_t length; \
}n;


/**
 *  Initialize the struct holding the vector.
 *  Parameters:
 *   - v => pointer to vector;
 */
#define init(v) ({ \
v->size = sizeof(*v->data); \
v->data = malloc(v->size); \
v->capacity = 1; \
v->length = 0; })


/**
 *  Append an element to the end of the vector.
 *  Parameters:
 *   - v => pointer to vector;
 *   - elem => element to append.
 */
#define push(v, elem) ({ \
if(v->length < v->capacity) v->data[(v->length)++] = (elem); \
else{ \
    v->capacity *= 2; \
    v->data = realloc(v->data, v->size*v->capacity); \
    v->data[(v->length)++] = (elem); } })


/**
 *  Delete the last n elements.
 *  Does NOT cancel the data.
 *  Parameters:
 *   - v => pointer to vector;
 *   - n => number of elements to be deleted.
 */
#define pop(v, n) ({ v->length = (v->length > n) ? v->length - n : 0; })


/**
 *  Set n as the new capacity.
 *  If n is gt the current capacity a reallocation occurs.
 *  Parameters:
 *   - v => pointer to vector;
 *   - n => new capacity (in elements).
 */
#define resize(v, n) ({ \
if(n > 0 && v->capacity != n){ \
    v->data = realloc(v->data, v->size*n); \
    v->capacity = n; \
    if(v->length > n){ v->length = n; }}


/**
 *  Reduce the capacity to match the current length
 *  Parameters:
 *   - v => pointer to vector.
 */
#define shrink(v) ({ \
size_t l = (v->length == 0) ? 1 : v->length; \
v->data = realloc(v->data, v->size*l); \
v->capacity = l; })

/**
 *  Free the memory allocated for the data
 *  and for the vector.
 *  Parameters:
 *   - v => pointer to vector.
 */
#define delete(v) ({ free(v->data); free(v); })

#endif /* GENVECTOR_H */
