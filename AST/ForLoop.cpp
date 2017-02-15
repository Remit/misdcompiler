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

void ForLoop::print(std::ostream * print_stream) {
	*print_stream << "\n - For-Loop - ";
	*print_stream << "\n - Start of loop: ";
	if(Start != NULL)
		Start->print(print_stream);
		
	*print_stream << "\n - Ending condition of loop: ";
	if(End != NULL)
		End->print(print_stream);
		
	*print_stream << "\n - Step of loop: ";
	if(Step != NULL)
		Step->print(print_stream);
	
	*print_stream << "\n - Body of loop: ";
	if(Body != NULL)
		Body->print(print_stream);
}

Value * ForLoop::generateCode() {
	Value * ret = NULL;
	
	if(Start != NULL) {
		StoreInst * start_val_raw = NULL;
		start_val_raw = (StoreInst *)Start->generateCode(); // Initializing the loop variable.
		Value * start_val = start_val_raw->getValueOperand();
		if(start_val != NULL) {
			Function * func = Builder.GetInsertBlock()->getParent();
			BasicBlock * headerBB = Builder.GetInsertBlock();
			BasicBlock * loopBB = BasicBlock::Create(GlobalContext, "loop", func);
			
			Builder.CreateBr(loopBB);
			Builder.SetInsertPoint(loopBB);
			
			PHINode * counter = Builder.CreatePHI(start_val->getType(), 2, counter_name.c_str());
			counter->addIncoming(start_val, headerBB);
			
			if (Body != NULL) {
				Body->generateCode();
				Value * next_var = NULL;
				Value * step_val = NULL;
				if(Step != NULL) {
					StoreInst * step_val_raw = NULL;
					step_val_raw = (StoreInst *)Step->generateCode();
					next_var = step_val_raw->getValueOperand();
				} else {
					step_val = ConstantFP::get(GlobalContext, APFloat(1.0));
					next_var = Builder.CreateFAdd(counter, step_val, "nextvar");
				}
				
				if(next_var != NULL) {
					Value * endCond = NULL;
					if(End != NULL) {
						endCond = End->generateCode();
						if(endCond != NULL) {
							BasicBlock * loopEndBB = Builder.GetInsertBlock();
							BasicBlock * afterBB = BasicBlock::Create(GlobalContext, "afterloop", func);
							Builder.CreateCondBr(endCond, loopBB, afterBB);
							Builder.SetInsertPoint(afterBB);
							counter->addIncoming(next_var, loopEndBB);
						}
					}
				}
			}
		}
	}

	ret = Constant::getNullValue(Type::getDoubleTy(GlobalContext));

	return ret;
}

std::string ForLoop::generateStructCode() { // The same as for the While-loop, change them at the same time
	std::string ret = "";
	
	if(End != NULL) { // Condition check instruction generation (jwt)
		strcpy(SP_IR[mem_point].label, std::to_string(label_i).c_str()); // Assigning a unique label for condition;
		std::string lbl_cond = std::to_string(label_i);
		label_i++;
		SP_IR[mem_point].tag[0] = false; // Tag is false - we are waiting for check results from CPU
		SP_IR[mem_point].tag[1] = true; // Not in use
		SP_IR[mem_point].tag[2] = true; // Not in use
		SP_IR[mem_point].op[0] = 0; // The value is received from CPU
		SP_IR[mem_point].op[1] = 0; // Not in use
		SP_IR[mem_point].op[2] = 0; // Not in use
		SP_IR[mem_point].opcode = JWT; // Setting the opcode for conditional jump to ELSE-branch
		SP_IR[mem_point].q = false;

		int jwt_pos = mem_point;
		mem_point++;
		int loop_body_beg = mem_point; // Positions of instructions in SPU program representation
		
		if(Body != NULL) {
			Body->generateStructCode();
		
			strcpy(SP_IR[loop_body_beg].label, std::to_string(label_i).c_str()); // Creating a label for loop body
			label_i++;
			
			// Jump to loop begin
			strcpy(SP_IR[mem_point].label, std::to_string(label_i).c_str()); // Assigning a unique label for jump to condition;
			label_i++;
			SP_IR[mem_point].tag[0] = true; 
			SP_IR[mem_point].tag[1] = true; // Not in use
			SP_IR[mem_point].tag[2] = true; // Not in use
			SP_IR[mem_point].op[0] = 0; // The value is received from CPU
			SP_IR[mem_point].op[1] = 0; // Not in use
			SP_IR[mem_point].op[2] = 0; // Not in use
			SP_IR[mem_point].opcode = JNW; // Setting the opcode for conditional jump to ELSE-branch
			SP_IR[mem_point].q = false;
			SP_IR[mem_point].jmp_adr = jwt_pos;
			strcpy(SP_IR[mem_point].jmp_label,lbl_cond.c_str());
		
			mem_point++;
			
			// End of the loop
			SP_IR[mem_point].opcode = NOOP;
			strcpy(SP_IR[jwt_pos].jmp_label, std::to_string(label_i).c_str()); // Assigning a unique label for condition to jump to else-branch
			SP_IR[jwt_pos].jmp_adr = mem_point;
			strcpy(SP_IR[mem_point].label, std::to_string(label_i).c_str());// An empty-command for end label and position
			SP_IR[mem_point].tag[0] = true; // Unconditional branch
			SP_IR[mem_point].tag[1] = true; // Not in use
			SP_IR[mem_point].tag[2] = true; // Not in use
			SP_IR[mem_point].op[0] = 0; // The value is received from CPU
			SP_IR[mem_point].op[1] = 0; // Not in use
			SP_IR[mem_point].op[2] = 0; // Not in use
			SP_IR[mem_point].q = false;
				
			label_i++;
			mem_point++;
		}
	}
	
	return ret;
}