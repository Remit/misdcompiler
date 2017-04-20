#include "include/Passes.h"

int Compile(visualization_option option_vis, ast_IR_option option_ast_IR, std::string ast_filename, asm_IR_option option_asm_IR, std::string asm_filename, IR_Graph * src_result_graph, std::string out_filename, int iteration, std::string in_filename, TimeStamp * ts) {

	int dfd, status = -1;
	if( ( dfd = open( "/dev/misd", O_RDWR ) ) > 0 ) // TODO: Change to "<" after debug
		std::cout << "Open MISD device error, you need to have the MISD device and the MISD driver installed before compiling" << std::endl;
	else {
		IR_Graph* al_graph = new IR_Graph();
		IR_Graph* sp_graph = new IR_Graph();
		
		ts->startTime(in_filename,iteration,std::string("2 - Decomposing"));
		status = IRDecompositionPass(al_graph, sp_graph, src_result_graph, option_vis);
		ts->endTime(in_filename,iteration,std::string("2 - Decomposing"));
		
		if(status == 0) {
			// Construction of ASTs
			SequenceAST* al_AST = new SequenceAST();
			SequenceAST* sp_AST = new SequenceAST();
			ts->startTime(in_filename,iteration,std::string("3 - IR2AST"));
			status = IR2ASTConversionPass(al_AST, sp_AST, al_graph, sp_graph, option_ast_IR, ast_filename);
			ts->endTime(in_filename,iteration,std::string("3 - IR2AST"));
			if(status == 0) {
				// Generation of asm IRs
				ts->startTime(in_filename,iteration,std::string("4 - AST2ASM"));
				status = AST2ASMConversionPass(al_AST, sp_AST, option_asm_IR, asm_filename);
				ts->endTime(in_filename,iteration,std::string("4 - AST2ASM"));
				
				if(status == 0) {
					// Generation of binary code
					ts->startTime(in_filename,iteration,std::string("5 - ASM2BIN"));
					auto TargetTriple = sys::getDefaultTargetTriple();
					StringRef tt = sys::getHostCPUName();
					InitializeAllTargetInfos();
					InitializeAllTargets();
					InitializeAllTargetMCs();
					InitializeAllAsmParsers();
					InitializeAllAsmPrinters();
					
					std::string Error;
					auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);
					
					if(Target) {
						auto CPU = "generic";
						auto Features = "";//+feature,+feature,...
						TargetOptions opt;
						auto RM = Optional<Reloc::Model>();
						auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
						
						GlobalModule->setDataLayout(TargetMachine->createDataLayout());
						GlobalModule->setTargetTriple(TargetTriple);
						
						std::error_code EC;
						raw_fd_ostream dest(StringRef(out_filename.c_str()), EC, sys::fs::F_None);

						if (!EC) {
							legacy::PassManager pass;
							auto FileType = TargetMachine::CGFT_ObjectFile;

							if (!TargetMachine->addPassesToEmitFile(pass, dest, FileType)) {
								pass.run(*GlobalModule);
								dest.flush();
							}
						}
					}
					ts->endTime(in_filename,iteration,std::string("5 - ASM2BIN"));
				}
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
	initialize_SPU();

	if(asm_filename.compare("") == 0) {
		buf = std::cout.rdbuf();
	} else {
		of.open(asm_filename.c_str());
		buf = of.rdbuf();
	}

	std::ostream out_ASM_IR(buf);
	
	std::string al_hdr("\n ----- MACHINE CODE OF ARITHMETIC-LOGIC INSTRUCTIONS STREAM ----- \n");
	std::string sp_hdr("\n ----- MACHINE CODE OF STRUCTURE PROCESSING INSTRUCTIONS STREAM ----- \n");
	
	if((al_AST != NULL) && (sp_AST != NULL)) {		
		GlobalModule = new Module("MainModule", GlobalContext);
		FunctionType *FT = FunctionType::get(Type::getVoidTy(GlobalContext), false);
		Constant* c = GlobalModule->getOrInsertFunction("void",FT);
		Function* main_func = cast<Function>(c);
		main_func->setCallingConv(CallingConv::C);
		BasicBlock * startBB = BasicBlock::Create(GlobalContext, "start", main_func);
		Builder.SetInsertPoint(startBB);
		
		// Onetime declaration of misd burst struct type
		Type* type1 = Type::getInt16Ty(GlobalContext);
		Type* type23 = Type::getInt32PtrTy(GlobalContext);
		const std::vector< Type* > types = {type1, type23, type23};
		ArrayRef< Type * > TypesAr = ArrayRef< Type * >(types);
		StringRef struct_name = StringRef("misdbursttype");
		burst_struct_type = StructType::create(TypesAr, struct_name);
		
		// Generating SPU asm IR for SP-instructions stream
		sp_AST->generateStructCode();
		// TODO: Inserting the last command to halt the SPU program
		SP_IR[mem_point].tag[0] = false; // waiting for address
		SP_IR[mem_point].tag[1] = true; // Not in use
		SP_IR[mem_point].tag[2] = true; // Not in use
		SP_IR[mem_point].op[0] = 0; // Unconditional branch
		SP_IR[mem_point].op[1] = 0; // Not in use
		SP_IR[mem_point].op[2] = 0; // Not in use
		SP_IR[mem_point].opcode = JT; // Jump to condition after the loop body is processed
		SP_IR[mem_point].q = false;
		SP_IR[mem_point].jmp_adr = -1;
		mem_point++;
		
		SPU_IR2BIN(); // Generating binary of SP-instructions stream
		//TODO: Inserting at start commands to store the binary representation of the SPU program in the memory of target machine

		// Signature of int ioctl(int fd, unsigned long request, ...) The third argument is either void * or char * (may be not present)
		Type* argsPTC[] = { Type::getInt16Ty(GlobalContext), Type::getInt32Ty(GlobalContext), Type::getInt32PtrTy(GlobalContext) };
		FunctionType* ioctlTy = FunctionType::get(Type::getInt16Ty(GlobalContext), ArrayRef<Type*>(argsPTC,3), false);
		Constant* c_ioctl = GlobalModule->getOrInsertFunction("ioctl",ioctlTy);
		Function* ioctl_func = cast<Function>(c_ioctl);
		// Transforming binary representation of SPU code into format for PCI transfer
		
		
		unsigned int words_count = ceil( ( (float) mem_point * 5 * sizeof(unsigned int) ) / sizeof(unsigned long) ); // Computing number of words to transfer to SPU via PCI
		//unsigned long* adr = (unsigned long*)malloc(sizeof(unsigned long)); // Allocating memory for address
		//unsigned long* data = (unsigned long*)calloc(words_count, sizeof(unsigned long)); // Allocating memory for binary SPU program to transfer it to SPU via PCI
		
		//ArrayType* arrayType = ArrayType::get(Type::getInt32Ty(GlobalContext), words_count);
		ConstantInt* words_count_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), words_count);
		Value * llvm_alloca_data_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "data");
		Value * llvm_alloca_adr_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "adr");
		
		Value * llvm_alloca_misdburst_struct_inst = Builder.CreateAlloca(burst_struct_type, nullptr, "misdburst");
		Value * idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), 0);
		Value * first_field = Builder.CreateGEP(burst_struct_type,llvm_alloca_misdburst_struct_inst, idx, "get1elemptr");
		Builder.CreateStore(words_count_val, first_field);
		idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), 1);
		Value * second_field = Builder.CreateGEP(burst_struct_type,llvm_alloca_misdburst_struct_inst, idx, "get2elemptr");
		Builder.CreateStore(llvm_alloca_adr_array_inst, second_field);
		idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), 2);
		Value * third_field = Builder.CreateGEP(burst_struct_type,llvm_alloca_misdburst_struct_inst, idx, "get3elemptr");
		Builder.CreateStore(llvm_alloca_data_array_inst, third_field);
//		Value* insert_field1 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, words_count_val, std::vector<unsigned>(0), "setcount");
//		Value* insert_field2 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_adr_array_inst, std::vector<unsigned>(1), "setdataptr");
//		Value* insert_field3 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_data_array_inst, std::vector<unsigned>(2), "setadrptr");
		

		int j = 0;
		unsigned long tmp, elem;
		ConstantInt* elem_val;
		Value * memory_reg;
		for(int i = 0; i < MEM_LENGTH; i++) {
			if(i % 2 != 0) {//uneven lines
				tmp = SP_BIN[i][0];
				elem = (tmp << 16) & 0xFFFF0000;
				tmp = SP_BIN[i][1];
				elem = elem | tmp;
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), elem);
				idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), j);
				memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_data_array_inst, idx);
				Builder.CreateStore(elem_val, memory_reg);
				//Builder.CreateInsertValue(llvm_alloca_data_array_inst, elem_val, std::vector<unsigned>(1, j));
				//TODO: Placeholder for adr
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), j);
				//Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, j));
				j++;
				
				tmp = SP_BIN[i][2];
				elem = (tmp << 16) & 0xFFFF0000;
				tmp = SP_BIN[i][3];
				elem = elem | tmp;
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), elem);
				idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), j);
				memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_data_array_inst, idx);
				Builder.CreateStore(elem_val, memory_reg);
				//Builder.CreateInsertValue(llvm_alloca_data_array_inst, elem_val, std::vector<unsigned>(1, j));
				//TODO: Placeholder for adr
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), j);
				//Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, j));
				j++;
			} else { //even lines
				tmp = SP_BIN[i-1][4];
				elem = (tmp << 16) & 0xFFFF0000;
				tmp = SP_BIN[i][0];
				elem = elem | tmp;
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), elem);
				idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), j);
				memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_data_array_inst, idx);
				Builder.CreateStore(elem_val, memory_reg);
				//Builder.CreateInsertValue(llvm_alloca_data_array_inst, elem_val, std::vector<unsigned>(1, j));
				//TODO: Placeholder for adr
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), j);
				//Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, j));
				j++;
				
				tmp = SP_BIN[i][1];
				elem = (tmp << 16) & 0xFFFF0000;
				tmp = SP_BIN[i][2];
				elem = elem | tmp;
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), elem);
				idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), j);
				memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_data_array_inst, idx);
				Builder.CreateStore(elem_val, memory_reg);
				//Builder.CreateInsertValue(llvm_alloca_data_array_inst, elem_val, std::vector<unsigned>(1, j));
				//TODO: Placeholder for adr
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), j);
				//Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, j));
				j++;
				
				tmp = SP_BIN[i][3];
				elem = (tmp << 16) & 0xFFFF0000;
				tmp = SP_BIN[i][4];
				elem = elem | tmp;
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), elem);
				idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), j);
				memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_data_array_inst, idx);
				Builder.CreateStore(elem_val, memory_reg);
				//Builder.CreateInsertValue(llvm_alloca_data_array_inst, elem_val, std::vector<unsigned>(1, j));
				//TODO: Placeholder for adr
				elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), j);
				//Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, j));
				j++;
			}
		}
		if(mem_point % 2 != 0) { //Last word for uneven number of binary lines
			tmp = SP_BIN[mem_point - 1][4];
			elem = (tmp << 16) & 0xFFFF0000;
			elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), elem);
			//Builder.CreateInsertValue(llvm_alloca_data_array_inst, elem_val, std::vector<unsigned>(1, j));
			idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), j);
			memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_data_array_inst, idx);
			Builder.CreateStore(elem_val, memory_reg);
			//TODO: Placeholder for adr
			elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), j);
			//Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, j));
		}
		
		
		// Creating open function for the device in Linux: int open(const char *path, int oflag, ... );
		Type* argsPTCopen[] = { Type::getInt8PtrTy(GlobalContext), Type::getInt16Ty(GlobalContext) };
		FunctionType* openTy = FunctionType::get(Type::getInt16Ty(GlobalContext), ArrayRef<Type*>(argsPTCopen,2), false);
		Constant* c_open = GlobalModule->getOrInsertFunction("open",openTy);
		Function* open_func = cast<Function>(c_open);
		
		std::vector<Value*> ArgsVopen;
		// First arg - a path to the device driver in Linux, should be placed as an array of chars (ends with \0) in memory by program
		ConstantInt* number_of_chars = ConstantInt::get(Type::getInt16Ty(GlobalContext), 10);
		Value * llvm_alloca_device_chars = Builder.CreateAlloca(Type::getInt8Ty(GlobalContext), number_of_chars, "device_chars");
		char* device_name = "/dev/misd";
		for(int k = 0; k < 10; k++) {
			char symbol = device_name[k];
			idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), k);
			memory_reg = Builder.CreateGEP(Type::getInt8Ty(GlobalContext),llvm_alloca_device_chars, idx);
			elem_val = ConstantInt::get(Type::getInt8Ty(GlobalContext), symbol);
			Builder.CreateStore(elem_val, memory_reg);
		}
		ArgsVopen.push_back(llvm_alloca_device_chars);
		// Second arg
		ConstantInt* open_settings_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), O_RDWR);
		ArgsVopen.push_back(open_settings_val);
		
		// Opening MISD device from the program itself
		Value * open_device_call = Builder.CreateCall(open_func, ArgsVopen, "callopendevice");
		// Additional check - compare result of function with 0, if below 0 then no device was found, stop compilation
		
		// Inserting into IRBuilder command to send the binary SPU code to SPU via PCI
		unsigned long request = MISD_WRITE_LCM;

		std::vector<Value*> ArgsV;
		// First arg
		//ConstantInt* fd_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), dfd);
		ArgsV.push_back(open_device_call);
		// Second arg
		ConstantInt* request_val = ConstantInt::get(Type::getInt64Ty(GlobalContext), request);
		ArgsV.push_back(request_val);
		// Third arg
		ArgsV.push_back(llvm_alloca_misdburst_struct_inst);
		
		Builder.CreateCall(ioctl_func, ArgsV, "callioctl");
		
		// Generating LLVM IR for AL-instructions stream
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
				print_SPU_asm_IR(&out_ASM_IR);
				break;
			case ASM_IR_CPU:
				out_ASM_IR << al_hdr;
				out_ASM_IR << asm_llvm;
				break;
			case ASM_IR_SPU:
				out_ASM_IR << sp_hdr;
				print_SPU_asm_IR(&out_ASM_IR);
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