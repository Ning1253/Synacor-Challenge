#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <conio.h>

#include "header.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    } 
    if (argc > 3) {
        printf("Too many arguments.\n");
        return 1;
    }
    
    FILE* fptr = fopen(argv[1], "rb");
    uint16_t* ram = calloc(32768, sizeof(uint16_t));
    uint16_t* reg = calloc(8, sizeof(uint16_t));
    layer* stack = NULL;

    int i = 0;
    while (!feof(fptr)) {
        uint8_t lo = fgetc(fptr);
        uint8_t hi = fgetc(fptr);
        ram[i++] = lo + (hi << 8);
    }

    ram[5485] = 6;
    ram[5489] = NOOP; // Ackermann? Naa...
    ram[5490] = NOOP;

    if (argc == 3) {
        FILE* inputptr = fopen(argv[2], "r");
        run(ram, reg, stack, inputptr);
    } else {
        run(ram, reg, stack, NULL);
    }
}

void run(uint16_t* ram, uint16_t * reg, layer* stack, FILE* inputfile) {
    bool flag = false;
    layer* l = NULL;
    char c;
    for (uint16_t pp = 0;; pp++) {
        if (flag) {
            printf("Instr: [%d] %d\n\n", pp, ram[pp]);
            printf("Reg: \n");
            for (int i = 0; i < 8; i++) {
                printf("[%d] | %d\n", i, reg[i]);
            }
            layer* ptr = stack;
            printf("Stack: ");
            while (ptr) {
                printf("%d > ", ptr->val);
                ptr = ptr->prev;
            }
            printf("\n\n");
        }

        switch (ram[pp]) {
            case HALT:
                return;
            case SET:
                reg[ram[pp + 1] % 32768] = get_val(2);
                pp += 2;
                break;
            case PUSH:
                l = malloc(sizeof(layer));
                *l = (layer){get_val(1), stack};
                stack = l;
                pp += 1;
                break;
            case POP:
                if (stack == NULL) {
                    error("Empty Stack. ", pp);
                }
                reg[ram[pp + 1] % 32768] = stack->val;
                stack = stack->prev;
                pp += 1;
                break;
            case EQ:
                reg[ram[pp + 1] % 32768] = (get_val(2) == get_val(3) ? 1 : 0);
                pp += 3;
                break;
            case GT:
                reg[ram[pp + 1] % 32768] = (get_val(2) > get_val(3) ? 1 : 0);
                pp += 3;
                break;
            case JMP:
                pp = get_val(1);
                pp -= 1;
                break;
            case JT:
                if (get_val(1) != 0) {
                    pp = get_val(2);
                    pp -= 1;
                } else {
                    pp += 2;
                }
                break;
            case JF:
                if (get_val(1) == 0) {
                    pp = get_val(2);
                    pp -= 1;
                } else {
                    pp += 2;
                }
                break;
            case ADD:
                reg[ram[pp + 1] % 32768] = (get_val(2) + get_val(3)) % 32768;
                pp += 3;
                break;
            case MULT:
                reg[ram[pp + 1] % 32768] = (get_val(2) * get_val(3)) % 32768;
                pp += 3;
                break;
            case MOD:
                reg[ram[pp + 1] % 32768] = (get_val(2) % get_val(3)) % 32768;
                pp += 3;
                break;
            case AND:
                reg[ram[pp + 1] % 32768] = (get_val(2) & get_val(3));
                pp += 3;
                break;
            case OR:
                reg[ram[pp + 1] % 32768] = (get_val(2) | get_val(3));
                pp += 3;
                break;
            case NOT:
                reg[ram[pp + 1] % 32768] = ~get_val(2) & ~(1 << 15); 
                pp += 2;
                break;
            case RMEM:
                reg[ram[pp + 1] % 32768] = ram[get_val(2)];
                pp += 2;
                break;
            case WMEM:
                ram[get_val(1)] = get_val(2);
                pp += 2;
                break;
            case CALL:
                l = malloc(sizeof(layer)); 
                *l = (layer){pp + 2, stack};
                stack = l;
                pp = get_val(1);
                pp -= 1;
                break;
            case RET:
                if (stack == NULL) {
                    return;
                }
                pp = stack->val;
                stack = stack->prev;
                pp -= 1;
                break;
            case OUT:
                printf("%c", get_val(1));
                pp += 1;
                break;
            case IN:
                if (inputfile != NULL && (c = fgetc(inputfile)) != EOF) {
                    reg[ram[pp + 1] % 32768] = c;
                } else {
                    c = getchar();
                    if (c != '/') {
                        reg[ram[pp + 1] % 32768] = c;
                    } else {
                        debug(ram, reg, &flag);
                        pp -= 2;
                    }
                }

                pp += 1;
                break;
            case NOOP:
                break;
            default:
                error("Unexpected Token. ", pp);
        }
    }
}

void error(char* msg, uint16_t ptr) {
    printf("[loc %d] %s\n", ptr, msg);
    exit(1);
}

void debug(uint16_t* ram, uint16_t* reg, bool* flag) {
    char* cmd = calloc(256, sizeof(char));
    unsigned char c = 0, i = 0;
    while ((c = getchar()) != '\n') {
        cmd[i++] = c;
    }
    switch (cmd[0]) {
        case 0:
            for (int i = 0; i < 8; i++) {
                printf("%d | %d\n", i, reg[i]);
            }
            printf("\n");
            break;
        case 's':
            int r = cmd[2] - 48;
            int val = atoi(cmd + 4);
            printf("Changed reg[%d] to %d. \n\n", r, val);
            reg[r] = val;
            break;
        case 'd':
            *flag = true;
            break;

    }
}

char* convert(uint16_t val) {
    char* string = calloc(8, sizeof(char));
    if (val > 32767) {
        sprintf(string, "reg[%d]", val % 32768);
    } else {
        sprintf(string, "%d", val);
    }
    return string;
}