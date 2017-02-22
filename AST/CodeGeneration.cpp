#ifndef CODEGENERATION_H_
#include "../include/CodeGeneration.h"
#endif

spu_cmd SP_IR[MEM_LENGTH];
unsigned int SP_BIN[MEM_LENGTH][5];
int mem_point = 0;
int label_i = 0;



// This procedure prints the asm representation
// of SPU program either to file or to the
// standard output.
void print_SPU_asm_IR(std::ostream * print_stream) {
	
	// Printing asm IR
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
			case JT:
				operation = "JT";
				cnt_of_ops = JT_C;
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

		out_str += operation;
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
			if(opcode == JT)
				out_str += ", "; // JT has operations
				
			out_str += jmp_lbl;
			out_str += "(";
			out_str += std::to_string(SP_IR[i].jmp_adr);
			out_str += ") ";
		}
		
		* print_stream << out_str << std::endl;
	}

	// Printing binary in text format
	* print_stream << std::endl;
	* print_stream << " -- BINARY REPRESENTATION OF SPU ASM CODE -- " << std::endl;
	for(int i = 0; i < mem_point; i++) {
		std::string out_str;
		
		out_str += std::to_string(i);
		int left_syms_a = 8 - std::to_string(i).length() - 1;
		while(left_syms_a > 0) {
			out_str += " ";
			left_syms_a--;
		}
		out_str += "| ";
		
		for(int j = 0; j < 5; j++) {
			for(int k = 15; k >= 0; k--) {
				if((SP_BIN[i][j] >> k) & 0x0001)
					out_str += "1";
				else
					out_str += "0";
			}
		}
		* print_stream << out_str << std::endl;
	}
}

void SPU_IR2BIN() {
	unsigned int first, second, third, fourth, fifth; // From leftmost to rightmost
	unsigned int tmp;
	
	for(int point = 0; point < mem_point; point++) {
		switch (SP_IR[point].opcode) {
			// format 1
			case DELS: case MAX: case MIN: case POWER: case SQUIZ: {
				
				first = 0x0000;
				second = 0x0000;
				
				third = 0x0000;
				fourth = 0x0000;
				
				//queue
				if (SP_IR[point].q)
					fifth = 0x8000; // representation of 100...0b
				else
					fifth = 0x0000;
				
				tmp = SP_IR[point].op[0]; // Adding structure ID
				fifth = fifth | (tmp << 8);

				tmp = SP_IR[point].opcode; // Adding operation code
				fifth = fifth | (tmp << 3);

				// Third tag
				if (SP_IR[point].tag[2])
					tmp = 0x0004; // representation of 0...00100b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// Second tag
				if (SP_IR[point].tag[1])
					tmp = 0x0002; // representation of 0...0010b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// First tag
				if (SP_IR[point].tag[0])
					tmp = 0x0001; // representation of 0...001b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				break;
			}
			// format 2
			case DEL: case SEARCH: {
				
				first = 0x0000;
				second = 0x0000;
				
				third = (SP_IR[point].op[1] >> 16) & 0x0000FFFF; // Leftmost of the operand
				fourth = SP_IR[point].op[1] & 0x0000FFFF; //Rightmost bits of the operand
				
				//queue
				if (SP_IR[point].q)
					fifth = 0x8000; // representation of 100...0b
				else
					fifth = 0x0000;
				
				tmp = SP_IR[point].op[0]; // Adding structure ID
				fifth = fifth | (tmp << 8);

				tmp = SP_IR[point].opcode; // Adding operation code
				fifth = fifth | (tmp << 3);

				// Third tag
				if (SP_IR[point].tag[2])
					tmp = 0x0004; // representation of 0...00100b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// Second tag
				if (SP_IR[point].tag[1])
					tmp = 0x0002; // representation of 0...0010b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// First tag
				if (SP_IR[point].tag[0])
					tmp = 0x0001; // representation of 0...001b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				break;
			}
			// format 3
			case ADD: {
				
				first = (SP_IR[point].op[2] >> 16) & 0x0000FFFF; // Leftmost of the operand
				second = SP_IR[point].op[2] & 0x0000FFFF; //Rightmost bits of the operand
				
				third = (SP_IR[point].op[1] >> 16) & 0x0000FFFF; // Leftmost of the operand
				fourth = SP_IR[point].op[1] & 0x0000FFFF; //Rightmost bits of the operand
				
				//queue
				if (SP_IR[point].q)
					fifth = 0x8000; // representation of 100...0b
				else
					fifth = 0x0000;
				
				tmp = SP_IR[point].op[0]; // Adding structure ID
				fifth = fifth | (tmp << 8);

				tmp = SP_IR[point].opcode; // Adding operation code
				fifth = fifth | (tmp << 3);

				// Third tag
				if (SP_IR[point].tag[2])
					tmp = 0x0004; // representation of 0...00100b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// Second tag
				if (SP_IR[point].tag[1])
					tmp = 0x0002; // representation of 0...0010b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// First tag
				if (SP_IR[point].tag[0])
					tmp = 0x0001; // representation of 0...001b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				break;
			}
			// format 4
			case AND: case OR: case NOT: {
				
				first = 0x0000;
				second = 0x0000;
				
				third = 0x0000;
				fourth = (SP_IR[point].op[2] << 8) & 0x0000FF00;
				tmp = SP_IR[point].op[1] & 0x000000FF;
				fourth = fourth | tmp;
				
				//queue
				if (SP_IR[point].q)
					fifth = 0x8000; // representation of 100...0b
				else
					fifth = 0x0000;
				
				tmp = SP_IR[point].op[0]; // Adding structure ID
				fifth = fifth | (tmp << 8);

				tmp = SP_IR[point].opcode; // Adding operation code
				fifth = fifth | (tmp << 3);

				// Third tag
				if (SP_IR[point].tag[2])
					tmp = 0x0004; // representation of 0...00100b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// Second tag
				if (SP_IR[point].tag[1])
					tmp = 0x0002; // representation of 0...0010b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// First tag
				if (SP_IR[point].tag[0])
					tmp = 0x0001; // representation of 0...001b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				break;
			}
			// format 5
			case LS: case LSEQ: case GR: case GREQ: {
				
				first = 0x0000;
				second = (SP_IR[point].op[2] >> 24) & 0x000000FF;
				
				third = (SP_IR[point].op[2] >> 8) & 0x0000FFFF;
				fourth = (SP_IR[point].op[2] << 8) & 0x0000FF00;
				tmp = SP_IR[point].op[1] & 0x000000FF;
				fourth = fourth | tmp;
				
				//queue
				if (SP_IR[point].q)
					fifth = 0x8000; // representation of 100...0b
				else
					fifth = 0x0000;
				
				tmp = SP_IR[point].op[0]; // Adding structure ID
				fifth = fifth | (tmp << 8);

				tmp = SP_IR[point].opcode; // Adding operation code
				fifth = fifth | (tmp << 3);

				// Third tag
				if (SP_IR[point].tag[2])
					tmp = 0x0004; // representation of 0...00100b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// Second tag
				if (SP_IR[point].tag[1])
					tmp = 0x0002; // representation of 0...0010b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// First tag
				if (SP_IR[point].tag[0])
					tmp = 0x0001; // representation of 0...001b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				break;
			}
			// format 6
			case JT: { //TODO: Synchronize with the description using 1 and 0 tags
				
				first = 0x0000;
				second = 0x0000;
				third = (SP_IR[point].jmp_adr >> 24) & 0x000000FF;
				
				fourth = (SP_IR[point].jmp_adr >> 8) & 0x0000FFFF;
				
				fifth = (SP_IR[point].jmp_adr << 8) & 0x0000FF00;
				tmp = SP_IR[point].opcode; // Adding operation code
				fifth = fifth | (tmp << 3);

				// Third tag
				if (SP_IR[point].tag[2])
					tmp = 0x0004; // representation of 0...00100b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// Second tag
				if (SP_IR[point].tag[1])
					tmp = 0x0002; // representation of 0...0010b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				// First tag
				if (SP_IR[point].tag[0])
					tmp = 0x0001; // representation of 0...001b
				else
					tmp = 0x0000;
				fifth = fifth | tmp;
				
				break;
			}
		}
	
		SP_BIN[point][0] = first;
		SP_BIN[point][1] = second;
		SP_BIN[point][2] = third;
		SP_BIN[point][3] = fourth;
		SP_BIN[point][4] = fifth;
	}
	
	for(int point = mem_point; point < MEM_LENGTH; point++) {
		SP_BIN[point][0] = 0x0000;
		SP_BIN[point][1] = 0x0000;
		SP_BIN[point][2] = 0x0000;
		SP_BIN[point][3] = 0x0000;
		SP_BIN[point][4] = 0x0000;
	}
}