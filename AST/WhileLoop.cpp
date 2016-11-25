#include "../include/WhileLoop.h"

WhileLoop::WhileLoop()
{
	Condition = NULL;
	Body = NULL;
	lbl = AST_WHILELOOP;
}

WhileLoop::~WhileLoop()
{
}

void WhileLoop::setCondition(Base_AST* a_cond) {
	Condition = a_cond;
}

void WhileLoop::setBody(Base_AST* a_body) {
	Body = a_body;
}

Base_AST* WhileLoop::getCondition() {
	return Condition;
}

Base_AST* WhileLoop::getBody() {
	return Body;
}

Base_AST * WhileLoop::copyAST() {
	WhileLoop * cpy = new WhileLoop();
	if(Body != NULL)
		cpy->setBody(Body->copyAST());
	if(Condition != NULL)
		cpy->setCondition(Condition->copyAST());
		
	return cpy;
}

void WhileLoop::print() {
	std::cout << "\n - While-Loop - ";
	if(Condition != NULL) {
		std::cout << "\n - Condition: ";
		Condition->print();
	}
	if(Body != NULL) {
		std::cout << "\n - Body: ";
		Body->print();
	}
}