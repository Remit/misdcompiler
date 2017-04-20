#include "../include/WhileLoop.h"

WhileLoop::WhileLoop()
{
	Condition = NULL;
	Body = NULL;
	lbl = AST_WHILELOOP;
	al_tag_name = "";
	parent_op_node = -1;
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

void WhileLoop::setALtagName(std::string a_al_tag_name) {
	al_tag_name = a_al_tag_name;
}

void WhileLoop::setParentOpNode(int a_parent_op_node) {
	parent_op_node = a_parent_op_node;
}

Base_AST* WhileLoop::getCondition() {
	return Condition;
}

Base_AST* WhileLoop::getBody() {
	return Body;
}

std::string WhileLoop::getALTagName() {
	return al_tag_name;
}

int WhileLoop::getParentOpNode() {
	return parent_op_node;
}

Base_AST * WhileLoop::copyAST() {
	WhileLoop * cpy = new WhileLoop();
	if(Body != NULL)
		cpy->setBody(Body->copyAST());
	if(Condition != NULL)
		cpy->setCondition(Condition->copyAST());
	cpy->setParentOpNode(parent_op_node);
		
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
	StoreInst * llvm_store_inst;
	Value * address_for_spu = NULL;
	
	AllocaInst * llvm_alloca_inst = Builder.CreateAlloca(Type::getInt32Ty(GlobalContext), nullptr, al_tag_name.c_str());
	NamedValues[al_tag_name] = llvm_alloca_inst;
	//ret = (Value *)NamedValues[al_tag_name];
	
	Function * func = Builder.GetInsertBlock()->getParent();
	BasicBlock * headerBB = BasicBlock::Create(GlobalContext, "condition", func);
	Builder.CreateBr(headerBB);
	Builder.SetInsertPoint(headerBB);

	BasicBlock * loopBB = BasicBlock::Create(GlobalContext, "loop");
	BasicBlock * afterBB = BasicBlock::Create(GlobalContext, "afterloop");
	Value * cond = NULL;
	if(Condition != NULL) {
		cond = Condition->generateCode();
		// TODO: Additional LLVM if-branch to store the necessary jump address for SPU after receiving the result of condition evaluation
		StoreInst * llvm_store_inst = Builder.CreateStore(cond, ret);//TODO: Result of condition which will be transmitted -- we need address -- replace cond
		if(cond != NULL) {
			Builder.CreateCondBr(cond, loopBB, afterBB);
			func->getBasicBlockList().push_back(loopBB); // Inserting basic block for ELSE-branch after basic block for THEN-branch
			Builder.SetInsertPoint(loopBB);
			// Storing address to send to SPU in case condition is true
			ret = (Value *)NamedValues[al_tag_name];
			address_for_spu = ConstantInt::get(Type::getInt32Ty(GlobalContext), true_address[parent_op_node]);
			llvm_store_inst = Builder.CreateStore(address_for_spu, ret); 
			
			if(Body != NULL) {
				Body->generateCode();
			}
			Builder.CreateBr(headerBB);
			func->getBasicBlockList().push_back(afterBB); // Inserting basic block for instructions after merging of branches after basic block for ELSE-branch
			Builder.SetInsertPoint(afterBB);
			
			// Storing address to send to SPU in case condition is false
			address_for_spu = ConstantInt::get(Type::getInt32Ty(GlobalContext), false_address[parent_op_node]);
			llvm_store_inst = Builder.CreateStore(address_for_spu, ret);
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
		SP_IR[mem_point].tag[0] = false; // Tag is false - we are waiting for jmp address from CPU
		SP_IR[mem_point].tag[1] = true; // Not in use
		SP_IR[mem_point].tag[2] = true; // Not in use
		SP_IR[mem_point].op[0] = 0; // The value is received from CPU
		SP_IR[mem_point].op[1] = 0; // Not in use
		SP_IR[mem_point].op[2] = 0; // Not in use
		SP_IR[mem_point].opcode = JT; // Setting the opcode for conditional jump to end of the loop
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
			SP_IR[mem_point].opcode = JT; // Setting the opcode for unconditional jump to the loop condition
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