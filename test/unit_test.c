#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"

int main() {
    /// ########################### INIT ###########################
    Vector v1;
    init(&v1);
    assert(&v1 != NULL);
    assert(v1.data != NULL);
    assert(v1.capacity == 1);
    assert(v1.length == 0);

    Vector *v2 = NULL;
    v2 = init(v2);
    assert(v2 != NULL);
    assert(v2->data != NULL);
    assert(v2->capacity == 1);
    assert(v2->length == 0);


    Vector *v3 = malloc(sizeof(Vector));
    init(v3);
    assert(v3 != NULL);
    assert(v3->data != NULL);
    assert(v3->capacity == 1);
    assert(v3->length == 0);

    /// ######################## PUSH_FLOAT ########################

    /// ######################### PUSH_ARR #########################

    /// ########################### POP ############################

    /// ######################### SET_SIZE #########################

    /// ########################## SHRINK ##########################

    /// ########################## VECCPY ##########################


    return 0;
}
