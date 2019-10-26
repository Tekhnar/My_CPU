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
const int SIZE_RAM = 1000000;

#define CPU_MODE
#include "../Assembler/general_data.h"
long ItLength(FILE* file);
unsigned char* Buffering (const char name_file[], long* length);
void Work(unsigned char *data, long length);
void CheckFile(unsigned char **buffer);
void CommandProcessing(Stack_t stack, unsigned char* data, type_cpu* regist, long length, unsigned char* ram);

unsigned char* ConstructRAM();
void DestructRAM(unsigned char* ram);

#include "functions.cpp"

#endif //PROCESSOR_FUNCTIONS_H
