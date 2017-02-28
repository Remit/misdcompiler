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
	Value * memory_reg;
	
	if(direction == TR_SEND) {
		ret = Builder.CreateLoad(ret, name_of_var.c_str());
		// Inserting into IRBuilder command to send the data to SPU via PCI
		unsigned long request = MISD_WRITE_IO;
		
		ConstantInt* words_count_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), 1);
		Value * llvm_alloca_data_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "data");
		Value * llvm_alloca_adr_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "adr");
		Value * idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), 0);
		memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_data_array_inst, idx);
		Builder.CreateStore(ret, memory_reg);
		//Builder.CreateInsertValue(llvm_alloca_data_array_inst, ret, std::vector<unsigned>(1, 0));
		//TODO: Placeholder for adr
		Value * elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), 0);
		memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_adr_array_inst, idx);
		Builder.CreateStore(ret, memory_reg);
//		Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, 0));
		
		Value * llvm_alloca_misdburst_struct_inst = Builder.CreateAlloca(burst_struct_type, nullptr, "misdburst");
		idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), 0);
		Value * first_field = Builder.CreateGEP(burst_struct_type,llvm_alloca_misdburst_struct_inst, idx, "get1elemptr");
		Builder.CreateStore(words_count_val, first_field);
		idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), 1);
		Value * second_field = Builder.CreateGEP(burst_struct_type,llvm_alloca_misdburst_struct_inst, idx, "get2elemptr");
		Builder.CreateStore(llvm_alloca_adr_array_inst, second_field);
		idx = ConstantInt::get(Type::getInt16Ty(GlobalContext), 2);
		Value * third_field = Builder.CreateGEP(burst_struct_type,llvm_alloca_misdburst_struct_inst, idx, "get3elemptr");
		Builder.CreateStore(llvm_alloca_data_array_inst, third_field);
//		Value* insert_field1 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, words_count_val, std::vector<unsigned>(1, 0), "setcount");
//		Value* insert_field2 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_adr_array_inst, std::vector<unsigned>(1, 1), "setdataptr");
//		Value* insert_field3 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_data_array_inst, std::vector<unsigned>(1, 2), "setadrptr");

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
		Value * memory_reg;
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

		std::vector<Value*> ArgsV;
		// First arg
		ArgsV.push_back(open_device_call);
		// Second arg
		ConstantInt* request_val = ConstantInt::get(Type::getInt64Ty(GlobalContext), request);
		ArgsV.push_back(request_val);
		// Third arg
		ArgsV.push_back(llvm_alloca_misdburst_struct_inst);
		
		Builder.CreateCall(ioctl_func, ArgsV, "sent");
	} else if(direction == TR_RECEIVE) {
		// Inserting into IRBuilder command to send the data to SPU via PCI
		unsigned long request = MISD_READ_IO;
		
		ConstantInt* words_count_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), 1);
		Value * llvm_alloca_data_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "data");
		Value * llvm_alloca_adr_array_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), words_count_val, "adr");
		//TODO: Placeholder for adr
		Value * elem_val = ConstantInt::get(Type::getInt32Ty(GlobalContext), 0);
		memory_reg = Builder.CreateGEP(Type::getInt32Ty(GlobalContext),llvm_alloca_adr_array_inst, elem_val);
		Builder.CreateStore(ret, memory_reg);
//		Builder.CreateInsertValue(llvm_alloca_adr_array_inst, elem_val, std::vector<unsigned>(1, 0));
		
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
//		Value* insert_field1 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, words_count_val, std::vector<unsigned>(1, 0), "setcount");
//		Value* insert_field2 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_adr_array_inst, std::vector<unsigned>(1, 1), "setdataptr");
//		Value* insert_field3 = Builder.CreateInsertValue(llvm_alloca_misdburst_struct_inst, llvm_alloca_data_array_inst, std::vector<unsigned>(1, 2), "setadrptr");

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

		std::vector<Value*> ArgsV;
		// First arg
		ArgsV.push_back(open_device_call);
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