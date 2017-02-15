#ifndef STRUCTUREEXPR_H
#define STRUCTUREEXPR_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class StructureExpr : public Base_AST
{
public:
	StructureExpr();
	StructureExpr(std::string a_name);
	virtual ~StructureExpr();
	
	void setName(std::string a_name);
	
	std::string getName();
	
	Base_AST * copyAST();
	
	void print(std::ostream * print_stream);
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();

private:
	std::string name;

};

#endif // STRUCTUREEXPR_H
