//
// Created by texnar on 11/10/2019.
//

#ifndef INTERPRETER_GENERAL_DATA_H
#define INTERPRETER_GENERAL_DATA_H

const int MAX_NUM_JMP = 10;

struct commands {
    #define DEF_CMD(name, num, code)\
       unsigned int hash_##name;
    #include "commands.h"

    #undef DEF_CMD

#ifndef CPU_MODE

    #define REGISTER(name, num)\
        unsigned int hash_reg_##name;

    #include "register.h"

    #undef REGISTER

#endif
};


/*
enum code {
    END,
    PUSH,
    POP,
    ADD,
    SUB,
    DIV,
    MUL,
    SQRT,
    SIN,
    COS,
    POW
};
*/

#define DEF_CMD(name, num, code)\
    const unsigned char cmd_##name = num;
    #include "commands.h"

#undef DEF_CMD

char VERSION = 1;

#endif //INTERPRETER_GENERAL_DATA_H
