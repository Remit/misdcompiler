#ifndef IFEXPRESSION_H
#define IFEXPRESSION_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class IfExpression : public Base_AST
{
public:
	IfExpression();
	IfExpression(Base_AST* a_cond, Base_AST* a_then_expr, Base_AST* a_else_expr, std::string a_al_tag_name = "", int a_parent_op_node = -1) : Condition(a_cond), ThenExpression(a_then_expr), ElseExpression(a_else_expr), al_tag_name(a_al_tag_name), parent_op_node(a_parent_op_node) { lbl = AST_IFEXPRESSION; }
	~IfExpression();
	
	void setCondition(Base_AST* a_cond);
	void setThenExpression(Base_AST* a_then_expr);
	void setElseExpression(Base_AST* a_else_expr);
	void setALtagName(std::string a_al_tag_name);
	void setParentOpNode(int a_parent_op_node);
	
	Base_AST* getCondition();
	Base_AST* getThenExpression();
	Base_AST* getElseExpression();
	std::string getALTagName();
	int getParentOpNode();
	
	Base_AST * copyAST();
	
	void print(std::ostream * print_stream);
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();

private:
	Base_AST* Condition;
	Base_AST* ThenExpression;
	Base_AST* ElseExpression;
	std::string al_tag_name;
	int parent_op_node;

};

#endif // IFEXPRESSION_H
