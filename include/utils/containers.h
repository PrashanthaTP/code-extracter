#ifndef CONTAINERS_H

struct stack_st {
    unsigned int len;
   // int (*pop)(struct stack* self);
    //int (*push)(struct stack* self);
};

typedef struct stack_st stack_t;

int pop(stack_t* self);
int push(stack_t* self);
stack_t* make_stack(void);
#endif //CONTAINERS_H
