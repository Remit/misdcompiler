#include "../include/VariableExpr.h"

VariableExpr::VariableExpr()
{
	name = "";
	var_type = VAR_UNDEFINED;
	isDeclaration = false;
}

VariableExpr::VariableExpr(std::string a_name, variable_type a_var_type, bool a_isDeclaration) {
	name = a_name;
	var_type = a_var_type;
	isDeclaration = a_isDeclaration;
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