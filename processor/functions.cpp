//
// Created by texnar on 23/10/2019.
//


void Work(unsigned char *data, long length) {
    Stack_t stack = {};
    StackInit (&stack);
    unsigned char *ram = ConstructRAM();
    //*(type_cpu *)&ram[1] = 66;
    type_cpu registers[MAX_NUM_REGISTER] = {};

//    printf("PI[1] %x %x %x\n,",IP[0], IP[1], 0xAA);
    CommandProcessing(&stack, data, registers, length, ram);
    //printf("RAMM %lg", *(type_cpu *)&ram[1]);
    DestructRAM (ram);
    StackClose (&stack);
//    printf ("222");
}

void CheckFile(unsigned char **buffer) {
    const unsigned char *data = *buffer;
    if (*(int*)data != 'aKiM'){
        printf("DATA%d %d %d %d", data[0], data[1], data[2], data[3]);
//        printf("Incorrect format of file,\n please, repeat compilation!");
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

unsigned char* Buffering(int num_arg, char *poin_arg[], long* length){
    FILE* file = OpenFile(num_arg, poin_arg);
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

void CommandProcessing(Stack_t* stack, unsigned char* data,
        type_cpu* registers, long length, unsigned char* ram) {
    unsigned char *IP = data;
    RGBQUAD* main_window = nullptr;
    while ((IP - data) <= length - 5) {
        switch (IP[0]) {
#define DEF_CMD(name, num, code, code_cpu)\
            case cmd_##name: {\
            code_cpu; \
            break;}

#include "../Assembler/commands.h"

            default:
                printf("Unknown command!\n");
                abort();
                break;

#undef DEF_CMD

        }
        //StackDump(&stack, "Debug", __FILE__, __LINE__, __PRETTY_FUNCTION__);
    }
}

unsigned char* ConstructRAM(){
    unsigned char* ram = (unsigned char*) malloc(SIZE_RAM);
    if (ram == nullptr){
        printf("Error in malloc\n");
        abort();
    }
    return ram;
}

void DestructRAM(unsigned char* ram){
    free(ram);
}

FILE* OpenFile(int num_arg, char *poin_arg[]){
    if (num_arg > 1){
        return fopen(poin_arg[1], "rb");
    } else
        return fopen("../workspace_for_processor/CODE.nasm", "rb");
}

void FunctionPUSHCpu(Stack_t* stack, unsigned char** IP,
        type_cpu* registers, unsigned char* ram){
    switch ((*IP)[1]){
        case WRITE_NUM:{
            type_cpu temp_num = *(type_cpu*)(&((*IP)[2]));
            StackPush(stack, temp_num);
            (*IP) += sizeof(type_cpu) + 2 * sizeof(char);
            break;
        }
        case WRITE_REG: {
            StackPush(stack, registers[(*IP)[2]]);
            (*IP) += 3 * sizeof(char);
            break;
        }
        case RAM_NUM: {
            StackPush(stack, *(type_cpu *)(&ram[sizeof (double) * *(long *) (&(*IP)[2]) ]));
            (*IP) += sizeof(long) + 2 * sizeof(char);
            break;
        }
        case RAM_REG: {
//                printf("regisss %d\n", (long)(registers[IP[2]]  - 1e-12));
            long temp_num = sizeof(double) * (long)(registers[(*IP)[2]] + 1e-12);
            StackPush(stack, *(type_cpu *)&ram[temp_num]);
            (*IP) += 3 * sizeof(char);
            break;
        }
        case RAM_REG_CHAR: {
//            printf("Reg %d\n", (*IP)[2]);
//            printf("Reg1 %lg\n", registers[(*IP)[2]]);
//            printf("regisss + %ld\n", (long)(registers[(*IP)[2]]  + 1e-12));
//            printf("regisss - %ld\n", (long)(registers[(*IP)[2]]  - 1e-12));
//            printf("regisss %lg\n", registers[(*IP)[2]]);
            long temp_num = (long)(registers[(*IP)[2]] + 1e-12);
            double tmp = (double)ram[temp_num];
            StackPush(stack, tmp);
            (*IP) += 3 * sizeof(char);
            break;
        }
        case RAM_NUM_CHAR: {
            long temp_num = *(long*)&(*IP)[2];
            StackPush(stack, ram[temp_num]);

            (*IP) += 2 * sizeof(char) + sizeof(long);
            break;
        }
        default:
            printf("Error in argument of 'push'!\n");
            abort();
            break;
    }
}

void FunctionPOPCpu(Stack_t* stack, unsigned char** IP,
        type_cpu** registers, unsigned char* ram){
    switch ((*IP)[1]){
        case WRITE_REG: {
//            printf("Reg_num %d\n", (*IP)[2]);
            StackPop(stack, &(*registers)[(*IP)[2]]);


//            printf("Reg_pop %lg\n", (*registers)[(*IP)[2]]);
            (*IP) += 3 * sizeof(char);
            break;
        }
        case WRITE_NOTHING: {
            double tmp = -1;
            StackPop(stack, &tmp);
            (*IP) += 2 * sizeof(char);
            break;
        }
        case RAM_NUM: {
            type_cpu tmp = -1;
            StackPop(stack, &tmp);
//                printf("gfgfg %lg\n", tmp);
//                printf("num ram %ld\n", *(long *)&(*IP)[2]);
            *(type_cpu *)(&ram[sizeof (type_cpu)* *(long *) (&(*IP)[2])]) = tmp;
//                printf("num test %lg\n", *(type_cpu *)(&ram[*(long *) (&(*IP)[2])]));
            (*IP) += sizeof(long) + 2 * sizeof(char);
            break;
        }
        case RAM_REG: {
            type_cpu temp_num = -1;
            StackPop(stack, &temp_num);
            *(type_cpu *)&ram[sizeof (double) * (long)((*registers)[(*IP)[2]])] = temp_num;

            (*IP) += 3 * sizeof(char);
            break;
        }
        case RAM_REG_CHAR: {
            long temp_num = (long)((*registers)[(*IP)[2]]);
            double tmp = -1;
            StackPop(stack, &tmp);
            ram[temp_num] = (unsigned char)tmp;
            (*IP) += 3 * sizeof(char);
            break;
        }
        case RAM_NUM_CHAR: {
            long temp_num = *(long*)&(*IP)[2];
            double tmp = -1;
            StackPop(stack, &tmp);
            ram[temp_num] = (unsigned char)tmp;
            (*IP) += 2 * sizeof(char) + sizeof(long);
            break;
        }
        default:
            printf("Error in argument of 'pop'!\n");
            abort();
            break;
    }
}
void FunctionUPDCpu(unsigned char** IP, unsigned char* ram, RGBQUAD** main_window){
//    txLock();
    for(int i = 0; i < WINDOW_LENGTH; i++){
        for(int j = 0; j < WINDOW_WIGTH * 3; j+=1){
            //long tmp = j + (-i + WINDOW_LENGTH) * WINDOW_WIGTH;

            txSetPixel	(j, i, RGB ((unsigned int)ram[i * WINDOW_WIGTH * 3 + j * 3],
                                           (unsigned int)ram[i * WINDOW_WIGTH * 3 + j * 3 + 1],
                                           (unsigned int)ram[i * WINDOW_WIGTH * 3 + j * 3 + 2]));

//            main_window[j + (-i + WINDOW_LENGTH) * WINDOW_WIGTH] = RGB ((unsigned int)ram[i * WINDOW_WIGTH * 3 + j * 3],
//                                                                        (unsigned int)ram[i * WINDOW_WIGTH * 3 + j * 3 + 1],
//                                                                        (unsigned int)ram[i * WINDOW_WIGTH * 3 + j * 3 + 2]);
//            RGBQUAD* c = main_window;
//            c->rgbRed      = (unsigned char) (255 - c->rgbRed);    // Negative colors
//            c->rgbGreen    = (unsigned char) (255 - c->rgbGreen);
//            c->rgbBlue     = (unsigned char) (255 - c->rgbBlue);
        }
        //printf("Line %d\n", i);
        txRedrawWindow();
    }
//    txUnlock();
//    txRedrawWindow();
    (*IP)++;
}

void FunctionROUCpu(Stack_t* stack, unsigned char** IP){
    double tmp = -1;
    StackPop(stack, &tmp);
    tmp = floor(tmp);
    StackPush(stack, tmp);
    (*IP)++;
}