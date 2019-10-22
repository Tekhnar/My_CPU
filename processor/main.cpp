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




int main() {
    long length = 0;
    unsigned char *data = Buffering("../workspace for processor/CODE.txt", &length);
    CheckFile(&data);

    Work(data, length);

    return 0;
}

void Work(unsigned char *data, long length) {
    Stack_t stack = {};
    StackInit(&stack);
    type_cpu registers[MAX_NUM_REGISTER];

    //printf("PI[1] %x %x %x\n,",IP[0], IP[1], 0xAA);
    CommandProcessing(stack, data, registers, length);
}

void CheckFile(unsigned char **buffer) {
    const unsigned char *data = *buffer;
    if (*(int*)data != 'aKiM'){
        printf("DATA%d %d %d %d", data[0], data[1], data[2], data[3]);
        printf("Incorrect format of file,\n please, repeat compilation!");
        abort();
    }
    if (data[4] != VERSION) {
        printf("Compiled file version does not match with version processor,\n please, update compiler and repeat compilation!");
        abort();
    }
    *buffer += 5;
}

long ItLength(FILE* file){
    assert(file != nullptr);

    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    fseek(file, 0, SEEK_SET);

    return result;
}

unsigned char* Buffering(const char name_file[], long* length){
    FILE* file = fopen("../workspace for processor/CODE.txt", "rb");
    if (file == nullptr) {
        printf("Can't find file!\ninterpret original file or сheck file name");
        assert(file != nullptr);
    }
    *length = ItLength(file);
    unsigned char* data = (unsigned char*) calloc(*length, sizeof(char));
    fread(data, sizeof(char), *length, file);
    fclose(file);
    return data;
}

void CommandProcessing(Stack_t stack, unsigned char* data, type_cpu* registers, long length) {
    unsigned char *IP = data;

    while ((IP - data + 5) <= length) {
        switch (IP[0]) {
#define DEF_CMD(name, num, code)\
            case cmd_##name: \
            code; \
            break;

#include "commands_cpu.h"

            default:
                printf("Unknown command!\n");
                abort();
                break;

#undef DEF_CMD
                /*case cmd_push:
                    if (IP[1] == 0xAA){
                        type_cpu temp_num = *(type_cpu*)(IP + 2);
                        StackPush(&stack, temp_num);
                    }
                    else if (IP[1] == 0xBB) {

                    } else {
                        printf("Error in argument of 'push'!\nPlease, write about this in call center!\n");
                        abort();
                    }
                    break;

                    //case cmd_pop:

        */
        }
        //StackDump(&stack, "Debug", __FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}
