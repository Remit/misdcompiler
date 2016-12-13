#include "../include/IfExpression.h"

IfExpression::IfExpression()
{
	Condition = NULL;
	ThenExpression = NULL;
	ElseExpression = NULL;
	lbl = AST_IFEXPRESSION;
}

IfExpression::~IfExpression()
{
}

void IfExpression::setCondition(Base_AST* a_cond) {
	Condition = a_cond;
}

void IfExpression::setThenExpression(Base_AST* a_then_expr) {
	ThenExpression = a_then_expr;
}

void IfExpression::setElseExpression(Base_AST* a_else_expr) {
	ElseExpression = a_else_expr;
}

Base_AST* IfExpression::getCondition() {
	return Condition;
}

Base_AST* IfExpression::getThenExpression() {
	return ThenExpression;
}

Base_AST* IfExpression::getElseExpression() {
	return ElseExpression;
}

void IfExpression::print() {
	std::cout << "\n - If-expression - ";
	if(Condition != NULL) {
		std::cout << "\n - Condition: ";
		Condition->print();
	}
	if(ThenExpression != NULL) {
		std::cout << "\n - Then: ";
		ThenExpression->print();
	}
	if(ElseExpression != NULL) {
		std::cout << "\n - Else: ";
		ElseExpression->print();
	}
}

Base_AST * IfExpression::copyAST() {
	IfExpression * cpy = new IfExpression();
	if(Condition != NULL)
		cpy->setCondition(Condition->copyAST());
	if(ThenExpression != NULL)
		cpy->setThenExpression(ThenExpression->copyAST());
	if(ElseExpression != NULL)
		cpy->setElseExpression(ElseExpression->copyAST());
	
	return cpy;
}

Value * IfExpression::generateCode() {
	Value * ret = NULL;
	return ret;
}