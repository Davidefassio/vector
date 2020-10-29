//
//  main.c
//  genVector
//
//  Created by Davide Fassio on 28/10/2020.
//  Copyright © 2020 Davide Fassio. All rights reserved.
//

#include <stdio.h>
#include "genvector.h"

defvec(Vector, int);
defvec(Matrix, Vector);

#define print(v) ({size_t i; for(i = 0; i < v.length; ++i) printf("%d ", v.data[i]); printf("\n"); })

int main(int argc, char *argv[]){
    Matrix m; init(m);
    
    int i, j;
    
    for(i = 0; i < 10; ++i){
        Vector tmp; init(tmp);
        push(m, tmp);
        for(j = 0; j < 10; ++j){
            push(m.data[i], i*j);
        }
    }
    
    for(i = 0; i < 10; ++i){
        for(j = 0; j < 10; ++j){
            printf("%2d ", m.data[i].data[j]);
        }
        printf("\n");
    }
    printf("\n");
     
    reverse(m);
    
    for(i = 0; i < 10; ++i){
        for(j = 0; j < 10; ++j){
            printf("%2d ", m.data[i].data[j]);
        }
        printf("\n");
    }
    
    for(i = 0; i < 10; ++i){
        delete(m.data[i]);
    }
    delete(m);
    
    /*Vector v; init(v);
    
    int i;
    for(i = 0; i < 10; ++i){
        push(v, i);
    }
    
    print(v);
    
    insert(v, -1, 4);
    
    print(v);
    
    erase(v, 4, 5);
    
    print(v);
    
    printf("%lu\n", v.capacity);
    shrink(v);
    printf("%lu\n", v.capacity);
    resize(v, 20);
    printf("%lu\n", v.capacity);*/
    
    return 0;
}
