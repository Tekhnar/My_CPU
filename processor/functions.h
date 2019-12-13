//
// Created by texnar on 23/10/2019.
//
//#pragma warn -Wmultichar

#ifndef PROCESSOR_FUNCTIONS_H
#define PROCESSOR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "math.h"
#include "my_stack.h"

#include "TXLin.h"

typedef double type_cpu;

const int MAX_NUM_REGISTER = 4;
const int SIZE_RAM = 1440500;

const long WINDOW_LENGTH = 600; //Length
const long WINDOW_WIGTH = 800; //Length


#define CPU_MODE
#include "../Assembler/general_data.h"
long ItLength(FILE* file);
unsigned char* Buffering (int num_arg, char *poin_arg[], long* length);
void Work(unsigned char *data, long length);
void CheckFile(unsigned char **buffer);
void CommandProcessing(Stack_t* stack, unsigned char* data,
        type_cpu* regist, long length, unsigned char* ram);
FILE* OpenFile(int num_arg, char *poin_arg[]);

void FunctionPUSHCpu(Stack_t* stack, unsigned char** IP,
        type_cpu* registers, unsigned char* ram);
void FunctionPOPCpu(Stack_t* stack, unsigned char** IP,
        type_cpu** registers, unsigned char* ram);
void FunctionUPDCpu(unsigned char** IP, unsigned char* ram, RGBQUAD** main_window);
void FunctionROUCpu(Stack_t* stack, unsigned char** IP);

unsigned char* ConstructRAM();
void DestructRAM(unsigned char* ram);

#include "functions.cpp"

#endif //PROCESSOR_FUNCTIONS_H
