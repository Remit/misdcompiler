#include "../include/ExpressionAST.h"

ExpressionAST::ExpressionAST()
{
	LHS_E = NULL;
	RHS_E = NULL;
}

ExpressionAST::~ExpressionAST()
{
}

Base_AST* ExpressionAST::getLHS_E() {
	return LHS_E;
}

Base_AST* ExpressionAST::getRHS_E() {
	return RHS_E;
}

void ExpressionAST::setLHS_E(Base_AST* a_LHS_E) {
	LHS_E = a_LHS_E;
}

void ExpressionAST::setRHS_E(Base_AST* a_RHS_E) {
	RHS_E = a_RHS_E;
}
