#ifndef IFEXPRESSION_H
#define IFEXPRESSION_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

class IfExpression : public Base_AST
{
public:
	IfExpression();
	IfExpression(Base_AST* a_cond, Base_AST* a_then_expr, Base_AST* a_else_expr) : Condition(a_cond), ThenExpression(a_then_expr), ElseExpression(a_else_expr) { lbl = AST_IFEXPRESSION; }
	~IfExpression();
	
	void setCondition(Base_AST* a_cond);
	void setThenExpression(Base_AST* a_then_expr);
	void setElseExpression(Base_AST* a_else_expr);
	
	Base_AST* getCondition();
	Base_AST* getThenExpression();
	Base_AST* getElseExpression();
	
	Base_AST * copyAST();
	
	void print();
	
	virtual Value *generateCode();

private:
	Base_AST* Condition;
	Base_AST* ThenExpression;
	Base_AST* ElseExpression;

};

#endif // IFEXPRESSION_H
