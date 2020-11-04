/**
 *  MIT License
 *  Copyright (c) 2020 Davide Fassio
 */

#ifndef GENVECTOR_H
#define GENVECTOR_H

#ifdef __cplusplus  // C++ code

#include <cstdlib>
extern "C" {
    
#else               // C code
    
#include <stdlib.h>
    
#endif /* __cplusplus */
    
    
/**
 *  Define the struct holding the vector.
 *  Parameters:
 *   - n => name of the struct;
 *   - t => type of elements in data.
 */
#define defvec(n, t) \
typedef struct{      \
    t *data;         \
    t *_tmp;         \
    size_t capacity; \
    size_t length;   \
}n;
    
    
/**
 *  Initialize the struct holding the vector.
 *  Parameters:
 *   - v => istance of vector;
 */
#define init(v) ({                 \
v.data = malloc(sizeof(*v.data));  \
v._tmp = NULL;                     \
v.capacity = 1;                    \
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
 *
 *  If the constant VECTOR_LINEAR_GROWTH is defined the capacity
 *  is increased only by 1 every time.
 *  If it's not defined then the capacity doubles every time if it can
 *  (resulting in a logarithmic complexity rather than a linear),
 *  if it can't then is increased only by 1.
 *  In every case if it can't increase the capacity even by 1 then
 *  it exit with EXIT_FAILURE.
 *
 *  Parameters:
 *   - v => istance of vector;
 *   - n => element to append. (stable)
 */
#ifdef VECTOR_LINEAR_GROWTH
    
#define push(v, n) ({                                         \
if(v.length >= v.capacity){                                   \
    v.data = realloc(v.data, sizeof(*v.data) * ++v.capacity); \
    if(v.data == NULL) exit(EXIT_FAILURE);                    \
} v.data[(v.length)++] = (n); })
    
#else
    
#define push(v, n) ({                                             \
if(v.length >= v.capacity){                                       \
    v.capacity *= 2;                                              \
    v._tmp = realloc(v.data, sizeof(*v.data) * v.capacity);       \
    if(v._tmp == NULL){                                           \
        v.capacity /= 2;                                          \
        v._tmp = realloc(v.data, sizeof(*v.data) * ++v.capacity); \
        if(v._tmp == NULL) exit(EXIT_FAILURE);                    \
    }                                                             \
    v.data = v._tmp;                                              \
} v.data[(v.length)++] = (n); })
    
#endif /* VECTOR_LINEAR_GROWTH */
    
    
/**
 *  Delete the last n elements.
 *  Does NOT cancel or obfuscate the data.
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
} })
    
    
/**
 *  Erase the elements in the range [firts, last).
 *  Parameters:
 *   - v => istance of vector;
 *   - f => first (included);
 *   - l => last (excluded).
 */
#define erase(v, f, l) ({ \
if(l < f) exit(EXIT_FAILURE);                                 \
else if(l == v.length) v.length -= (l - f);                   \
else if(!inBound(v, f) || !inBound(v, l)) exit(EXIT_FAILURE); \
else{                                                         \
    size_t i;                                                 \
    for(i = f; i + l - f < v.length; ++i)                     \
        v.data[i] = v.data[i + l - f];                        \
    v.length -= (l - f);                                      \
} })
    
    
/**
 *  Set n as the new capacity.
 *  If n is gt the current capacity a reallocation occurs.
 *  Parameters:
 *   - v => istance of vector;
 *   - n => new capacity (in elements).
 */
#define resize(v, n) ({                            \
if(n > 0 && v.capacity != n){                      \
    v.data = realloc(v.data, sizeof(*v.data) * n); \
    v.capacity = n;                                \
    if(v.length > n) v.length = n;                 \
} })
    
    
/**
 *  Reduce the capacity to match the current length
 *  Parameters:
 *   - v => istance of vector.
 */
#define shrink(v) ({                               \
if(v.capacity != v.length){                        \
    size_t l = (v.length == 0) ? 1 : v.length;     \
    v.data = realloc(v.data, sizeof(*v.data) * l); \
    v.capacity = l;                                \
} })
    
    
/**
 *  Reverse the data array.
 *  Parameters:
 *   - v => istance of vector.
 */
#define reverse(v) ({                             \
size_t i; v._tmp = malloc(sizeof(*v._tmp));       \
for(i = 0; i < v.length / 2; ++i){                \
    *(v._tmp) = *(v.data + i);                    \
    *(v.data + i) = *(v.data + v.length - i - 1); \
    *(v.data + v.length - i - 1) = *(v._tmp);     \
} free(v._tmp); })
    
    
/**
 *  Free the memory allocated for the data.
 *  Parameters:
 *   - v => istance of vector.
 */
#define delete(v) free(v.data)
    
    
#ifdef __cplusplus  // Close the open bracket from extern "C"
}
#endif /* __cplusplus */

#endif /* GENVECTOR_H */
