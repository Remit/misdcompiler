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

Value * WhileLoop::generateCode() {
	Value * ret = NULL;
	
	Function * func = Builder.GetInsertBlock()->getParent();
	BasicBlock * headerBB = BasicBlock::Create(GlobalContext, "condition", func);
	Builder.SetInsertPoint(headerBB);
	BasicBlock * loopBB = BasicBlock::Create(GlobalContext, "loop", func);
	BasicBlock * afterBB = BasicBlock::Create(GlobalContext, "afterloop", func);
	Value * cond = NULL;
	if(Condition != NULL) {
		cond = Condition->generateCode();
		if(cond != NULL) {
			Builder.CreateCondBr(cond, loopBB, afterBB);
			Builder.SetInsertPoint(loopBB);
			if(Body != NULL) {
				Body->generateCode();
			}
			Builder.CreateBr(headerBB);
			BasicBlock * loopEndBB = Builder.GetInsertBlock();
			Builder.SetInsertPoint(afterBB);
		}
	}

	ret = Constant::getNullValue(Type::getDoubleTy(GlobalContext));
	return ret;
}