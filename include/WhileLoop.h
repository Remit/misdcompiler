#ifndef WHILELOOP_H
#define WHILELOOP_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

class WhileLoop : public Base_AST
{
public:
	WhileLoop();
	WhileLoop(Base_AST* a_cond, Base_AST* a_body) : Condition(a_cond), Body(a_body) {}
	~WhileLoop();
	
	void setCondition(Base_AST* a_cond);
	void setBody(Base_AST* a_body);
	
	Base_AST* getCondition();
	Base_AST* getBody();

private:
	Base_AST* Condition;
	Base_AST* Body;

};

#endif // WHILELOOP_H