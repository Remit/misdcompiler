#include "../include/LogicalExpression.h"

LogicalExpression::LogicalExpression()
{
	op = OP_LOGICAL_UNDEFINED;
	BinExpr_LHS = NULL;
	BinExpr_RHS = NULL;
}

LogicalExpression::~LogicalExpression()
{
}

void LogicalExpression::setOperation(cond_op_types a_op) {
	op = a_op;
}

void LogicalExpression::setLHS(Base_AST* LHS_AST) {
	BinExpr_LHS = LHS_AST;
}

void LogicalExpression::setRHS(Base_AST* RHS_AST) {
	BinExpr_RHS = RHS_AST;
}

cond_op_types LogicalExpression::getOperation() {
	return op;
}

Base_AST* LogicalExpression::getLHS() {
	return BinExpr_LHS;
}

Base_AST* LogicalExpression::getRHS() {
	return BinExpr_RHS;
}