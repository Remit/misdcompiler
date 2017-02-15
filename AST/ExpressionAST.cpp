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

void ExpressionAST::print(std::ostream * print_stream) {
	*print_stream << "\n - Expression - ";
	
	if(LHS_E != NULL) {
		*print_stream << "\n - Left operand: ";
		LHS_E->print(print_stream);
	}
	if(RHS_E != NULL) {
		*print_stream << "\n - Right operand: ";
		RHS_E->print(print_stream);
	}
}

Value * ExpressionAST::generateCode() {
	Value * ret = NULL;
	Value * LHS_code = NULL;
	Value * RHS_code = NULL;
	
	if(LHS_E != NULL)
		LHS_code = LHS_E->generateCode();
	if(RHS_E != NULL)
		RHS_code = RHS_E->generateCode();
		
	ret = LHS_code;
	
	return ret;
}

std::string ExpressionAST::generateStructCode() {
	std::string ret = "";
	return ret;
}