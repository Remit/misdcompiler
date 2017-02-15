#include "include/Passes.h"

int Compile(visualization_option option_vis, ast_IR_option option_ast_IR, std::string ast_filename, asm_IR_option option_asm_IR, std::string asm_filename, IR_Graph * src_result_graph, std::string out_filename) {

	IR_Graph* al_graph = new IR_Graph();
	IR_Graph* sp_graph = new IR_Graph();
	
	int status = IRDecompositionPass(al_graph, sp_graph, src_result_graph, option_vis);
	
	if(status == 0) {
		// Construction of ASTs
		SequenceAST* al_AST = new SequenceAST();
		SequenceAST* sp_AST = new SequenceAST();
		status = IR2ASTConversionPass(al_AST, sp_AST, al_graph, sp_graph, option_ast_IR, ast_filename);
			
		if(status == 0) {
			// Generation of asm IRs
			status = AST2ASMConversionPass(al_AST, sp_AST, option_asm_IR, asm_filename);
			
			if(status == 0) {
				// Generation of binary code
				// TODO:
			}
		}
	}
	
	return status;
}


int IRDecompositionPass(IR_Graph* al_graph, IR_Graph* sp_graph, IR_Graph * src_result_graph, visualization_option option_vis) {
	int al_stat, sp_stat;
	if(src_result_graph != NULL) {
		al_stat = Graph_ArithmeticLogicProcessing(src_result_graph, al_graph);
		sp_stat = Graph_StructureProcessing(src_result_graph, sp_graph);
	}
	
	if((al_stat == 0) && (sp_stat == 0)) {
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
				src_result_graph->visualise(i_gr_path);
				al_graph->visualise(al_gr_path);
				sp_graph->visualise(sp_gr_path);
				break;
			case VIS_INITIAL:
				i_gr_path = base_path + initial;
				create_index(initial);
				src_result_graph->visualise(i_gr_path);
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
				src_result_graph->visualise(i_gr_path);
				al_graph->visualise(al_gr_path);
				break;
			case VIS_INITIAL_STRUCT:
				i_gr_path = base_path + initial;
				sp_gr_path = base_path + sp;
				create_index(initial);
				create_index(sp);
				src_result_graph->visualise(i_gr_path);
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
		
		return 0;
	}
	else
		return 1;
}

int IR2ASTConversionPass(SequenceAST* al_AST, SequenceAST* sp_AST, IR_Graph* al_graph, IR_Graph* sp_graph, ast_IR_option option_ast_IR, std::string ast_filename) {
	std::streambuf * buf;
	std::ofstream of;

	if(ast_filename.compare("") == 0) {
		buf = std::cout.rdbuf();
	} else {
		of.open(ast_filename.c_str());
		buf = of.rdbuf();
	}

	std::ostream out_AST_IR(buf);
	
	int al_ast_res, sp_ast_res;
	al_ast_res = convertIRtoAST(al_graph, al_AST);
	sp_ast_res = convertIRtoAST(sp_graph, sp_AST);
	
	std::string al_hdr("\n ----- AST OF ARITHMETIC-LOGIC GRAPH ----- \n");
	std::string sp_hdr("\n ----- AST OF STRUCTURE PROCESSING GRAPH ----- \n");
	
	if((al_ast_res == 0) && (sp_ast_res == 0)) {
		switch(option_ast_IR) {
			case AST_IR_ALL:
				out_AST_IR << al_hdr;
				al_AST->print(&out_AST_IR);
				out_AST_IR << std::endl;
				out_AST_IR << sp_hdr;
				sp_AST->print(&out_AST_IR);
				break;
			case AST_IR_CPU:
				out_AST_IR << al_hdr;
				al_AST->print(&out_AST_IR);
				break;
			case AST_IR_SPU:
				out_AST_IR << sp_hdr;
				sp_AST->print(&out_AST_IR);
				break;
			case AST_IR_NONE:
				break;
		}
		
		return 0;
	} else {
		return 1;
	}
}

int AST2ASMConversionPass(SequenceAST* al_AST, SequenceAST* sp_AST, asm_IR_option option_asm_IR, std::string asm_filename) {
	std::streambuf * buf;
	std::ofstream of;

	if(asm_filename.compare("") == 0) {
		buf = std::cout.rdbuf();
		std::cout << "HI FUCK!" << std::endl;
	} else {
		of.open(asm_filename.c_str());
		buf = of.rdbuf();
	}

	std::ostream out_ASM_IR(buf);
	
	std::string al_hdr("\n ----- MACHINE CODE OF ARITHMETIC-LOGIC INSTRUCTIONS STREAM ----- \n");
	std::string sp_hdr("\n ----- MACHINE CODE OF STRUCTURE PROCESSING INSTRUCTIONS STREAM ----- \n");
	
	if((al_AST != NULL) && (sp_AST != 0)) {
		GlobalModule = new Module("MainModule", GlobalContext);
		FunctionType *FT = FunctionType::get(Type::getVoidTy(GlobalContext), false);
		Constant* c = GlobalModule->getOrInsertFunction("void",FT);
		Function* main_func = cast<Function>(c);
		main_func->setCallingConv(CallingConv::C);
		BasicBlock * startBB = BasicBlock::Create(GlobalContext, "start", main_func);
		Builder.SetInsertPoint(startBB);

		al_AST->generateCode();
				
		Builder.CreateRetVoid();
				
		std::string asm_llvm;
		raw_string_ostream OS(asm_llvm);
		GlobalModule->print(OS,nullptr);
		
		switch(option_asm_IR) {
			case ASM_IR_ALL:
				out_ASM_IR << al_hdr;
				out_ASM_IR << asm_llvm;
				out_ASM_IR << std::endl;
				out_ASM_IR << sp_hdr;
				//sp_AST->print(&out_AST_IR);
				break;
			case ASM_IR_CPU:
				out_ASM_IR << al_hdr;
				out_ASM_IR << asm_llvm;
				break;
			case ASM_IR_SPU:
				out_ASM_IR << sp_hdr;
				//sp_AST->print(&out_AST_IR);
				break;
			case ASM_IR_NONE:
				break;
		}
		
		return 0;
	} else {
		return 1;
	}
}

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