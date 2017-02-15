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

void WhileLoop::print(std::ostream * print_stream) {
	* print_stream << "\n - While-Loop - ";
	if(Condition != NULL) {
		* print_stream << "\n - Condition: ";
		Condition->print(print_stream);
	}
	if(Body != NULL) {
		* print_stream << "\n - Body: ";
		Body->print(print_stream);
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

std::string WhileLoop::generateStructCode() {
	std::string ret = "";
	
	if(Condition != NULL) { // Condition check instruction generation (jwt)
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