# vector
Implementation of std::vector in C.

## Data structure
``` c
typedef struct{
    float *data;     // Pointer to the array
    size_t capacity; // Actual capacity of the array
    size_t length;   // Number of elements inserted (using push_int / push_arr)
}Vector;
```

## Functions
```void init(Vector*)``` \
EVERY vector must be initialized using this function (recommended) or manually.
Vector returned by other functions of this library are already initialized.

```void push_float(Vector*, float)``` \
Append a number (float) at the end of the vector, if it exceeds the capacity it's resized automatically doubling the capacity. 

```void push_arr(Vector*, float*, size_t)``` \
Append an array of float of length n at the end of the vector, if it exceeds the capacity it's resized automatically doubling it until it fit. 

```void pop(Vector*, size_t)``` \
Delete the last n elements of the vector. The capacity remain unchaged.

```void set_size(Vector*, size_t)``` \
Set a given capacity. If it's less than the length than some data will be lost. \
Useful when is known in advance the capacity needed and so it reduces the reallocation happening in push_float.

```void shrink(Vector*)``` \
Reduce the capacity of the vector to match the length and so reducing the memory wasted.

```void veccpy(Vector*)``` \
Copy a vector and return another istance equivalent in data, capacity and length.

```int isEqual(size_t cnt, ...)``` \
cnt is the number of elements that follows. \
If cnt == 1 retrun 1 (true). \
If cnt > 1 check if the vectors have equal length and v1[i] == v2[i] == ... for each i. If it's true return 1, otherwise 0.

```Vector* sum(size_t cnt, ...)```  \
cnt is the number of elements that follows. \
If cnt == 1 sum all the element of the vector and return a vector with length and capacity of 1 and data[0] that contains the sum. \
If cnt > 1 sum all the vectors element by element and return a vector with capacity equals to the length and data[i] = v1[i] + v2[i] + ...

```Vector* sub(size_t cnt, ...)``` \
cnt is the number of elements that follows. \
If cnt == 1 subtract all the element of the vector to the first and return a vector with length and capacity of 1 and data[0] that contains the result. \
If cnt > 1 subtract all the vectors element by element to the first vector and return a vector with capacity equals to the length and data[i] = v1[i] - v2[i] - ...

```Vector* mult(size_t cnt, ...)``` \
cnt is the number of elements that follows. \
If cnt == 1 multiply all the element of the vector by each other and return a vector with length and capacity of 1 and data[0] that contains the result. \
If cnt > 1 multiply all the vectors element by element by each other and return a vector with capacity equals to the length and data[i] = v1[i] * v2[i] * ...

```Vector* divide(size_t cnt, ...)``` \
cnt is the number of elements that follows. \
If cnt == 1 divide the first element by all the others and return a vector with length and capacity of 1 and data[0] that contains the result. \
If cnt > 1 divide the first vector element by element by all others and return a vector with capacity equals to the length and data[i] = v1[i] / v2[i] / ...

```Vector* ksum(Vector*, float)``` \
Sum the float given to all the elements of the vector, storing the result in the vector returned.

```Vector* kmult(Vector*, float)``` \
Multiply the float given by all the elements of the vector, storing the result in the vector returned.

```Vector* kpow(Vector*, float)``` \
Elevate to the float given all the elements of the vector, storing the result in the vector returned.

```float dot_prod(Vector*, Vector*)``` \
Dot product between two vectors of the same length. Return a float containing the result.

```void print(Vector*, FILE*)``` \
Print on a file the vector.

```void println(Vector*, FILE*)``` \
Print on a file the vector and the new line character.

## License
MIT License \
Copyright (c) 2020 Davide Fassio

## Author
Davide Fassio.
