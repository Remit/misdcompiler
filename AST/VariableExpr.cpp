#include "../include/VariableExpr.h"

VariableExpr::VariableExpr()
{
	name = "";
	var_type = VAR_UNDEFINED;
	isDeclaration = false;
	lbl = AST_VARIABLEEXPR;
}

VariableExpr::VariableExpr(std::string a_name, variable_type a_var_type, bool a_isDeclaration) {
	name = a_name;
	var_type = a_var_type;
	isDeclaration = a_isDeclaration;
	lbl = AST_VARIABLEEXPR;
}

VariableExpr::~VariableExpr()
{
}

void VariableExpr::setName(std::string a_name) {
	name = a_name;
}

void VariableExpr::setVarType(variable_type a_var_type) {
	var_type = a_var_type;
}

void VariableExpr::setIsDeclaration(bool a_isDeclaration) {
	isDeclaration = a_isDeclaration;
}

std::string VariableExpr::getName() {
	return name;
}

variable_type VariableExpr::getVarType() {
	return var_type;
}


bool VariableExpr::getIsDeclaration() {
	return isDeclaration;
}

Base_AST * VariableExpr::copyAST() {
	VariableExpr * cpy = new VariableExpr(name,var_type,isDeclaration);
	return cpy;
}

void VariableExpr::print(std::ostream * print_stream) {
	std::string v_type;
	switch(var_type) {
    case VAR_INT:
		v_type = "int";
		break;
    case VAR_LONG:
		v_type = "long";
		break;
    case VAR_FLOAT:
		v_type = "float";
		break;
    case VAR_DOUBLE:
		v_type = "double";
		break;
    case VAR_BOOL:
		v_type = "bool";
		break;
    case VAR_UNDEFINED:
		v_type = "?";
		break;
	}
	* print_stream << "\n - Variable " << name << " of type " << v_type;
	if(isDeclaration)
		* print_stream << " (declaration) ";
}

Value * VariableExpr::generateCode() {
	Value * ret = NULL;
	LoadInst * ld_inst;
	
	ret = NamedValues[name];
	if (ret == NULL) {
		std::cout << "Unknown variable name:\n" << name << std::endl;
	} else {
		ret = Builder.CreateLoad(ret, name.c_str());
		//ret = ld_inst->getPointerOperand();
	}

	return ret;
}

std::string VariableExpr::generateStructCode() {
	std::string ret = "";
	return ret;
}