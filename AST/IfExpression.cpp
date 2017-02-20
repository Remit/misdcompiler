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

void IfExpression::print(std::ostream * print_stream) {
	* print_stream << "\n - If-expression - ";
	if(Condition != NULL) {
		* print_stream << "\n - Condition: ";
		Condition->print(print_stream);
	}
	if(ThenExpression != NULL) {
		* print_stream << "\n - Then: ";
		ThenExpression->print(print_stream);
	}
	if(ElseExpression != NULL) {
		* print_stream << "\n - Else: ";
		ElseExpression->print(print_stream);
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

std::string IfExpression::generateStructCode() {
	std::string ret = "";
	
	if(Condition != NULL) { // IF-check instruction generation (jwt)
		strcpy(SP_IR[mem_point].label, std::to_string(label_i).c_str()); // Assigning a unique label for condition;
		label_i++;
		SP_IR[mem_point].tag[0] = false; // Tag is false - we are waiting for check results from CPU
		SP_IR[mem_point].tag[1] = true; // Not in use
		SP_IR[mem_point].tag[2] = true; // Not in use
		SP_IR[mem_point].op[0] = 0; // The value is received from CPU
		SP_IR[mem_point].op[1] = 0; // Not in use
		SP_IR[mem_point].op[2] = 0; // Not in use
		SP_IR[mem_point].opcode = JT; // Setting the opcode for conditional jump to ELSE-branch
		SP_IR[mem_point].q = false;

		int jwt_pos = mem_point;
		mem_point++;
		int then_pos_beg = mem_point, else_pos_beg; // Positions of instructions in SPU program representation
		
		if(ThenExpression != NULL) {
			ThenExpression->generateStructCode();
		
			strcpy(SP_IR[then_pos_beg].label, std::to_string(label_i).c_str()); // Creating a label for then-branch
			label_i++;
			int unc_jmp_end = mem_point; // Point to insert an unconditional branch later when it becomes known
			SP_IR[mem_point].tag[0] = true; // Unconditional branch
			SP_IR[mem_point].tag[1] = true; // Not in use
			SP_IR[mem_point].tag[2] = true; // Not in use
			SP_IR[mem_point].op[0] = 1; // Unconditional branch
			SP_IR[mem_point].op[1] = 0; // Not in use
			SP_IR[mem_point].op[2] = 0; // Not in use
			mem_point++;
			
			else_pos_beg = mem_point;
			
			if(ElseExpression != NULL) {
				ElseExpression->generateStructCode();
			
				strcpy(SP_IR[else_pos_beg].label, std::to_string(label_i).c_str()); // Creating a label for else-branch
				strcpy(SP_IR[jwt_pos].jmp_label, std::to_string(label_i).c_str()); // Assigning a unique label for condition to jump to else-branch
				SP_IR[jwt_pos].jmp_adr = else_pos_beg;
				label_i++;
				
				strcpy(SP_IR[mem_point].label, std::to_string(label_i).c_str());
				SP_IR[unc_jmp_end].opcode = JT;// Assigning jump to end after finishing then-branch, whereas the continuation in case of else-branch is unconditional
				strcpy(SP_IR[unc_jmp_end].jmp_label, std::to_string(label_i).c_str());
				SP_IR[unc_jmp_end].jmp_adr = mem_point;
				
				label_i++;
			}
		}
	}
	
	return ret;
}