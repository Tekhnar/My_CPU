//#define DEBUG
//#pragma warn -Wmultichar
#include "functions_asm.h"

int main(int num_arg, char *poin_arg[]) {
    commands com = {};
    CountConstHash(&com);
    FILE* file = OpenFile(num_arg, poin_arg);

    ConvertFile(file, &com, num_arg, poin_arg, "../workspace_for_processor/CODE.nasm");

    CloseFile(file);
    return 0;
}
