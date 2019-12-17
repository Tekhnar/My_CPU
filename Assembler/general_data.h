//
// Created by texnar on 11/10/2019.
//

#ifndef INTERPRETER_GENERAL_DATA_H
#define INTERPRETER_GENERAL_DATA_H

const int MAX_NUM_JMP = 1000;

const unsigned char WRITE_NUM = 0xAA;
const unsigned char WRITE_REG = 0xBB;
const unsigned char WRITE_NOTHING = 0xCC;
const unsigned char RAM_NUM = 0xDD;
const unsigned char RAM_REG = 0xEE;
const unsigned char RAM_REG_CHAR = 0xEF;
const unsigned char RAM_NUM_CHAR = 0xFE;


struct commands {
    #define DEF_CMD(name, num, code, code_cpu)\
       unsigned int hash_##name;
    #include "commands.h"

    #undef DEF_CMD

#ifndef CPU_MODE

    #define REGISTER(name, num)\
        unsigned int hash_reg_##name;

//    #include "register.h"
    #include "../Assembler/register.h"

    #undef REGISTER

#endif
};


#define DEF_CMD(name, num, code, code_cpu)\
    const unsigned char cmd_##name = num;
    #include "commands.h"

#undef DEF_CMD

char VERSION = 2;

#endif //INTERPRETER_GENERAL_DATA_H
