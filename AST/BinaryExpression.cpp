#include "../include/BinaryExpression.h"

BinaryExpression::BinaryExpression()
{
	op = OP_BINARY_UNDEFINED;
	BinExpr_LHS = NULL;
	BinExpr_RHS = NULL;
}

BinaryExpression::~BinaryExpression()
{
}

void BinaryExpression::setOperation(bin_op_types a_op) {
	op = a_op;
}

void BinaryExpression::setLHS(Base_AST* LHS_AST) {
	BinExpr_LHS = LHS_AST;
}

void BinaryExpression::setRHS(Base_AST* RHS_AST) {
	BinExpr_RHS = RHS_AST;
}

bin_op_types BinaryExpression::getOperation() {
	return op;
}

Base_AST* BinaryExpression::getLHS() {
	return BinExpr_LHS;
}

Base_AST* BinaryExpression::getRHS() {
	return BinExpr_RHS;
}