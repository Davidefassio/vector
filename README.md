# vector
Implementation of std::vector in C.

## Data structure
``` C
typedef struct{
    int *data;    // Pointer to the array
    int capacity; // Actual capacity of the array
    int length;   // Number of elements inserted (using push_int / push_arr)
}Vector;
```

## Functions
```void init(Vector*)``` \
EVERY vector must be initialized using this function (recommended) or manually.

```void push_int(Vector*, int)``` \
Append a number (int) at the end of the vector, if it exceeds the capacity it's resized automatically doubling the capacity. 

```void push_arr(Vector*, int*, int)``` \
Append an array of int of length n at the end of the vector, if it exceeds the capacity it's resized automatically doubling it until it fit. 

```void pop(Vector*, int)``` \
Delete the last n elements of the vector. The capacity remain unchaged.

```void set_size(Vector*, int)``` \
Set a given capacity. If it's less than the length than some data will be lost. Useful when is known in advance the capacity needed and so it reduces the reallocation happening in push_int.

```void shrink(Vector*)``` \
Reduce the capacity of the vector to match the length and so reducing the memory wasted.

```void veccpy(Vector*)``` \
Copy a vector and return another istance equivalent in data, capacity and length.

```int isEqual(Vector*, Vector*)``` \
Check if two vectors are equal. It return 0 (false) or 1 (true).

```Vector* sum(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.


```Vector* sub(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.


```Vector* mult(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.

```Vector* ksum(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.


```Vector* kmult(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.


```Vector* kpow(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.


```Vector* dot_prod(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.

```void print(Vector*, FILE*)``` 
Print on a file the vector.

```void println(Vector*, FILE*)``` 
Print on a file the vector.

## License
MIT License \
Copyright (c) 2020 Davide Fassio

## Author
Davide Fassio.
