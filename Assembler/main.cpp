#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include "general_data.h"


long ItLength(FILE* file);
void CountConstHash(commands* consthash);
void CommandProcessing (char* buffer, char* data, long length, commands* com, long* write_point);
unsigned int MurmurHash(const char text[]);
void FindRegister(commands* com, char str_reg[], unsigned int hash_read_reg, char* num_reg, int num_enter);

FILE* ConvertFile(FILE* file, commands* com, const char name_file[] = "CODE.txt");


int main() {
    commands com = {};
    CountConstHash(&com);

    FILE* file = fopen("text.txt", "rb");

    ConvertFile(file, &com, "CODE.txt");
//    FILE* newfile = fopen("CODE.txt", "w+");
//    printf("string %p\n",file);
    fclose(file);
    return 0;
}

void CountConstHash(commands* com) {

#define DEF_CMD(name, str, num, code) \
    com->hash_##name = MurmurHash(str);

#include "commands.h"

#undef DEF_CMD

#define REGISTER(name, str, num)\
    com->hash_reg_##name = MurmurHash(str);

    #include "register.h"

#undef REGISTER
}


unsigned int MurmurHash(const char text[])
{
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int len = strlen(text);

    const unsigned char * data = (const unsigned char *) text;
    unsigned int h = seed ^ len;

    unsigned int k = 0;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

long ItLength(FILE* file){
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    fseek(file, 0, SEEK_SET);

    return result;
}

FILE* ConvertFile(FILE* file, commands* com, const char name_file[]){
    assert(file != nullptr);

    long length = ItLength(file);

    char* buffer = (char *)calloc(length, sizeof(char));
    char* data = (char *)calloc(length * 3, sizeof(char)); // should be rewrite!
    int num_re = fread(buffer, sizeof(char), length, file);
    printf("%s\n", buffer);

//    int num_enter = 0;
    long write_point = 0;
//    char* last_symb = buffer;

    *(int *)data = 'aKiM';
    data[4] = VERSION;
    write_point += 5;

    CommandProcessing (buffer, data, length, com, &write_point);

//    printf("Hash_push %u\n", com->hash_push);
//    printf("Hash_pop %u\n", com->hash_pop);
    FILE* newfile = fopen(name_file, "w+");

    fwrite(data, sizeof(char), write_point, newfile);
    free(buffer);
    free(data);
    fclose(newfile);
}

void CommandProcessing (char* buffer, char* data, long length, commands* com, long* write_point){
    assert(buffer != 0);
    assert(data != 0);
    assert(com != 0);
    assert(write_point != 0);

    int num_enter = 1;
    char* last_symb = buffer;

    while ((last_symb - buffer) < length){
        char* first_symb = last_symb;
        last_symb = strchr(first_symb, '\n');
        if (last_symb == nullptr)
            last_symb = buffer + (length - 1);

        *last_symb = '\0';
        if (*(last_symb - 1) == '\r') *(last_symb - 1) = '\0';
        char command[10] = {};
        int pointer_read = 0;

        char *comment = strchr(first_symb, ';');
        if (comment != nullptr){
            *comment = '\0';
        }

        int num_read = sscanf(first_symb, "%s%n", command, &pointer_read);
//        if (num_read == 0) {
//        }
        unsigned int hash_read_com = MurmurHash(command);
        /*switch (MurmurHash(command)) {
            case com.hash_push:

            break;
        }*/
        printf("%s\n", command);
        printf("%u\n", hash_read_com);
        printf("Poiter_read %u\n", pointer_read);
        //printf("Hash_push %u\n", com->hash_push);


        /*if (hash_read_com == com->hash_push){
            double num = 0;
            if (0 == sscanf((first_symb + pointer_read), "%lg%n", &num, &pointer_read)) {
                printf("Don't find number of command in line <%d>\n", num_enter);
                abort();
            }
            printf("Number %lg\n", num);
            data[(*write_point)++] = PUSH;
            data[(*write_point)++] = 0xAA; //send number or registr
            *//*if number 0xAA if registr 0xBB*//*
//            data[(*write_point)] = 0x77; // this is wall

            *((double *)(data + *write_point)) = num;
            printf("Num FROM DATA %lg\n", *((double *)(data + *write_point)));
            *write_point += sizeof(double);

//            data[(*write_point)] = 0x77; // this is wall
        }*/

        /*if (hash_read_com == com->hash_pop){
            char str[10] ={};
            data[(*write_point)++] = POP;
            if (sscanf((first_symb + pointer_read), "%s%n", str, &pointer_read) == 0) {
                printf("Don't find number of command in line <%d>\n", num_enter);
                abort();
            }
        }*/

        bool known_command = false;

        #define DEF_CMD(name, str, num, code)\
            if (hash_read_com == com->hash_##name){ code; known_command = true;}
        #include "commands.h"


        if (!known_command) {
            printf("Don't find command \"%s\" in line (%d) \n", command, num_enter);
            abort();
        }
        #undef DEF_CMD

        num_enter++;
        last_symb++;
        printf("\n");

    }
}

void FindRegister(commands* com, char str_reg[], unsigned int hash_read_reg, char* num_reg, int num_enter){
    bool known_register = false;

    #define REGISTER(name, str, num)\
    if (com->hash_reg_##name == hash_read_reg && str[0] == str_reg[0]){\
        *num_reg = 1;\
        known_register = true;\
    }
    #include "register.h"

    if (!known_register){
        printf("Unknown register in command push '%s'<%d>\n", str_reg, num_enter);
        abort();
    }

    #undef REGISTER
}