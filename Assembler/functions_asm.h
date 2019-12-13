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
void FunctionPUSH(char** data, long* write_point,
        commands* com, int* pointer_read, char* first_symb, int num_enter);
void FunctionPOP(char** data, long* write_point,
        commands* com, int* pointer_read, char* first_symb, int num_enter);

void SearchEmptyLine(char* command, bool* known_command, jumps array_jumps[], long *write_point);
void ReturnTextToOriginal(int* num_enter, char* comment, char** last_symb);
void SearchLabel(char* command, bool* known_command);
void SearchEndOfLine(char** last_symb, char* first_symb,
                     char* buffer, char** comment, long length);
void FuncJmpToNum(char** data, long* write_point,
                  jumps array_jumps[], commands* com, int* pointer_read,
                  char* first_symb, int num_enter, long* num_jmp, char* jmp_symbol);
void FuncJmpToReg(char** data, long* write_point,
                  commands* com, int* pointer_read, char* first_symb, int num_enter);

void WriteInFile(int num_arg,char** poin_arg, char* data, long write_point, const char* name_file);
inline void FreeMemory(char* buffer, char* data);
inline void CheckVersion(char* data, long* write_point);

bool SearchTypeRam(int* pointer_read, char* first_symb);



FILE* OpenFile(int num_arg, char *poin_arg[]);
inline void CloseFile(FILE* file);

FILE* ConvertFile(FILE* file, commands* com, int num_arg, char *poin_arg[],
        const char name_file[] = "../workspace_for_processor/CODE.txt");


#include "functions_asm.cpp"

#endif //ASSEMBLER_FUNCTIONS_ASM_H
