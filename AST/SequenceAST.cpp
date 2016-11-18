#include "../include/SequenceAST.h"

SequenceAST::SequenceAST()
{
	LHS_E = NULL;
	RHS_E = NULL;
}

SequenceAST::~SequenceAST()
{
}

Base_AST* SequenceAST::getLHS_E() {
	return LHS_E;
}

Base_AST* SequenceAST::getRHS_E() {
	return RHS_E;
}

void SequenceAST::setLHS_E(Base_AST* a_LHS_E) {
	LHS_E = a_LHS_E;
}

void SequenceAST::setRHS_E(Base_AST* a_RHS_E) {
	RHS_E = a_RHS_E;
}
