#include "functions_asm.h"

int main(int num_arg, char *poin_arg[]) {
    commands com = {};
    CountConstHash(&com);
//    printf("num arg%d\n", num_arg);
//    printf("name %s\n", poin_arg[1]);
    FILE* file = OpenFile(num_arg, poin_arg);
    //FILE* file = fopen(poin_arg[1], "rb");

    ConvertFile(file, &com, num_arg, poin_arg, "../workspace_for_processor/CODE.nasm");
//    FILE* newfile = fopen("CODE.txt", "w+");
//    printf("string %p\n",file);
    fclose(file);
    return 0;
}
