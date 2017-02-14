#ifndef CODEGENERATION_H_
#include "../include/CodeGeneration.h"
#endif

spu_cmd SP_IR[MEM_LENGTH];
int mem_point = 0;
int label_i = 0;

// This procedure prints the asm representation
// of SPU program either to file or to the
// standard output.
void print_SPU_asm_IR(std::string * filename) {
	std::streambuf * buf;
	std::ofstream of;

	if(filename->compare("") == 0) {
		buf = std::cout.rdbuf();
	} else {
		of.open(filename->c_str());
		buf = of.rdbuf();
	}

	std::ostream out_SPU_asm_IR(buf);
	
	for(int i = 0; i < mem_point; i++) { // End is where we stopped writing the instructions
		std::string out_str;
		
		// Printing address
		out_str += std::to_string(i);
		int left_syms_a = 8 - std::to_string(i).length() - 1;
		while(left_syms_a > 0) {
			out_str += " ";
			left_syms_a--;
		}
		out_str += "| ";
			
		// Printing label or indentation
		std::string lbl(SP_IR[i].label);
		if(lbl.compare("") == 0)
			out_str += "        ";
		else {
			out_str += lbl + ":";
			int left_syms = 8 - lbl.length() - 1;
			while(left_syms > 0) {
				out_str += " ";
				left_syms--;
			}
		}
		
		// Printing the operation
		std::string operation;
		int opcode = SP_IR[i].opcode;
		int cnt_of_ops;
		
		bool is_jmp_op = false;
		switch(opcode) {
			case NOOP:
				operation = "NOP";
				cnt_of_ops = NOOP_C;
				break;
			case DEL:
				operation = "DEL";
				cnt_of_ops = DEL_C;
				break;
			case ADD:
				operation = "INSERT";
				cnt_of_ops = ADD_C;
				break;
			case MIN:
				operation = "MIN";
				cnt_of_ops = MIN_C;
				break;
			case MAX:
				operation = "MAX";
				cnt_of_ops = MAX_C;
				break;
			case SEARCH:
				operation = "SEARCH";
				cnt_of_ops = SEARCH_C;
				break;
			case SQUIZ:
				operation = "COMPRESS";
				cnt_of_ops = SQUIZ_C;
				break;
			case POWER:
				operation = "POWER";
				cnt_of_ops = POWER_C;
				break;
			case OR:
				operation = "UNION";
				cnt_of_ops = OR_C;
				break;
			case AND:
				operation = "INTERSECT";
				cnt_of_ops = AND_C;
				break;
			case NOT:
				operation = "DIFFERENCE";
				cnt_of_ops = NOT_C;
				break;
			case LSEQ:
				operation = "LTE";
				cnt_of_ops = LSEQ_C;
				break;
			case LS:
				operation = "LT";
				cnt_of_ops = LS_C;
				break;
			case GREQ:
				operation = "GTE";
				cnt_of_ops = GREQ_C;
				break;
			case GR:
				operation = "GT";
				cnt_of_ops = GR_C;
				break;
			case DELS:
				operation = "DELS";
				cnt_of_ops = DELS_C;
				break;
			case JWT:
				operation = "JWT";
				cnt_of_ops = JWT_C;
				is_jmp_op = true;
				break;
			case JNW:
				operation = "JNW";
				cnt_of_ops = JNW_C;
				is_jmp_op = true;
				break;
			case NEXT:
				operation = "NEXT";
				cnt_of_ops = NEXT_C;
				break;
		}
		
		// Printing queue quantifier if necessary
		if(SP_IR[i].q)
			operation += "q";

		out_str += " ";

		// Printing operands if any
		if(cnt_of_ops > 0) { // First operand
			if(!SP_IR[i].tag[0])
				out_str += "?";
			else
				out_str += std::to_string(SP_IR[i].op[0]);
		}
		if(cnt_of_ops > 1) { // Second operand
			out_str += ", ";
			if(!SP_IR[i].tag[1])
				out_str += "?";
			else
				out_str += std::to_string(SP_IR[i].op[1]);
		}
		if(cnt_of_ops > 2) { // Third operand
			out_str += ", ";
			if(!SP_IR[i].tag[2])
				out_str += "?";
			else
				out_str += std::to_string(SP_IR[i].op[2]);
		}

		// Printing jump labels and addresses for jump instructions
		if(is_jmp_op) {
			std::string jmp_lbl(SP_IR[i].jmp_label);
			if(opcode == JWT)
				out_str += ", "; // JWT has operations
				
			out_str += jmp_lbl;
			out_str += "(";
			out_str += std::to_string(SP_IR[i].jmp_adr);
			out_str += ") ";
		}
		
		out_SPU_asm_IR << out_str;
	}
}

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