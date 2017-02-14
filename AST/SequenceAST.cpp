#include "../include/SequenceAST.h"

SequenceAST::SequenceAST()
{
	LHS_E = NULL;
	RHS_E = NULL;
	lbl = AST_SEQUENCEAST;
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

void SequenceAST::print() {
	std::cout << "\n - Sequence - ";
	if(LHS_E != NULL) {
		std::cout << "\n - Left subtree: ";
		LHS_E->print();
	}
	if(RHS_E != NULL) {
		std::cout << "\n - Right subtree: ";
		RHS_E->print();
	}
}

Base_AST * SequenceAST::copyAST() {
	SequenceAST * cpy = new SequenceAST();
	if(LHS_E != NULL)
		cpy->setLHS_E(LHS_E->copyAST());
	if(RHS_E != NULL)
		cpy->setRHS_E(RHS_E->copyAST());
		
	return cpy;
}

Value * SequenceAST::generateCode() {
	Value * ret = NULL;
	Value * LHS_code = NULL;
	Value * RHS_code = NULL;
	
	if(LHS_E != NULL)
		LHS_code = LHS_E->generateCode();
	if(RHS_E != NULL) {
		RHS_code = RHS_E->generateCode();
		SequenceAST * seq_next = (SequenceAST *)RHS_E;
		if(seq_next->getRHS_E() == NULL)
			ret = LHS_code;
		else
			ret = RHS_code;
	}
	
	return ret;
}

std::string SequenceAST::generateStructCode() {
	std::string ret = "";
	
	if(LHS_E != NULL)
		LHS_E->generateStructCode();
	if(RHS_E != NULL)
		RHS_E->generateStructCode();
	
	return ret;
}