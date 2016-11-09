#include "../include/WhileLoop.h"

WhileLoop::WhileLoop()
{
	Condition = NULL;
	Body = NULL;
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
