#include "../include/TransferExpr.h"

TransferExpr::TransferExpr() {
	name_of_var = "";
	direction = TR_UNDEFINED;
}

TransferExpr::~TransferExpr() {
}
	
void TransferExpr::setNameOfVar(std::string a_name_of_var) {
	name_of_var = a_name_of_var;
}

void TransferExpr::setDirection(transfer_direction a_direction) {
	direction = a_direction;
}
	
std::string TransferExpr::getNameOfVar() {
	return name_of_var;
}

transfer_direction TransferExpr::getDirection() {
	return direction;
}

Base_AST * TransferExpr::copyAST() {
	TransferExpr * cpy = new TransferExpr(name_of_var, direction);
	
	return cpy;
}

void TransferExpr::print(std::ostream * print_stream) {
	* print_stream << "\n - Transfer expression: ";
	if(direction == TR_SEND) {
		* print_stream << " SEND ";
	} else if(direction == TR_RECEIVE) {
		* print_stream << " RECEIVE ";
	} else if(direction == TR_UNDEFINED) {
		* print_stream << " UNDEFINED ";
	}
	
	* print_stream << " variable " << name_of_var;
}

Value * TransferExpr::generateCode() {
	Value * ret = NULL;
	ret = NamedValues[name_of_var];
	
	// Signature of int ioctl(int fd, unsigned long request, ...) The third argument is either void * or char * (may be not present)
	Type* argsPTC[] = { Type::getInt16Ty(GlobalContext), Type::getInt32Ty(GlobalContext), Type::getInt32PtrTy(GlobalContext) };
	FunctionType* ioctlTy = FunctionType::get(Type::getInt16Ty(GlobalContext), ArrayRef<Type*>(argsPTC,3), false);
	Constant* c_ioctl = GlobalModule->getOrInsertFunction("ioctl",ioctlTy);
	Function* ioctl_func = cast<Function>(c_ioctl);
	
	if(direction == TR_SEND) {
		ret = Builder.CreateLoad(ret, name_of_var.c_str());
		// Inserting into IRBuilder command to send the data to SPU via PCI
		int dfd;
		if( ( dfd = open( "/dev/misd", O_RDWR ) ) < 0 ) std::cout << "Open MISD device error" << std::endl;
		unsigned long request = MISD_WRITE_IO;
		
		ConstantInt* words_count_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), 1);
		Value * llvm_alloca_data_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "data");
		Value * llvm_alloca_adr_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "adr");
		Builder.CreateInsertValue(llvm_alloca_data_array_inst, ret, std::vector<unsigned>(1, 0));
		//TODO: Placeholder for adr
		Value * elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), 0);
		Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, 0));
		
		Value * llvm_alloca_misdburst_struct_inst = Builder.CreateAlloca(burst_struct_type, nullptr, "misdburst");
		Value* insert_field1 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, words_count_val, std::vector<unsigned>(1, 0), "setcount");
		Value* insert_field2 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_adr_array_inst, std::vector<unsigned>(1, 1), "setdataptr");
		Value* insert_field3 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_data_array_inst, std::vector<unsigned>(1, 2), "setadrptr");

		std::vector<Value*> ArgsV;
		// First arg
		ConstantInt* fd_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), dfd);
		ArgsV.push_back(fd_val);
		// Second arg
		ConstantInt* request_val = ConstantInt::get(Type::getInt64Ty(GlobalContext), request);
		ArgsV.push_back(request_val);
		// Third arg
		ArgsV.push_back(llvm_alloca_misdburst_struct_inst);
		
		Builder.CreateCall(ioctl_func, ArgsV, "sent");
	} else if(direction == TR_RECEIVE) {
		// Inserting into IRBuilder command to send the data to SPU via PCI
		int dfd;
		if( ( dfd = open( "/dev/misd", O_RDWR ) ) < 0 ) std::cout << "Open MISD device error" << std::endl;
		unsigned long request = MISD_READ_IO;
		
		ConstantInt* words_count_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), 1);
		Value * llvm_alloca_data_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "data");
		Value * llvm_alloca_adr_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "adr");
		//TODO: Placeholder for adr
		Value * elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), 0);
		Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, 0));
		
		Value * llvm_alloca_misdburst_struct_inst = Builder.CreateAlloca(burst_struct_type, nullptr, "misdburst");
		Value* insert_field1 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, words_count_val, std::vector<unsigned>(1, 0), "setcount");
		Value* insert_field2 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_adr_array_inst, std::vector<unsigned>(1, 1), "setdataptr");
		Value* insert_field3 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_data_array_inst, std::vector<unsigned>(1, 2), "setadrptr");

		std::vector<Value*> ArgsV;
		// First arg
		ConstantInt* fd_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), dfd);
		ArgsV.push_back(fd_val);
		// Second arg
		ConstantInt* request_val = ConstantInt::get(Type::getInt64Ty(GlobalContext), request);
		ArgsV.push_back(request_val);
		// Third arg
		ArgsV.push_back(llvm_alloca_misdburst_struct_inst);
		
		Builder.CreateCall(ioctl_func, ArgsV, "received");
		Builder.CreateStore(llvm_alloca_data_array_inst, ret);
	}
	
	return ret;
}

std::string TransferExpr::generateStructCode() {
	std::string ret = "";
	return ret;
}