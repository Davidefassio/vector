# genVector (Generalized vector)
A generalization to all types of the library vector.h

## Functions
In ALL of the following macros the v is an istance of the struct, NOT a pointer to struct.
#### ```defvec(n, t)```
Define a struct named n with data of type t.
``` C
typedef struct{
    t *data;          // Dynamic array of type t.
    t *_tmp;          // Private temporary pointer.
    size_t capacity;  // Num. of elements that data can hold.
    size_t length;    // Num. of elements that data is holding.
}n;
```

#### ```init(v)```
Initialize the struct holding the vector.

#### ```inBound(v, i)```
Check if i is a valid index of v.data. \
Returns: 1 = valid, 0 = invalid.

#### ```push(v, n)```
Append the element n to the data of v. \
If it exceeds the capacity it resizes the container.

You can define the constant ```#define VECTOR_LINEAR_GROWTH```:
 - if it is defined the capacity is increased by 1 every time;
 - if it is NOT defined the capacity will double every time if it can, if it cannot then the capacity is increased by 1.
 
In every case if it can't increase the capacity even by 1 then it exit with EXIT_FAILURE.

Pushing n elements will result in:
 - O(n^2): slower but uses less space in memory.
 - O(nlogn): much faster and you can use shrink the free the unused space.

#### ```pop(v, n)```
Delete the last n elements from the data of v. \
It only reduces the length by n. \
Does NOT overwrite the date!

#### ```insert(v, n, p)```
Insert the element n at the position p of v.data.

#### ```erase(v, f, l)```
Delete the elements of v.data in the range [f, l).

#### ```resize(v, n)```
Set n as the capacity of v and realloc the data if needed.

#### ```shrink(v)```
Reduce the capacity of v to match the current length.
It's useful to save space in memory.

#### ```reverse(v)```
Reverse the data of v.

#### ```delete(v)```
Free the memory allocated for the data of v.

## License
MIT License \
Copyright (c) 2020 Davide Fassio

## Author
Davide Fassio.

