#include "functions.h"

int main() {
    long length = 0;
    unsigned char *data = Buffering("../workspace_for_processor/CODE.nasm",  &length);
    CheckFile(&data);

    Work(data, length);

    return 0;
}
