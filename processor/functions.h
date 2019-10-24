//
// Created by texnar on 23/10/2019.
//

#ifndef PROCESSOR_FUNCTIONS_H
#define PROCESSOR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "math.h"
#include "my_stack.h"

typedef double type_cpu;

const int MAX_NUM_REGISTER = 4;
//#include "/home/texnar/CLionProjects/Interpreter/general_data.h"
#define CPU_MODE
#include "../Assembler/general_data.h"
long ItLength(FILE* file);
unsigned char* Buffering (const char name_file[], long* length);
void Work(unsigned char *data, long length);
void CheckFile(unsigned char **buffer);
void CommandProcessing(Stack_t stack, unsigned char* data, type_cpu* regist, long length);



#endif //PROCESSOR_FUNCTIONS_H

#include "functions.cpp"