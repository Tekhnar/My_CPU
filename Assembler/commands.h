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
})

DEF_CMD(push, 1,
    {
        data[(*write_point)++] = cmd_push;

        double num = 0;
        if (sscanf((first_symb + pointer_read), "%lg%n", &num, &pointer_read) == 0) {

            char str_reg[10] ={};
            char num_reg = 0;
            if (sscanf((first_symb + pointer_read), "%s%n", str_reg, &pointer_read) >= 1) {
//                printf("%s\n", str_reg);
//                printf("Hash reg %d\n", com->hash_reg_ax);

                unsigned int hash_read_reg = MurmurHash(str_reg);
//                printf("Hash read %d", hash_read_reg);
                FindRegister(com, str_reg, hash_read_reg, &num_reg, num_enter);
                /*if (com->hash_reg_ax == hash_read_reg && "ax"[0] == str_reg[0]){
                    num_reg = 1;
                }

                else if (com->hash_reg_bx == hash_read_reg && "bx"[0] == str_reg[0]){
                    num_reg = 2;
                }

                else if (com->hash_reg_cx == hash_read_reg && "cx"[0] == str_reg[0]){
                    num_reg = 3;
                }

                else if (com->hash_reg_dx == hash_read_reg && "dx"[0] == str_reg[0]){
                    num_reg = 4;
                } else */
                /*if (!known_register){
                    printf("Unknown register in command push '%s'<%d>\n", str_reg, num_enter);
                    abort();
                }*/

                data[(*write_point)++] = 0xBB;

                *((unsigned char *) (data + *write_point)) = num_reg;
                *write_point += sizeof(char);

//                printf("Don't find number of command in line <%d>\n", num_enter);
//                abort();
            } else {
                printf("Don't find number or register of command push <%d>\n", num_enter);
                abort();
            }
        } else {
            printf("Number %lg\n", num);
            data[(*write_point)++] = 0xAA; //send number or registr
            /*if number 0xAA if registr 0xBB*/
            //            data[(*write_point)] = 0x77; // this is wall

            *((double *) (data + *write_point)) = num;
            printf("Num FROM DATA %lg\n", *((double *) (data + *write_point)));
            *write_point += sizeof(double);
        }

        //            data[(*write_point)] = 0x77; // this is wall
    })

DEF_CMD(pop, 2,
    {
        data[(*write_point)++] = cmd_pop;
        char str_reg[10] ={};
        char num_reg = 0;
        if (sscanf((first_symb + pointer_read), "%s%n", str_reg, &pointer_read) >= 1) {
//                printf("%s\n", str_reg);
//                printf("Hash reg %d\n", com->hash_reg_ax);

            unsigned int hash_read_reg = MurmurHash(str_reg);
//                printf("Hash read %d", hash_read_reg);
            FindRegister(com, str_reg, hash_read_reg, &num_reg, num_enter);
            /*if (com->hash_reg_ax == hash_read_reg && "ax"[0] == str_reg[0]){
                num_reg = 1;
            }

            else if (com->hash_reg_bx == hash_read_reg && "bx"[0] == str_reg[0]){
                num_reg = 2;
            }

            else if (com->hash_reg_cx == hash_read_reg && "cx"[0] == str_reg[0]){
                num_reg = 3;
            }

            else if (com->hash_reg_dx == hash_read_reg && "dx"[0] == str_reg[0]){
                num_reg = 4;
            } else {
                printf("Unknown register in command pop '%s'<%d>\n", str_reg, num_enter);
                abort();
            }
*/

            data[(*write_point)++] = 0xBB; // pop upload number in register

            *((unsigned char *) (data + *write_point)) = num_reg;
            *write_point += sizeof(char);

//                printf("Don't find number of command in line <%d>\n", num_enter);
//                abort();
        } else {

//            printf("Don't find number or register of command push <%d>\n", num_enter);
//            abort();
            data[(*write_point)++] = 0xCC; // pop not upload number. lost the number

        }


//            printf("Don't find number of command in line <%d>\n", num_enter);
//            printf("STR: '%d'\n", str[0]);
//            abort();
    })

DEF_CMD(add, 3,{
        data[(*write_point)++] = cmd_add;
    })

DEF_CMD(sub, 4,{
        data[(*write_point)++] = cmd_sub;
    })

DEF_CMD(div, 5,{
    data[(*write_point)++] = cmd_div;
    })

DEF_CMD(mul, 6,{
        data[(*write_point)++] = cmd_mul;
    })

DEF_CMD(sqrt, 7,{
        data[(*write_point)++] = cmd_sqrt;
    })

DEF_CMD(sin, 8,{
        data[(*write_point)++] = cmd_sin;
    })

DEF_CMD(cos, 9,{
        data[(*write_point)++] = cmd_cos;
    })

DEF_CMD(pow, 10,{
        data[(*write_point)++] = cmd_pow;
    })

DEF_CMD(jmp, 11, {
        long num_jmp = 0;
        data[(*write_point)++] = cmd_jmp;
//    printf("poi before %d\n", pointer_read);
        if (sscanf((first_symb + pointer_read), "%ld%n", &num_jmp, &pointer_read)){
            printf("num %ld\n", num_jmp);
            data[(*write_point)++] = 0xAA;
            *(long*)(&data[(*write_point)]) = num_jmp;
            *(write_point) += sizeof(long);
        }
//        printf("pi after %d\n", pointer_read);
//        char s[10] = {};
//        sscanf((first_symb + pointer_read), "%s%n", s, &pointer_read);
//    printf("s[%s\n", s);
        if (char* jmp_symbol = strchr(first_symb + pointer_read, ':')){
            pointer_read = jmp_symbol + 1 - first_symb;
            sscanf((first_symb + pointer_read), "%ld%n", &num_jmp, &pointer_read);
            printf("jmp %ld\n", num_jmp);

            if (num_jmp < 0 || num_jmp >= MAX_NUM_JMP) {
                printf("Invalid jmp number<%d>\n", num_enter);
                abort();
            }

            data[(*write_point)++] = 0xBB;
            data[(*write_point)++] = array_jumps[num_jmp].address_jump_to;
            array_jumps[num_jmp].used_jump = true;
        }
        //*((char*) (&data[*write_point])) = num;
})


