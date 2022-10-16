#include <stdlib.h>
#include "utils/containers.h"

int pop(stack_t* self){
    if(self->len<0){
        return -1;
    }
    self->len--;
    return self->len;
}

int push(stack_t* self){
    self->len++;
    return self->len;
}


stack_t* make_stack(){
    stack_t* stack = malloc(sizeof(stack_t));
    (*stack).len = 0;
    //stack->push = &push;
    //stack->pop = *pop;
    return  stack;
}
