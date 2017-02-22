#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "include/CommonTypesAndConstants.h"
#endif

#ifndef IRGRAPH_H_
#include "include/IRGraph.h"
#endif

#ifndef PASSES_H_
#include "include/Passes.h"
#endif

LLVMContext GlobalContext;
IRBuilder<> Builder(GlobalContext);
Module * GlobalModule;
std::map<std::string, AllocaInst *> NamedValues;
StructType * burst_struct_type;

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(IR_Graph& gr);

int main(int argc, char *argv[]) {
	if( argc < 3 ) {
		cout << "You need to specify at least input and output files." << endl;
		exit(0);
	}

	FILE *fp = fopen(argv[1],"r");
	if( !fp ) {
		cout << "Could not open the file for reading." << endl;
		exit(0);
	}

	FILE *out_fp = fopen(argv[2],"w");
	if( ! out_fp ) {
		cout << "Could not open the file for writing." << endl;
		exit(0);
	}
	
	std::string out_filename(argv[2]);

	yyin = fp;
	yyout = out_fp;

	// Considering non-obligatory arguments
	int basis_opt_adr = 3;
	
	// Visualization options
	visualization_option option_vis = VIS_NONE;
	if( argc > basis_opt_adr) {
		if(strcmp(argv[basis_opt_adr],"-v") == 0) {
			basis_opt_adr++;
			if(argc > basis_opt_adr) {
				char * option_params = argv[basis_opt_adr];
				if(strcmp(option_params,"ias") == 0) 
					option_vis = VIS_ALL;
				else if(strcmp(option_params,"i--") == 0)
					option_vis = VIS_INITIAL;
				else if (strcmp(option_params,"-a-") == 0)
					option_vis = VIS_ARITH;
				else if (strcmp(option_params,"--s") == 0)
					option_vis = VIS_STRUCT;
				else if (strcmp(option_params,"ia-") == 0)
					option_vis = VIS_INITIAL_ARITH;
				else if (strcmp(option_params,"i-s") == 0)
					option_vis = VIS_INITIAL_STRUCT;
				else if (strcmp(option_params,"-as") == 0)
					option_vis = VIS_ARITH_STRUCT;
				else if (strcmp(option_params,"---") == 0)
					option_vis = VIS_NONE;
				else
					cout << "Error: Non-existent arguments for \'-v\'." << endl;
					
				basis_opt_adr++;
			} else {
				cout << "Error: No arguments for \'-v\'." << endl;
			}
		}
	}
	
	// Considering output of AST IRs of CPU code and SPU code
	ast_IR_option option_ast_IR = AST_IR_NONE;
	std::string ast_filename;
	if(argc > basis_opt_adr) {
		if(strcmp(argv[basis_opt_adr],"-ast") == 0) {
			basis_opt_adr++;
			if(argc > basis_opt_adr) {

				char * option_params = argv[basis_opt_adr];
				if(strlen(option_params) == 3) {
					char * option_params_main = (char*)malloc(2);
					char * option_params_file = (char*)malloc(1);
					strncpy(option_params_main,option_params,2);
					option_params_main[2]='\0';
					strncpy(option_params_file,option_params + 2,1);
					option_params_file[1]='\0';
					if(strcmp(option_params_main,"as") == 0) 
						option_ast_IR = AST_IR_ALL;
					else if(strcmp(option_params_main,"a-") == 0)
						option_ast_IR = AST_IR_CPU;
					else if (strcmp(option_params_main,"-s") == 0)
						option_ast_IR = AST_IR_SPU;
					else if (strcmp(option_params_main,"--") == 0)
						option_ast_IR = AST_IR_NONE;
					else
						cout << "Error: Non-existent arguments for AST printing settings in \'-ast\'." << endl;
						
					size_t flag_pos = 2;
					basis_opt_adr++;
					if(argc > basis_opt_adr) {
						if(strcmp(option_params_file,"f")  == 0) {
							ast_filename.assign(argv[basis_opt_adr]);
						} else if(strcmp(option_params_file,"-")  != 0) {
							cout << "Error: Non-existent argument for AST file print option in \'-ast\'." << endl;
						}
						basis_opt_adr++;
					}
				}
			} else {
				cout << "Error: No arguments for \'-ast\'." << endl;
			}
		}
	}
	
	// Considering output of asm IRs of CPU code and SPU code
	asm_IR_option option_asm_IR = ASM_IR_NONE;
	std::string asm_filename;
	if(argc > basis_opt_adr) {
		if(strcmp(argv[basis_opt_adr],"-asm") == 0) {
			basis_opt_adr++;
			if(argc > basis_opt_adr) {

				char * option_params = argv[basis_opt_adr];
				if(strlen(option_params) == 3) {
					char * option_params_main = (char*)malloc(2);
					char * option_params_file = (char*)malloc(1);
					strncpy(option_params_main,option_params,2);
					option_params_main[2]='\0';
					strncpy(option_params_file,option_params + 2,1);
					option_params_file[1]='\0';
					if(strcmp(option_params_main,"as") == 0) 
						option_asm_IR = ASM_IR_ALL;
					else if(strcmp(option_params_main,"a-") == 0)
						option_asm_IR = ASM_IR_CPU;
					else if (strcmp(option_params_main,"-s") == 0)
						option_asm_IR = ASM_IR_SPU;
					else if (strcmp(option_params_main,"--") == 0)
						option_asm_IR = ASM_IR_NONE;
					else
						cout << "Error: Non-existent arguments for asm IR printing settings in \'-asm\'." << endl;
						
					size_t flag_pos = 2;
					basis_opt_adr++;
					if(argc > basis_opt_adr) {
						if(strcmp(option_params_file,"f")  == 0) {
							asm_filename.assign(argv[basis_opt_adr]);
						} else if(strcmp(option_params_file,"-")  != 0) {
							cout << "Error: Non-existent argument for asm IR file print option in \'-asm\'." << endl;
						}
						basis_opt_adr++;
					}
				}
			} else {
				cout << "Error: No arguments for \'-asm\'." << endl;
			}
		}
	}
	

	IR_Graph result_graph;
	int status = yyparse(result_graph);
	fclose(fp);
	fclose(out_fp);
	remove(argv[2]);
	if(status == 0) {
		status = Compile(option_vis, option_ast_IR, ast_filename, option_asm_IR, asm_filename, &result_graph, out_filename);
	}

	if(status == 0)
		cout << endl << "*************************" << endl << "Compilation completed successfully." << endl;
	else
		cout << endl << "Some errors occured during compilation. Exiting (" << status << ")" << endl;
		
	return 0;
}
