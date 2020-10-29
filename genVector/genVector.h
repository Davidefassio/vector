/**
 *  MIT License
 *  Copyright (c) 2020 Davide Fassio
 */

#ifndef GENVECTOR_H
#define GENVECTOR_H

// Include some standard libraries.
#include <stdlib.h>
#include <string.h>


/**
 *  Define the struct holding the vector.
 *  Parameters:
 *   - n => name of the struct;
 *   - t => type of elements in data.
 */
#define defvec(n, t) \
typedef struct{      \
    t *data;         \
    size_t size;     \
    size_t capacity; \
    size_t length;   \
}n;


/**
 *  Initialize the struct holding the vector.
 *  Parameters:
 *   - v => istance of vector;
 */
#define init(v) ({        \
v.size = sizeof(*v.data); \
v.data = malloc(v.size);  \
v.capacity = 1;           \
v.length = 0; })


/**
 *  Return true if the index is in [0, data length).
 *  Parameters:
 *   - v => istance of vector;
 *   - i => index to check.
 */
#define inBound(v, i) (i >= 0 && i < v.length) ? 1 : 0


/**
 *  Append an element to the end of the vector.
 *  Parameters:
 *   - v => istance of vector;
 *   - n => element to append. (stable)
 */
#define push(v, n) ({                                 \
if(v.length < v.capacity) v.data[(v.length)++] = (n); \
else{                                                 \
    v.capacity *= 2;                                  \
    v.data = realloc(v.data, v.size * v.capacity);    \
    v.data[(v.length)++] = (n);                       \
} })


/**
 *  Delete the last n elements.
 *  Does NOT cancel the data.
 *  Parameters:
 *   - v => istance of vector;
 *   - n => number of elements to be deleted.
 */
#define pop(v, n) ({ v.length = (v.length > n) ? v.length - n : 0; })


/**
 *  Insert an element in a given position.
 *  Paramaters:
 *   - v => istance of vector;
 *   - n => element to insert; (stable)
 *   - p => position in which insert the element.
 */
#define insert(v, n, p) ({                                   \
if(p == v.length) push(v, (n));                              \
else if(!inBound(v, p)) exit(EXIT_FAILURE);                  \
else{                                                        \
    size_t i; push(v, v.data[v.length-1]);                   \
    for(i = v.length-2; i > p; --i) v.data[i] = v.data[i-1]; \
    v.data[p] = (n);                                         \
} ++v.length; })


/**
 *  Erase the elements in the range [firts, last).
 *  Parameters:
 *   - v => istance of vector;
 *   - f => first (included);
 *   - l => last (excluded).
 */
#define erase(v, f, l) ({                                               \
if(l == v.length) v.length -= (l - f);                                  \
else if(!inBound(v, f) || !inBound(v, l)) exit(EXIT_FAILURE);           \
else{                                                                   \
    size_t i;                                                           \
    for(i = f; i < l && i + l - f < v.length; ++i) v[i] = v[i + l - f]; \
    v-length -= (l - f);                                                \
} })



/**
 *  Set n as the new capacity.
 *  If n is gt the current capacity a reallocation occurs.
 *  Parameters:
 *   - v => istance of vector;
 *   - n => new capacity (in elements).
 */
#define resize(v, n) ({                   \
if(n > 0 && v.capacity != n){             \
    v.data = realloc(v.data, v.size * n); \
    v.capacity = n;                       \
    if(v.length > n) v.length = n;        \
} })


/**
 *  Reduce the capacity to match the current length
 *  Parameters:
 *   - v => istance of vector.
 */
#define shrink(v) ({                        \
size_t l = (v.length == 0) ? 1 : v->length; \
v.data = realloc(v.data, v.size * l);       \
v.capacity = l; })


/**
 *  Reverse the data array.
 *  Parameters:
 *   - v => istance of vector.
 */
#define reverse(v) ({                                      \
size_t i; void *tmp = malloc(v.size);                      \
for(i = 0; i < v.length / 2; ++i){                         \
    memcpy(tmp, v.data + i, v.size);                       \
    memcpy(v.data + i, v.data + v.length - i - 1, v.size); \
    memcpy(v.data + v.length - i - 1, tmp, v.size);        \
} free(tmp); })


/**
 *  Free the memory allocated for the data
 *  and for the vector.
 *  Parameters:
 *   - v => istance of vector.
 */
#define delete(v) free(v.data)


#endif /* GENVECTOR_H */
