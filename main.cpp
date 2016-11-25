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

#ifndef ALGORITHM_
#include "include/Algorithm.h"
#endif

#ifndef IR2AST_
#include "include/IR2AST.h"
#endif

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(IR_Graph& gr);

void create_index(std::string js_name) {
	std::ofstream index_file;
	std::string path_to_index;
	if(strcmp(js_name.c_str(),"initial.js") == 0)
		path_to_index = "Visualisation/initial.html";
	else if(strcmp(js_name.c_str(),"arithmetic-logic.js") == 0)
		path_to_index = "Visualisation/arithmetic-logic.html";
	else if(strcmp(js_name.c_str(),"structure.js") == 0)
		path_to_index = "Visualisation/structure.html";
	index_file.open(path_to_index.c_str());
	
	index_file << "<!DOCTYPE html>\n" \
				<< "<html>\n" \
				<< "<head>\n" \
				<< "<link href=\"style.css\" rel=\"stylesheet\" />\n" \
				<< "<meta charset=utf-8 />\n" \
				<< "<meta name=\"viewport\" content=\"user-scalable=no, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, minimal-ui\">\n" \
				<< "<title>Images</title>\n" \
				<< "<script src=\"Cytospace/jquery-3.1.1.js\"></script>\n" \
				<< "<script src=\"Cytospace/cytoscape.min.js\"></script>\n" \
				<< "<script src=\"" \
				<< js_name \
				<< "\"></script>\n" \
				<< "</head>\n" \
				<< "<body>\n" \
				<< "<div id=\"cy\"></div>\n" \
				<< "</body>\n" \
				<< "</html>\n";
	
	index_file.close();
	return;
}

int main(int argc, char *argv[]) {
	if( argc < 3 ) {
		cout << "You need to specify input and output files." << endl;
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

	yyin = fp;
	yyout = out_fp;

	// Considering non-obligatory arguments
	visualisation_option option_vis = VIS_NONE;
	if( argc > 3 ) {
		if(strcmp(argv[3],"-v") == 0) {
			if(argc > 4) {
				char * option_params = argv[4];
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
			}
		}
	}

	IR_Graph result_graph;
	int status = yyparse(result_graph);

	IR_Graph* al_graph = Graph_ArithmeticLogicProcessing(&result_graph);
	IR_Graph* sp_graph = Graph_StructureProcessing(&result_graph);
	
	SequenceAST* al_AST = convertIRtoAST(al_graph);
	if(al_AST != NULL) {
		al_AST->print();
	}
	//Base_AST* sp_AST = convertIRtoAST(sp_graph);
	
	std::string i_gr_path;
	std::string al_gr_path;
	std::string sp_gr_path;
	std::string initial = "initial.js";
	std::string alp = "arithmetic-logic.js";
	std::string sp = "structure.js";
	
	std::string base_path = "Visualisation/";
	switch(option_vis) {
		case VIS_ALL:
			i_gr_path = base_path + initial;
			al_gr_path = base_path + alp;
			sp_gr_path = base_path + sp;
			create_index(initial);
			create_index(alp);
			create_index(sp);
			result_graph.visualise(i_gr_path);
			al_graph->visualise(al_gr_path);
			sp_graph->visualise(sp_gr_path);
			break;
		case VIS_INITIAL:
			i_gr_path = base_path + initial;
			create_index(initial);
			result_graph.visualise(i_gr_path);
			break;
		case VIS_ARITH:
			al_gr_path = base_path + alp;
			create_index(alp);
			al_graph->visualise(al_gr_path);
			break;
		case VIS_STRUCT:
			sp_gr_path = base_path + sp;
			create_index(sp);
			sp_graph->visualise(sp_gr_path);
			break;
		case VIS_INITIAL_ARITH:
			i_gr_path = base_path + initial;
			al_gr_path = base_path + alp;
			create_index(initial);
			create_index(alp);
			result_graph.visualise(i_gr_path);
			al_graph->visualise(al_gr_path);
			break;
		case VIS_INITIAL_STRUCT:
			i_gr_path = base_path + initial;
			sp_gr_path = base_path + sp;
			create_index(initial);
			create_index(sp);
			result_graph.visualise(i_gr_path);
			sp_graph->visualise(sp_gr_path);
			break;
		case VIS_ARITH_STRUCT:
			al_gr_path = base_path + alp;
			sp_gr_path = base_path + sp;
			create_index(alp);
			create_index(sp);
			al_graph->visualise(al_gr_path);
			sp_graph->visualise(sp_gr_path);
			break;
		case VIS_NONE:
			break;
	}
	
	fclose(fp);
	fclose(out_fp);


	if(status == 0)
		cout << endl << "*************************" << endl << "Compilation completed successfully." << endl;
	else
		cout << endl << "Some errors occured during compilation. Exiting (" << status << ")" << endl;
		
	return 0;
}
