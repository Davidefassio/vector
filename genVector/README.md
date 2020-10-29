# genvector (Generalized vector)
A generalization to all types of the library vector.h

## Functions
#### ```defvec(n, t)```
Define a struct named n with data of type t.
``` C
typedef struct{
    t *data;          // Dynamic array of type t.
    size_t size;      // Size in Bytes of t.
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
If it exceeds the capacity it resizes the container. \
The new capacity is twice the old, so in the long run \
the cost of the function is logarithmic and not linear. 

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

