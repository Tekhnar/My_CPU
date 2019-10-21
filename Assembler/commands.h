//
// Created by texnar on 20/10/2019.
//

/*
#ifndef INTERPRETER_COMMANDS_H
#define INTERPRETER_COMMANDS_H

#endif //INTERPRETER_COMMANDS_H
*/

DEF_CMD(push, "push", 1,
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

DEF_CMD(pop, "pop", 2,
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

DEF_CMD(add, "add", 3,{
        data[(*write_point)++] = cmd_add;
    })

DEF_CMD(sub, "sub", 4,{
        data[(*write_point)++] = cmd_sub;
    })

DEF_CMD(div, "div", 5,{
    data[(*write_point)++] = cmd_div;
    })

DEF_CMD(mul, "mul", 6,{
        data[(*write_point)++] = cmd_mul;
    })

DEF_CMD(sqrt, "sqrt", 7,{
        data[(*write_point)++] = cmd_sqrt;
    })

DEF_CMD(sin, "sin", 8,{
        data[(*write_point)++] = cmd_sin;
    })

DEF_CMD(cos, "cos", 9,{
        data[(*write_point)++] = cmd_cos;
    })

DEF_CMD(pow, "pow", 10,{
        data[(*write_point)++] = cmd_pow;
    })
