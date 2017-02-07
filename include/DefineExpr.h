#ifndef DEFINEEXPR_H
#define DEFINEEXPR_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class DefineExpr : public Base_AST
{
public:
	DefineExpr();
	DefineExpr(std::vector<std::string> * a_defined_names, variable_type a_def_type) : def_type(a_def_type) { if(a_defined_names != NULL) { for(int i = 0; i < a_defined_names->size(); i++) defined_names.push_back((*a_defined_names)[i]); } }
	~DefineExpr();
	
	void setTypeOfVars(variable_type a_def_type);
	variable_type getTypeOfVars();
	void setListOfNames(std::vector<std::string> * a_defined_names);
	std::vector<std::string> * getListOfNames();
	
	Base_AST * copyAST();
	
	void print();
	
	virtual Value *generateCode();

private:
	std::vector<std::string> defined_names;
	variable_type def_type;

};

#endif // DEFINEEXPR_H
