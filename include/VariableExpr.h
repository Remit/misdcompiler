#ifndef VARIABLEEXPR_H
#define VARIABLEEXPR_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

class VariableExpr : public Base_AST
{
public:
	VariableExpr();
	VariableExpr(std::string a_name, variable_type a_var_type, bool a_isDeclaration) : name(a_name), var_type(a_var_type), isDeclaration(a_isDeclaration) {}
	~VariableExpr();
	
	void setName(std::string a_name);
	void setVarType(variable_type a_var_type);
	void setIsDeclaration(bool a_isDeclaration);
	
	std::string getName();
	variable_type getVarType();
	bool getIsDeclaration();

private:
	std::string name;
	variable_type var_type;
	bool isDeclaration;

};

#endif // VARIABLEEXPR_H
