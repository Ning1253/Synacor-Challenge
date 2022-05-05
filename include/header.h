#ifndef c_header_h
#define c_header_h

#include <stdint.h>

typedef struct layer {
    uint16_t val;
    struct layer* prev;
} layer;

enum instr{
    HALT,
    SET,
    PUSH,
    POP,
    EQ,
    GT,
    JMP,
    JT,
    JF,
    ADD,
    MULT,
    MOD,
    AND,
    OR,
    NOT,
    RMEM,
    WMEM,
    CALL,
    RET,
    OUT,
    IN,
    NOOP
};

void run(uint16_t* ram, uint16_t * reg, layer* stack, FILE* inputfile);
void error(char* msg, uint16_t ptr);
void debug(uint16_t* ram, uint16_t* reg, bool* flag);
char* get_instr(uint16_t val);
char* convert(uint16_t val);

#define get_val(num) (ram[pp + num] < 32768 ? ram[pp + num] : reg[ram[pp + num] % 32768])
// get_val(n) means get the value of the n th argument, either as a literal or a registered value. 

#endif