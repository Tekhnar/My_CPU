//#pragma  GCC diagnostic ignored "-Wmultichar"
#pragma warn -Wmultichar
#include "functions.h"
//#include "TXLin.h"


int main(int num_arg, char *poin_arg[]) {
    long length = 0;

    unsigned char *data = Buffering (num_arg, poin_arg,  &length);
    unsigned char* clear_data = data;
    CheckFile (&data);

    Work (data, length);
    free (clear_data);
    return 0;
}
