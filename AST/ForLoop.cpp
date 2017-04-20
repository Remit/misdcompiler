#include "../include/ForLoop.h"

ForLoop::ForLoop()
{
	Start = NULL;
	End = NULL;
	Step = NULL;
	Body = NULL;
	counter_name = "";
	al_tag_name = "";
	lbl = AST_FORLOOP;
	parent_op_node = -1;
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

void ForLoop::setALtagName(std::string a_al_tag_name) {
	al_tag_name = a_al_tag_name;
}

void ForLoop::setParentOpNode(int a_parent_op_node) {
	parent_op_node = a_parent_op_node;
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

std::string ForLoop::getALTagName() {
	return al_tag_name;
}

int ForLoop::getParentOpNode() {
	return parent_op_node;
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
	cpy->setParentOpNode(parent_op_node);

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
	StoreInst * llvm_store_inst;
	Value * address_for_spu = NULL;
	
	AllocaInst * llvm_alloca_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), nullptr, al_tag_name.c_str());
	NamedValues[al_tag_name] = llvm_alloca_inst;
	ret = (Value *)NamedValues[al_tag_name];
	
	if(Start != NULL) {
		StoreInst * start_val_raw = NULL;
		start_val_raw = (StoreInst *)Start->generateCode(); // Initializing the loop variable.
		Value * start_val = start_val_raw->getValueOperand();
		if(start_val != NULL) {
			Function * func = Builder.GetInsertBlock()->getParent();
			BasicBlock * headerBB = BasicBlock::Create(GlobalContext, "condition", func);
			Builder.CreateBr(headerBB);
			Builder.SetInsertPoint(headerBB);
			
			BasicBlock * loopBB = BasicBlock::Create(GlobalContext, "loop");
			BasicBlock * afterBB = BasicBlock::Create(GlobalContext, "afterloop");
			//BasicBlock * loopBB = BasicBlock::Create(GlobalContext, "loop", func);
			if(End != NULL) {
				Value * endCond = End->generateCode();
				// TODO: Additional LLVM if-branch to store the necessary jump address for SPU after receiving the result of condition evaluation
				StoreInst * llvm_store_inst = Builder.CreateStore(endCond, ret);//TODO: Result of condition which will be transmitted -- we need address -- replace cond
				if(endCond != NULL) {
					Builder.CreateCondBr(endCond, loopBB, afterBB);
					func->getBasicBlockList().push_back(loopBB);
					Builder.SetInsertPoint(loopBB);
					// Storing address to send to SPU in case condition is true
					ret = (Value *)NamedValues[al_tag_name];
					address_for_spu = ConstantInt::get(Type::getInt32Ty(GlobalContext), true_address[parent_op_node]);
					llvm_store_inst = Builder.CreateStore(address_for_spu, ret); 
					
					if (Body != NULL) {
						Body->generateCode();
					}
					
					Value * next_var = NULL;
					Value * step_val = NULL;
					if(Step != NULL) {
						StoreInst * step_val_raw = NULL;
						step_val_raw = (StoreInst *)Step->generateCode();
						next_var = step_val_raw->getValueOperand();
					} else {
						if(start_val_raw->getType()->isFPOrFPVectorTy() || start_val_raw->getType()->isDoubleTy()) {
							step_val = ConstantFP::get(GlobalContext, APFloat(1.0));
							next_var = Builder.CreateFAdd(start_val_raw, step_val, "nextvar");
						} else {
							step_val = ConstantInt::get(Type::getInt16Ty(GlobalContext), 1);
							next_var = Builder.CreateAdd(start_val_raw, step_val, "nextvar");
						}
					}
					
					Builder.CreateBr(headerBB);
					func->getBasicBlockList().push_back(afterBB); // Inserting basic block for instructions after merging of branches after basic block for ELSE-branch
					Builder.SetInsertPoint(afterBB);
					
					// Storing address to send to SPU in case condition is false
					address_for_spu = ConstantInt::get(Type::getInt32Ty(GlobalContext), false_address[parent_op_node]);
					llvm_store_inst = Builder.CreateStore(address_for_spu, ret);
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
		SP_IR[mem_point].opcode = JT; // Setting the opcode for conditional jump end of the loop
		SP_IR[mem_point].q = false;

		int jwt_pos = mem_point;
		if(mem_point != (MEM_LENGTH - 2)) {
			mem_point++;
		} else {
			printf("Error: not enough memory for SPU code (MEM_LENGTH too small).");
			return ret;
		}
		int loop_body_beg = mem_point; // Positions of instructions in SPU program representation
		true_address[parent_op_node] = loop_body_beg;
		
		if(Body != NULL) {
			Body->generateStructCode();
		
			strcpy(SP_IR[loop_body_beg].label, std::to_string(label_i).c_str()); // Creating a label for loop body
			label_i++;
			
			// Jump to loop begin
			strcpy(SP_IR[mem_point].label, std::to_string(label_i).c_str()); // Assigning a unique label for jump to condition;
			label_i++;
			SP_IR[mem_point].tag[0] = true; // Tag is true - unconditional jump to the beginning
			SP_IR[mem_point].tag[1] = true; // Not in use
			SP_IR[mem_point].tag[2] = true; // Not in use
			SP_IR[mem_point].op[0] = 1; // Unconditional branch
			SP_IR[mem_point].op[1] = 0; // Not in use
			SP_IR[mem_point].op[2] = 0; // Not in use
			SP_IR[mem_point].opcode = JT; // Jump to condition after the loop body is processed
			SP_IR[mem_point].q = false;
			SP_IR[mem_point].jmp_adr = jwt_pos;
			strcpy(SP_IR[mem_point].jmp_label,lbl_cond.c_str());
		
			if(mem_point != (MEM_LENGTH - 2)) {
			mem_point++;
			} else {
				printf("Error: not enough memory for SPU code (MEM_LENGTH too small).");
				return ret;
			}
			false_address[parent_op_node] = mem_point;
			
			// End of the loop
			//strcpy(SP_IR[jwt_pos].jmp_label, std::to_string(label_i).c_str()); // Assigning a unique label for condition to jump to else-branch
			SP_IR[jwt_pos].jmp_adr = -1;//mem_point;
			strcpy(SP_IR[mem_point].label, std::to_string(label_i).c_str());
				
			label_i++;
		}
	}
	
	return ret;
}