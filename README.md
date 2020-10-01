# vector
Implementation of std::vector in C.

## Functions
```void init(Vector*)``` \
EVERY vector must be initialized usign this function (recommended) or manually.

```void push_int(Vector*, int)``` \
Append a number (int) at the end of the vector, if it exceeds the capacity it's resized automatically doubling the capacity. 

```void pop(Vector*, int)``` \
Delete the last n elements of the vector. The capacity remain unchaged.

```void set_size(Vector*, int)``` \
Set a given capacity. If it's less than the length than some data will be lost. Useful when is known in advance the capacity needed and so it reduces the reallocation happening in push_int.

```void shrink(Vector*)``` \
Reduce the capacity of the vector to match the length and so reducing the memory wasted.

```int isEqual(Vector*, Vector*)``` \
Check if two vectors are equal. It return 0 (false) or 1 (true).

```Vector* sum(Vector*, Vector*)``` \
Sum two vectors and returns a vector already initialized containing the sum element by element.

```void print(Vector*, FILE*)``` 
Print on a file the vector.

## License
MIT License \
Copyright (c) 2020 Davide Fassio

## Author
Davide Fassio.
