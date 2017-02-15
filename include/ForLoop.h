#ifndef FORLOOP_H
#define FORLOOP_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class ForLoop : public Base_AST
{
public:
	ForLoop();
	ForLoop(Base_AST* a_start, Base_AST* a_end, Base_AST* a_step, Base_AST* a_body) : Start(a_start), End(a_end), Step(a_step), Body(a_body) { lbl = AST_FORLOOP; }
	~ForLoop();
	
	void setStart(Base_AST* a_start);
	void setEnd(Base_AST* a_end);
	void setStep(Base_AST* a_step);
	void setBody(Base_AST* a_body);
	void setCounterName(std::string a_counter_name);
	
	Base_AST* getStart();
	Base_AST* getEnd();
	Base_AST* getStep();
	Base_AST* getBody();
	std::string getCounterName();
	
	Base_AST * copyAST();
	
	void print(std::ostream * print_stream);
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();
	
private:
	Base_AST* Start;
	Base_AST* End;
	Base_AST* Step;
	Base_AST* Body;
	std::string counter_name;
};

#endif // FORLOOP_H
