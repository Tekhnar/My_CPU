//
// Created by texnar on 20/10/2019.
//

/*
#ifndef INTERPRETER_COMMANDS_H
#define INTERPRETER_COMMANDS_H

#endif //INTERPRETER_COMMANDS_H
*/

DEF_CMD(end, 0,{
    data[(*write_point)++] = cmd_end;
    },
    {
        //exit;
        return ;
})

DEF_CMD(push, 1,
    {
        data[(*write_point)++] = cmd_push;
        FunctionPUSH(&data, write_point, com,
            &pointer_read, first_symb, num_enter);
    },
    {
        FunctionPUSHCpu(stack, &IP, registers, ram);
})

DEF_CMD(pop, 2,
    {
        data[(*write_point)++] = cmd_pop;
        FunctionPOP(&data, write_point, com,
                     &pointer_read, first_symb, num_enter);
    },
    {
        FunctionPOPCpu(stack, &IP, &registers, ram);
})

DEF_CMD(add, 3,{
        data[(*write_point)++] = cmd_add;
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        StackPush(stack, tmp1 + tmp2);
        IP++;
})

DEF_CMD(sub, 4,{
        data[(*write_point)++] = cmd_sub;
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        StackPush(stack, tmp2 - tmp1);
        IP++;
})

DEF_CMD(div, 5,{
    data[(*write_point)++] = cmd_div;
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        StackPush(stack, tmp2 / tmp1);
        IP++;
})

DEF_CMD(mul, 6,{
        data[(*write_point)++] = cmd_mul;
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        StackPush(stack, tmp2 * tmp1);
        IP++;
})

DEF_CMD(sqrt, 7,{
        data[(*write_point)++] = cmd_sqrt;
    },
    {
        double tmp1 = 0;
        StackPop(stack, &tmp1);
        StackPush(stack, sqrt(tmp1));
        IP++;
})

DEF_CMD(sin, 8,{
        data[(*write_point)++] = cmd_sin;
    },
    {
        double tmp1 = 0;
        StackPop(stack, &tmp1);
        StackPush(stack, sin(tmp1));
        IP++;
})

DEF_CMD(cos, 9,{
        data[(*write_point)++] = cmd_cos;
    },
    {
        double tmp1 = 0;
        StackPop(stack, &tmp1);
        StackPush(stack, cos(tmp1));
        IP++;
})

DEF_CMD(pow, 10,{
        data[(*write_point)++] = cmd_pow;
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        StackPush(stack, pow(tmp2, tmp1));
        IP++;
})

DEF_CMD(jmp, 11, {
    data[(*write_point)++] = cmd_jmp;
    FunctionJMP(&data, write_point, array_jumps, com, &pointer_read, first_symb, num_enter);
    },
    {
        if (IP[1] == WRITE_REG){
            IP = data + (long)((registers[IP[2]])) - 5;
        }
        else if (IP[1] == WRITE_NUM) {
            IP = data + *(long*)(&IP[1]) - 5;
        } else {
            printf("Error in argument of 'jmp'!\n");
            abort();
        }
})

DEF_CMD(ja, 12,{
    data[(*write_point)++] = cmd_ja;
    FindLabelJMP(&data, write_point, array_jumps,
            &pointer_read, first_symb, num_enter);
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        if (tmp2 <= tmp1) IP = data + *(long*)(&IP[1]) - 5;
        else IP += sizeof(long) + 1; // should be do in other
})

DEF_CMD(jae, 13,{
    data[(*write_point)++] = cmd_jae;
    FindLabelJMP(&data, write_point, array_jumps,
            &pointer_read, first_symb, num_enter);
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        if (tmp2 < tmp1) IP = data + *(long*)(&IP[1]) - 5;
        else IP += sizeof(long) + 1;
})

DEF_CMD(jb, 14,{
    data[(*write_point)++] = cmd_jb;
    FindLabelJMP(&data, write_point, array_jumps,
            &pointer_read, first_symb, num_enter);
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        if (tmp2 >= tmp1) IP = data + *(long*)(&IP[1]) - 5;
        else IP += sizeof(long) + 1;
})

DEF_CMD(jbe, 15,{
    data[(*write_point)++] = cmd_jbe;
    FindLabelJMP(&data, write_point, array_jumps,
            &pointer_read, first_symb, num_enter);
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        if (tmp2 > tmp1) IP = data + *(long*)(&IP[1]) - 5;
        else IP += sizeof(long) + 1;
})

DEF_CMD(je, 16,{
    data[(*write_point)++] = cmd_je;
    FindLabelJMP(&data, write_point, array_jumps,
            &pointer_read, first_symb, num_enter);
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        if (tmp2 != tmp1) IP = data + *(long*)(&IP[1]) - 5;
        else IP += sizeof(long) + 1;
//    printf("IP%p\n", IP);
})

DEF_CMD(jne, 17,{
    data[(*write_point)++] = cmd_jne;
    FindLabelJMP(&data, write_point, array_jumps,
            &pointer_read, first_symb, num_enter);
    },
    {
        double tmp1 = 0;
        double tmp2 = 0;
        StackPop(stack, &tmp1);
        StackPop(stack, &tmp2);
        if (tmp2 == tmp1) IP = data + *(long*)(&IP[1]) - 5;
        else IP += sizeof(long) + 1;
})

DEF_CMD(call, 18, {
    data[(*write_point)++] = cmd_call;
    FunctionCALL(&data, write_point, array_jumps,
            &pointer_read, first_symb, num_enter);
    },
    {
        type_cpu temp_num = (type_cpu)(*(long*)(&IP[1 + sizeof(long)]));
        StackPush(stack, temp_num);
        IP = data + *(long*)(&IP[1]) - 5;
})

DEF_CMD(out, 19,{
    data[(*write_point)++] = cmd_out;
    },
    {
        double tmp = -1;
        StackPop(stack, &tmp);
        printf("out: %lg\n", tmp);
        IP++;
})

DEF_CMD(in, 20,{
    data[(*write_point)++] = cmd_in;
    },
    {
        double tmp = -1;
        scanf("%lg", &tmp);
        StackPush(stack, tmp);
        IP++;
})
DEF_CMD(ret, 21,{
    data[(*write_point)++] = cmd_ret;
    },
    {
        double tmp = -1;
        StackPop(stack, &tmp);
        IP = data + (long)(tmp) - 5;
})

DEF_CMD(ini, 22, {
    data[(*write_point)++] = cmd_ini;
    },
    {
        txCreateWindow(WINDOW_WIGTH, WINDOW_LENGTH);
        main_window = txVideoMemory();
        IP++;
})

DEF_CMD(upd, 23, {
    data[(*write_point)++] = cmd_upd;
},
    {
    FunctionUPDCpu(&IP, ram, &main_window);
    })

DEF_CMD(rou, 24, {
    data[(*write_point)++] = cmd_rou;
},
    {
        FunctionROUCpu(stack, &IP);
    })