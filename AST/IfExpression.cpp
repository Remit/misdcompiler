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
		Builder.CreateFCmpONE(cond,ConstantFP::get(GlobalContext, APFloat(0.0)),"ifcond");
		Function * func = Builder.GetInsertBlock()->getParent();
		BasicBlock * thenBB = BasicBlock::Create(GlobalContext, "then", func);
		BasicBlock * elseBB = BasicBlock::Create(GlobalContext, "else");
		BasicBlock * mergeBB = BasicBlock::Create(GlobalContext, "ifcont");
		Builder.CreateCondBr(cond, thenBB, elseBB);
		Builder.SetInsertPoint(thenBB);
		
		Value * then_val = NULL;
		if(ThenExpression != NULL) {
			then_val = ThenExpression->generateCode();
			if(then_val != NULL) {
				Builder.CreateBr(mergeBB);
				thenBB = Builder.GetInsertBlock();
			}
		}
		
		func->getBasicBlockList().push_back(elseBB);
		Builder.SetInsertPoint(elseBB);
		Value * else_val = NULL;
		if(ElseExpression != NULL) {
			else_val = ElseExpression->generateCode();
			if (else_val != NULL) {
				Builder.CreateBr(mergeBB);
				elseBB = Builder.GetInsertBlock();
			}
		}
		
		func->getBasicBlockList().push_back(mergeBB);
		Builder.SetInsertPoint(mergeBB);
		PHINode * PN = Builder.CreatePHI(Type::getDoubleTy(GlobalContext), 2, "iftmp");
		if(then_val != NULL)
			PN->addIncoming(then_val, thenBB);
			
		if(else_val != NULL)
			PN->addIncoming(else_val, elseBB);
		ret = PN;
	}
	return ret;
}