#include "../include/BinaryExpression.h"

BinaryExpression::BinaryExpression()
{
	op = OP_BINARY_UNDEFINED;
	BinExpr_LHS = NULL;
	BinExpr_RHS = NULL;
	lbl = AST_BINARYEXPRESSION;
}

BinaryExpression::~BinaryExpression()
{
}

void BinaryExpression::setOperation(bin_op_types a_op) {
	op = a_op;
}

void BinaryExpression::setLHS(Base_AST* LHS_AST) {
	BinExpr_LHS = LHS_AST;
}

void BinaryExpression::setRHS(Base_AST* RHS_AST) {
	BinExpr_RHS = RHS_AST;
}

bin_op_types BinaryExpression::getOperation() {
	return op;
}

Base_AST* BinaryExpression::getLHS() {
	return BinExpr_LHS;
}

Base_AST* BinaryExpression::getRHS() {
	return BinExpr_RHS;
}

Base_AST * BinaryExpression::copyAST() {
	BinaryExpression * cpy = new BinaryExpression();
	cpy->setOperation(op);
	if(BinExpr_LHS != NULL)
		cpy->setLHS(BinExpr_LHS->copyAST());
	if(BinExpr_RHS != NULL)
		cpy->setRHS(BinExpr_RHS->copyAST());
		
	return cpy;
}

void BinaryExpression::print() {
	std::string op_str;
	switch(op) {
    case OP_PLUS:
		op_str = " + ";
		break;
    case OP_MINUS:
		op_str = " - ";
		break;
    case OP_DIV:
		op_str = " / ";
		break;
    case OP_MUL:
		op_str = " * ";
		break;
    case OP_MOD:
		op_str = " % ";
		break;
    case OP_AND:
		op_str = " & ";
		break;
    case OP_OR:
		op_str = " | ";
		break;
	case OP_ASSIGN:
		op_str = " = ";
		break;
	case OP_BINARY_UNDEFINED:
		op_str = " ? ";
		break;
    }
	
	std::cout << "\n - Binary expression: " << op_str;
	if(BinExpr_LHS != NULL) {
		std::cout << "\n - Left operand: ";
		BinExpr_LHS->print();
	}
	if(BinExpr_RHS != NULL) {
		std::cout << "\n - Right operand: ";
		BinExpr_RHS->print();
	}
}

Value * BinaryExpression::generateCode() {
	Value * ret;
	Value * LHS_code = NULL;
	Value * RHS_code = NULL;
	VariableExpr * ret_var = NULL;
	std::string var_name = "";
	StoreInst * llvm_store_inst = NULL;
	
	if((op != OP_ASSIGN) && (BinExpr_LHS != NULL))
		LHS_code = BinExpr_LHS->generateCode();
	if(BinExpr_RHS != NULL)
		RHS_code = BinExpr_RHS->generateCode();
		
	if((BinExpr_LHS == NULL) || (BinExpr_RHS == NULL))
		ret = NULL;
	else {
		switch(op) {
			case OP_PLUS:
				ret = Builder.CreateFAdd(LHS_code, RHS_code, "addtmp");
				break;
			case OP_MINUS:
				ret = Builder.CreateFSub(LHS_code, RHS_code, "subtmp");
				break;
			case OP_DIV:
				ret = Builder.CreateFDiv(LHS_code, RHS_code, "divtmp");
				break;
			case OP_MUL:
				ret = Builder.CreateFMul(LHS_code, RHS_code, "multmp");
				break;
			case OP_MOD:
				ret = Builder.CreateFRem(LHS_code, RHS_code, "remtmp");
				break;
			case OP_AND:
				ret = Builder.CreateAnd(LHS_code, RHS_code, "andtmp");
				break;
			case OP_OR:
				ret = Builder.CreateOr(LHS_code, RHS_code, "ortmp");
				break;
			case OP_ASSIGN:
				ret_var = (VariableExpr *)BinExpr_LHS;
				var_name = ret_var->getName();
				ret = NamedValues[var_name];
				if(ret != NULL) {
					llvm_store_inst = new StoreInst(RHS_code, ret, Builder.GetInsertBlock());
					ret = llvm_store_inst;
				}
				break;
			case OP_BINARY_UNDEFINED:
				ret = NULL;
				break;
		}
	}
	
	return ret;
}