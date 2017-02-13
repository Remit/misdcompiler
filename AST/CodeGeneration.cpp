#ifndef CODEGENERATION_H_
#include "../include/CodeGeneration.h"
#endif

spu_cmd SP_IR[MEM_LENGTH];
int mem_point = 0;

std::string print_bin(int num, int l) {
	std::string ret;
	int j,k;
    int c[32];
	
    for (j=l-1; j>=0; j--) {
        c[j] = num % 2;
        num /= 2;
    }
	
    for (j=0; j<l; j++) {
		ret += c[j];
    }
	
	return ret;
}