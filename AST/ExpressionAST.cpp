#include "../include/ExpressionAST.h"

ExpressionAST::ExpressionAST()
{
	LHS_E = NULL;
	RHS_E = NULL;
	lbl = AST_EXPRESSION;
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

Base_AST * ExpressionAST::copyAST() {
	ExpressionAST * cpy = new ExpressionAST();
	if(LHS_E != NULL)
		cpy->setLHS_E(LHS_E->copyAST());
	if(RHS_E != NULL)
		cpy->setRHS_E(RHS_E->copyAST());
	
	return cpy;
}

void ExpressionAST::print() {
	std::cout << "\n - Expression - ";
	
	if(LHS_E != NULL) {
		std::cout << "\n - Left operand: ";
		LHS_E->print();
	}
	if(RHS_E != NULL) {
		std::cout << "\n - Right operand: ";
		RHS_E->print();
	}
}

Value * ExpressionAST::generateCode() {
	Value * ret = NULL;
	return ret;
}