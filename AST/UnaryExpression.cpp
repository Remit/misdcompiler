#include "../include/UnaryExpression.h"

UnaryExpression::UnaryExpression()
{
    op = OP_UNARY_UNDEFINED;
	UnaryExpr_RHS = NULL;
}

UnaryExpression::~UnaryExpression()
{
}

void UnaryExpression::setOperation(unary_op_types a_op) {
	op = a_op;
}

void UnaryExpression::setRHS(Base_AST* RHS_AST) {
	UnaryExpr_RHS = RHS_AST;
}

unary_op_types UnaryExpression::getOperation() {
	return op;
}

Base_AST* UnaryExpression::getRHS() {
	return UnaryExpr_RHS;
}
