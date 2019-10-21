//
// Created by texnar on 11/10/2019.
//

#ifndef INTERPRETER_GENERAL_DATA_H
#define INTERPRETER_GENERAL_DATA_H
struct commands {
    #define DEF_CMD(name, str, num, code)\
       unsigned int hash_##name;
    #include "commands.h"

    #undef DEF_CMD


    #define REGISTER(name, str, num)\
        unsigned int hash_reg_##name;

    #include "register.h"

    #undef REGISTER
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

#define DEF_CMD(name, str, num, code)\
    unsigned char cmd_##name = num;
    #include "commands.h"

#undef DEF_CMD

char VERSION = 1;

#endif //INTERPRETER_GENERAL_DATA_H
