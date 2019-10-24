//
// Created by texnar on 23/10/2019.
//

void CountConstHash(commands* com) {

#define DEF_CMD(name, num, code) \
    com->hash_##name = MurmurHash(#name);

#include "commands.h"

#undef DEF_CMD

#define REGISTER(name, num)\
    com->hash_reg_##name = MurmurHash(#name);

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

FILE* ConvertFile(FILE* file, commands* com, int num_arg, char *poin_arg[], const char name_file[]){
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
    FILE* newfile = 0;
    if (num_arg > 2){
        strcat(poin_arg[2],".nasm");
        newfile = fopen(poin_arg[2], "w");
    } else newfile = fopen(name_file, "w");


    fwrite(data, sizeof(char), write_point, newfile);
    free(buffer);
    free(data);
    fclose(newfile);
}

void CommandProcessing (char* buffer, char* data, long length, commands* com, long* write_point) {
    assert(buffer != 0);
    assert(data != 0);
    assert(com != 0);
    assert(write_point != 0);

    jumps array_jumps[MAX_NUM_JMP] = {};
//    long jumps[MAX_NUM_JMP] = {};

    long copy_write_point = *write_point;
    for(int j = 0; j < 2; j++){

        *write_point = copy_write_point;
        int num_enter = 1;
        char *last_symb = buffer;

        while ((last_symb - buffer) < length) {
            char *first_symb = last_symb;
            last_symb = strchr(first_symb, '\n');
            if (last_symb == nullptr)
                last_symb = buffer + (length - 1);

            *last_symb = '\0';
            if (*(last_symb - 1) == '\r') *(last_symb - 1) = '\0';
            char command[10] = {};
            int pointer_read = 0;

            char *comment = strchr(first_symb, ';');
            if (comment != nullptr) {
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



            bool known_command = false;

#define DEF_CMD(name, num, code)\
                if (hash_read_com == com->hash_##name){ code; known_command = true;}

#include "commands.h"

            if (!known_command) {
                if (command[0] == ':') {
                    long num_jmp = 0;
                    if (sscanf(&(command[1]), "%ld%n", &num_jmp, &pointer_read)) {
                        array_jumps[num_jmp].address_jump_to = *write_point;
                        array_jumps[num_jmp].used_jump = true;
                        known_command = true;
                    }
                }
            }

            if (!known_command) {
                printf("Don't find command \"%s\" in line (%d) \n", command, num_enter);
                abort();
            }
#undef DEF_CMD


            num_enter++;
            // it is return text (\n)
            *last_symb = '\n';
            if (comment != nullptr) {
                *comment = ';';
            }
            last_symb++;
            printf("\n");

        }
    }
}

void FindRegister(commands* com, char str_reg[], unsigned int hash_read_reg, char* num_reg, int num_enter){
    bool known_register = false;

#define REGISTER(name, num)\
    if (com->hash_reg_##name == hash_read_reg && #name[0] == str_reg[0]){\
        *num_reg = num;\
        known_register = true;\
    }
#include "register.h"

    if (!known_register){
        printf("Unknown register in command push '%s'<%d>\n", str_reg, num_enter);
        abort();
    }

#undef REGISTER
}

FILE* OpenFile(int num_arg, char *poin_arg[]){
    if (num_arg > 1){
        return fopen(poin_arg[1], "rb");
    } else
        return fopen("../workspace_for_processor/text.txt", "rb");
}