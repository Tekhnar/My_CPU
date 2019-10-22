//
// Created by texnar on 22/10/2019.
//
#include "my_stack.h"

/*

#ifndef PROCESSOR_COMMANDS_CPU_H
#define PROCESSOR_COMMANDS_CPU_H

#endif //PROCESSOR_COMMANDS_CPU_H

*/

DEF_CMD(end, 0, {
    double tmp = -1;
    StackPop(&stack, &tmp);
    printf("Last number %lg\n", tmp);
    return ;
})

DEF_CMD(push, 1, {
    if (IP[1] == 0xAA){
        type_cpu temp_num = *(type_cpu*)(IP + 2);
        StackPush(&stack, temp_num);
        IP += sizeof(type_cpu) + 2 * sizeof(char);
    }
    else if (IP[1] == 0xBB) {
        StackPush(&stack, registers[IP[2]]);
        IP += 3 * sizeof(char);
    } else {
        printf("Error in argument of 'push'!\n");
        abort();
    }
})

DEF_CMD(pop, 2, {
    if (IP[1] == 0xBB){
        //type_cpu temp_num = *(type_cpu*)(IP + 2);
        StackPop(&stack, &registers[IP[2]]);
        IP += 3 * sizeof(char);
    }
    else if (IP[1] == 0xCC) {
        double tmp = -1;
        StackPop(&stack, &tmp);
        IP += 2 * sizeof(char);
    } else {
        printf("Error in argument of 'pop'!\n");
        abort();
    }
})

DEF_CMD(add, 3, {
    double tmp1 = 0;
    double tmp2 = 0;
    StackPop(&stack, &tmp1);
    StackPop(&stack, &tmp2);
    StackPush(&stack, tmp1 + tmp2);
    IP += sizeof(char);
})

DEF_CMD(sub, 4, {
    double tmp1 = 0;
    double tmp2 = 0;
    StackPop(&stack, &tmp1);
    StackPop(&stack, &tmp2);
    StackPush(&stack, tmp2 - tmp1);
    IP += sizeof(char);
})

DEF_CMD(div, 5, {
    double tmp1 = 0;
    double tmp2 = 0;
    StackPop(&stack, &tmp1);
    StackPop(&stack, &tmp2);
    StackPush(&stack, tmp2 / tmp1);
    IP += sizeof(char);
})

DEF_CMD(mul, 6, {
    double tmp1 = 0;
    double tmp2 = 0;
    StackPop(&stack, &tmp1);
    StackPop(&stack, &tmp2);
    StackPush(&stack, tmp2 * tmp1);
    IP += sizeof(char);
})

DEF_CMD(sqrt, 7, {
    double tmp1 = 0;
    StackPop(&stack, &tmp1);
    StackPush(&stack, sqrt(tmp1));
    IP += sizeof(char);
})

DEF_CMD(sin, 8, {
    double tmp1 = 0;
    StackPop(&stack, &tmp1);
    StackPush(&stack, sin(tmp1));
    IP += sizeof(char);
})

DEF_CMD(cos, 9, {
    double tmp1 = 0;
    StackPop(&stack, &tmp1);
    StackPush(&stack, cos(tmp1));
    IP += sizeof(char);
})

DEF_CMD(pow, 10, {
    double tmp1 = 0;
    double tmp2 = 0;
    StackPop(&stack, &tmp1);
    StackPop(&stack, &tmp2);
    StackPush(&stack, pow(tmp2, tmp1));
    IP += sizeof(char);
})
