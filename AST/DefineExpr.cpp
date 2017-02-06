#include "../include/DefineExpr.h"

DefineExpr::DefineExpr()
{
	def_type = VAR_UNDEFINED;
}

DefineExpr::~DefineExpr()
{
}

void DefineExpr::setTypeOfVars(variable_type a_def_type) {
	def_type = a_def_type;
}

variable_type DefineExpr::getTypeOfVars() {
	return def_type;
}

void DefineExpr::setListOfNames(std::vector<std::string> * a_defined_names) {
	if(a_defined_names != NULL) {
		for(int i = 0; i < a_defined_names->size(); i++)
			defined_names.push_back((*a_defined_names)[i]);
	}
}

std::vector<std::string> * DefineExpr::getListOfNames() {
	std::vector<std::string> * ret_defined_names = new std::vector<std::string>;
	
	for(int i = 0; i < defined_names.size(); i++)
		ret_defined_names->push_back(defined_names[i]);
		
	return ret_defined_names;
}
	
Base_AST * DefineExpr::copyAST() {
	std::vector<std::string> * a_defined_names = getListOfNames();
	DefineExpr * cpy = new DefineExpr(a_defined_names, def_type);
	return cpy;
}
	
void DefineExpr::print() {
	std::string type_name = "";
	switch(def_type) {
	case VAR_INT:
		type_name = "integer";
		break;
	case VAR_LONG:
		type_name = "long";
		break;
	case VAR_FLOAT:
		type_name = "float";
		break;
	case VAR_DOUBLE:
		type_name = "double";
		break;
	case VAR_UNDEFINED:
		type_name = "undefined";
		break;
	}
	
	std::cout << "\n - Define the following variables of " <<  type_name << " type: ";
	for(int i = 0; i < defined_names.size(); i++)
		std::cout << defined_names[i] << "   ";
}
	
Value * DefineExpr::generateCode() {
	Value * ret = NULL;
	if(defined_names.size() > 0) {
		Type * type_alloc = NULL;
		switch(def_type) {
		case VAR_INT:
			type_alloc = Type::getInt32Ty(GlobalContext);
			break;
		case VAR_LONG:
			type_alloc = Type::getInt64Ty(GlobalContext);
			break;
		case VAR_FLOAT:
			type_alloc = Type::getFP128Ty(GlobalContext);
			break;
		case VAR_DOUBLE:
			type_alloc = Type::getDoubleTy(GlobalContext);;
			break;
		case VAR_UNDEFINED:
			type_alloc = NULL;
			break;
		}
		
		if(type_alloc != NULL)
			for(int i = 0; i < defined_names.size(); i++) {
				std::string var_name = defined_names[i];
				AllocaInst * llvm_alloca_inst = new AllocaInst(type_alloc, var_name.c_str());
				NamedValues[var_name] = llvm_alloca_inst;
			}
	}
	return ret;
}