#ifndef CODEGENERATION_H_
#define CODEGENERATION_H_

#include "/usr/include/llvm/IR/DerivedTypes.h"
#include "/usr/include/llvm/IR/LLVMContext.h"
#include "/usr/include/llvm/IR/Module.h"
#include "/usr/include/llvm/IR/Verifier.h"
#include "/usr/include/llvm/IR/IRBuilder.h"
#include <fstream>
#include <iostream>

using namespace llvm;
extern LLVMContext GlobalContext;
extern IRBuilder<> Builder;
extern Module * GlobalModule;
extern std::map<std::string, AllocaInst *> NamedValues;

/////////////////////////////////////////
//           Define constatnts
/////////////////////////////////////////

#define WORD_LENGTH  80
#define MEM_LENGTH  256
#define LINE_SIZE 1024

/////////////////////////////////////////
//           Define opcodes
/////////////////////////////////////////

#define NOOP 99
#define DEL 1
#define ADD 2
#define MIN 3
#define MAX 4
#define SEARCH 5
#define SQUIZ 6
#define POWER 7
#define OR 8
#define AND 9
#define NOT 10
#define LSEQ 11
#define LS 12
#define GREQ 13
#define GR 14
#define DELS 15
#define JT 0
//#define JWT 98
//#define JNW 99
#define NEXT 16

/////////////////////////////////////////
//           Define op counts
/////////////////////////////////////////

#define NOOP_C 0
#define DEL_C 2
#define ADD_C 3
#define MIN_C 1
#define MAX_C 1
#define SEARCH_C 2
#define SQUIZ_C 1
#define OR_C 3
#define AND_C 3
#define NOT_C 3
#define LSEQ_C 3
#define LS_C 3
#define GREQ_C 3
#define GR_C 3
#define DELS_C 1
#define POWER_C 1
#define JT_C 1
//#define JWT_C 1
//#define JNW_C 0
#define NEXT_C 2

typedef struct { 		//Structure type for inner command representation, a structure corresponds to a command of SPU
    char label[80];     //Label of the operator
    int opcode;         //Inner code of operation
    long op[3];         //Operands (numbers are for structures, the simple data is unnumbered)
    bool tag[3];        //Tags
    char jmp_label[80]; //Symbolic jump label (see above) for jwt and jnw
    int jmp_adr;        //Jump address
    bool q;             //Output queue using flag
} spu_cmd;

extern spu_cmd SP_IR[MEM_LENGTH];
extern unsigned int SP_BIN[MEM_LENGTH][5];
extern int mem_point;
extern int label_i;
extern void SPU_IR2BIN(); //Function to convert the IR of SPU command to its binary representation
extern void print_SPU_asm_IR(std::ostream * print_stream);

#endif