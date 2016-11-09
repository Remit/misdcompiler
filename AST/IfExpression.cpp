#include "../include/IfExpression.h"

IfExpression::IfExpression()
{
	Condition = NULL;
	ThenExpression = NULL;
	ElseExpression = NULL;
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
