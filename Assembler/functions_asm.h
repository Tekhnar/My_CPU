//
// Created by texnar on 23/10/2019.
//

#ifndef ASSEMBLER_FUNCTIONS_ASM_H
#define ASSEMBLER_FUNCTIONS_ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include "general_data.h"

struct jumps{
    long address_jump_to;
    bool used_jump;
};

long ItLength(FILE* file);
void CountConstHash(commands* consthash);
void CommandProcessing (char* buffer, char* data, long length, commands* com, long* write_point);
unsigned int MurmurHash(const char text[]);
void FindRegister(commands* com, char str_reg[], unsigned int hash_read_reg, char* num_reg, int num_enter);

void FunctionJMP(char** data, long* write_point, jumps array_jumps[],
        commands* com, int* pointer_read, char* first_symb, int num_enter);
void FindLabelJMP(char** data, long* write_point, jumps array_jumps[],
        int* pointer_read, char* first_symb, int num_enter);
void FunctionCALL(char** data, long* write_point, jumps array_jumps[],
        int* pointer_read, char* first_symb, int num_enter);
void FunctionPUSH(char** data, long* write_point, jumps array_jumps[],
        commands* com, int* pointer_read, char* first_symb, int num_enter);
void FunctionPOP(char** data, long* write_point, jumps array_jumps[],
        commands* com, int* pointer_read, char* first_symb, int num_enter);

FILE* OpenFile(int num_arg, char *poin_arg[]);

FILE* ConvertFile(FILE* file, commands* com, int num_arg, char *poin_arg[],
        const char name_file[] = "../workspace_for_processor/CODE.txt");


#include "functions_asm.cpp"

#endif //ASSEMBLER_FUNCTIONS_ASM_H
