#ifndef WHILELOOP_H
#define WHILELOOP_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class WhileLoop : public Base_AST
{
public:
	WhileLoop();
	WhileLoop(Base_AST* a_cond, Base_AST* a_body, std::string a_al_tag_name = "", int a_parent_op_node = -1) : Condition(a_cond), Body(a_body), al_tag_name(a_al_tag_name), parent_op_node(a_parent_op_node) { lbl = AST_WHILELOOP; }
	~WhileLoop();
	
	void setCondition(Base_AST* a_cond);
	void setBody(Base_AST* a_body);
	void setALtagName(std::string a_al_tag_name);
	void setParentOpNode(int a_parent_op_node);
	
	Base_AST* getCondition();
	Base_AST* getBody();
	std::string getALTagName();
	int getParentOpNode();
	
	Base_AST * copyAST();
	
	void print(std::ostream * print_stream);
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();

private:
	Base_AST* Condition;
	Base_AST* Body;
	std::string al_tag_name;
	int parent_op_node;
};

#endif // WHILELOOP_H
