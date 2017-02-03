#include "../include/ForLoop.h"

ForLoop::ForLoop()
{
	Start = NULL;
	End = NULL;
	Step = NULL;
	Body = NULL;
	counter_name = "";
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
	Body = a_body;
}

void ForLoop::setCounterName(std::string a_counter_name) {
	counter_name = a_counter_name;
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

std::string ForLoop::getCounterName() {
	return counter_name;
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

Value * ForLoop::generateCode() {
	Value * ret = NULL;
	Value * start_val = NULL;
	if(Start != NULL) {
		start_val = Start->generateCode();
		
		Function * func = Builder.GetInsertBlock()->getParent();
		BasicBlock * headerBB = Builder.GetInsertBlock();
		BasicBlock * loopBB = BasicBlock::Create(GlobalContext, "loop", func);
		
		Builder.CreateBr(loopBB);
		Builder.SetInsertPoint(loopBB);
		
		PHINode * counter = Builder.CreatePHI(Type::getDoubleTy(GlobalContext), 2, counter_name.c_str());
		counter->addIncoming(start_val, headerBB);
		
		Value * old_val = NamedValues[counter_name];
		NamedValues[counter_name] = counter;
		
		if (Body != NULL) {
			Value * step_val = NULL;
			if(Step != NULL) {
				step_val = Step->generateCode();
			} else {
				step_val = ConstantFP::get(GlobalContext, APFloat(1.0));
			}
			
			if(step_val != NULL) {
				Value * next_var = Builder.CreateFAdd(counter, step_val, "nextvar");
				Value * endCond = NULL;
				if(End != NULL) {
					endCond = End->generateCode();
					if(endCond != NULL) {
						endCond = Builder.CreateFCmpONE(endCond, ConstantFP::get(GlobalContext, APFloat(0.0)), "loopcond");
						BasicBlock * loopEndBB = Builder.GetInsertBlock();
						BasicBlock * afterBB = BasicBlock::Create(GlobalContext, "afterloop", func);
						Builder.CreateCondBr(endCond, loopBB, afterBB);
						Builder.SetInsertPoint(afterBB);
						counter->addIncoming(next_var, loopEndBB);
						
						if(old_val)
							NamedValues[counter_name] = old_val;
						else
							NamedValues.erase(counter_name);
					}
				}
			}
		}
	}

	ret = Constant::getNullValue(Type::getDoubleTy(GlobalContext));

	return ret;
}