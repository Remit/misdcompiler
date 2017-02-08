#include "../include/IfExpression.h"

IfExpression::IfExpression()
{
	Condition = NULL;
	ThenExpression = NULL;
	ElseExpression = NULL;
	lbl = AST_IFEXPRESSION;
}

IfExpression::~IfExpression()
{
}

void IfExpression::setCondition(Base_AST* a_cond) {
	Condition = a_cond;
}

void IfExpression::setThenExpression(Base_AST* a_then_expr) {
	ThenExpression = a_then_expr;
}

void IfExpression::setElseExpression(Base_AST* a_else_expr) {
	ElseExpression = a_else_expr;
}

Base_AST* IfExpression::getCondition() {
	return Condition;
}

Base_AST* IfExpression::getThenExpression() {
	return ThenExpression;
}

Base_AST* IfExpression::getElseExpression() {
	return ElseExpression;
}

void IfExpression::print() {
	std::cout << "\n - If-expression - ";
	if(Condition != NULL) {
		std::cout << "\n - Condition: ";
		Condition->print();
	}
	if(ThenExpression != NULL) {
		std::cout << "\n - Then: ";
		ThenExpression->print();
	}
	if(ElseExpression != NULL) {
		std::cout << "\n - Else: ";
		ElseExpression->print();
	}
}

Base_AST * IfExpression::copyAST() {
	IfExpression * cpy = new IfExpression();
	if(Condition != NULL)
		cpy->setCondition(Condition->copyAST());
	if(ThenExpression != NULL)
		cpy->setThenExpression(ThenExpression->copyAST());
	if(ElseExpression != NULL)
		cpy->setElseExpression(ElseExpression->copyAST());
	
	return cpy;
}

Value * IfExpression::generateCode() {
	Value * ret = NULL;
	Value * cond = NULL;
	
	if(Condition != NULL)
		cond = Condition->generateCode();
	if(cond != NULL) {
		Function * func = Builder.GetInsertBlock()->getParent();
		BasicBlock * thenBB = BasicBlock::Create(GlobalContext, "then", func);
		BasicBlock * elseBB = BasicBlock::Create(GlobalContext, "else");
		BasicBlock * mergeBB = BasicBlock::Create(GlobalContext, "ifcont");
		Builder.CreateCondBr(cond, thenBB, elseBB); // Creating a conditional branch at the current point in the IR of a program
		Builder.SetInsertPoint(thenBB); // Inserting basic block for THEN-branch immediately after conditional branching
		
		Value * then_val = NULL;
		if(ThenExpression != NULL) {
			then_val = ThenExpression->generateCode();
			Builder.CreateBr(mergeBB); // Creating the unconditional branch to merging point of branches (to "ifcont")
			thenBB = Builder.GetInsertBlock();
		}
		
		// Else part of branches is generated independently of the existence of ELSE-branch in the code
		func->getBasicBlockList().push_back(elseBB); // Inserting basic block for ELSE-branch after basic block for THEN-branch
		Builder.SetInsertPoint(elseBB); // Current insert point is at the end of the ELSE-branch basic block
		Value * else_val = NULL;
		if(ElseExpression != NULL) {
			else_val = ElseExpression->generateCode();
			Builder.CreateBr(mergeBB); // Creating the unconditional branch to merging point of branches (to "ifcont")
			elseBB = Builder.GetInsertBlock();
		}
		
		func->getBasicBlockList().push_back(mergeBB); // Inserting basic block for instructions after merging of branches after basic block for ELSE-branch
		Builder.SetInsertPoint(mergeBB); // Current insert point is at the end of the basic block with instructions after merging point
		ret = cond;
		
		// Insert here PhiNode functionality if it becomes necessary.
	}
	
	return ret;
}