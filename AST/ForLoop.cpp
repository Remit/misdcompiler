#include "../include/ForLoop.h"

ForLoop::ForLoop()
{
	Start = NULL;
	End = NULL;
	Step = NULL;
	Body = NULL;
	lbl = AST_FORLOOP;
}

ForLoop::~ForLoop()
{
}

void ForLoop::setStart(Base_AST* a_start) {
	Start = a_start;
}

void ForLoop::setEnd(Base_AST* a_end) {
	End = a_end;
}

void ForLoop::setStep(Base_AST* a_step) {
	Step = a_step;
}

void ForLoop::setBody(Base_AST* a_body) {
	Body  =a_body;
}

Base_AST* ForLoop::getStart() {
	return Start;
}

Base_AST* ForLoop::getEnd() {
	return End;
}

Base_AST* ForLoop::getStep() {
	return Step;
}

Base_AST* ForLoop::getBody() {
	return Body;
}

Base_AST * ForLoop::copyAST() {
	ForLoop * cpy = new ForLoop();
	if(Body != NULL) {
		cpy->setBody(Body->copyAST());
	}
	if(End != NULL) {
		cpy->setEnd(End->copyAST());
	}
	if(Step != NULL) {
		cpy->setStep(Step->copyAST());
	}
	if(Start != NULL) {
		cpy->setStart(Start->copyAST());
	}

	return cpy;
}

void ForLoop::print() {
	std::cout << "\n - For-Loop - ";
	std::cout << "\n - Start of loop: ";
	if(Start != NULL)
		Start->print();
		
	std::cout << "\n - Ending condition of loop: ";
	if(End != NULL)
		End->print();
		
	std::cout << "\n - Step of loop: ";
	if(Step != NULL)
		Step->print();
	
	std::cout << "\n - Body of loop: ";
	if(Body != NULL)
		Body->print();
}
