#include "../include/ForLoop.h"

ForLoop::ForLoop()
{
	Start = NULL;
	End = NULL;
	Step = NULL;
	Body = NULL;
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
