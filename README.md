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
Vector returned by other functions of this library are already initialized.

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

```int isEqual(int cnt, ...)``` \
Check if two vectors are equal in length and in the data, NOT in capacity. It return 0 (false) or 1 (true).

```Vector* sum(int cnt, ...)``` \
cnt is the number of elements that follow.
If cnt == 1 sum all the element of the vector and return a vector with length and capacity of 1 and data[0] that contains the sum.
If cnt > 1 

```Vector* sub(int cnt, ...)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.

```Vector* mult(int cnt, ...)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.

```Vector* ksum(Vector*, int)``` \
Sum the int given to all the elements of the vector, storing the result in the vector returned.

```Vector* kmult(Vector*, int)``` \
Multiply the int given by all the elements of the vector, storing the result in the vector returned.

```Vector* kpow(Vector*, int)``` \
Elevate to the int given all the elements of the vector, storing the result in the vector returned.

```int dot_prod(Vector*, Vector*)``` \
Dot product between two vectors of the same length. Return an int containing the result.

```void print(Vector*, FILE*)``` \
Print on a file the vector.

```void println(Vector*, FILE*)``` \
Print on a file the vector and the new line character.

## License
MIT License \
Copyright (c) 2020 Davide Fassio

## Author
Davide Fassio.
