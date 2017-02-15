#ifndef EXPRESSIONAST_H
#define EXPRESSIONAST_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class ExpressionAST : public Base_AST
{
public:
	ExpressionAST();
	ExpressionAST(Base_AST* a_LHS_E, Base_AST* a_RHS_E) : LHS_E(a_LHS_E), RHS_E(a_RHS_E) { lbl = AST_EXPRESSION; }
	~ExpressionAST();
	
	Base_AST* getLHS_E();
	Base_AST* getRHS_E();
	
	void setLHS_E(Base_AST* a_LHS_E);
	void setRHS_E(Base_AST* a_RHS_E);
	
	Base_AST * copyAST();
	
	void print(std::ostream * print_stream);
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();

private:
	Base_AST* LHS_E;
	Base_AST* RHS_E;

};

#endif // EXPRESSIONAST_H
