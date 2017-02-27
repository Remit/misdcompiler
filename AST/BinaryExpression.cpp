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

void BinaryExpression::print(std::ostream * print_stream) {
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
	
	*print_stream << "\n - Binary expression: " << op_str;
	if(BinExpr_LHS != NULL) {
		*print_stream << "\n - Left operand: ";
		BinExpr_LHS->print(print_stream);
	}
	if(BinExpr_RHS != NULL) {
		*print_stream << "\n - Right operand: ";
		BinExpr_RHS->print(print_stream);
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
		if(op != OP_ASSIGN) {
			if((LHS_code->getType()->isFPOrFPVectorTy()) || (RHS_code->getType()->isFPOrFPVectorTy())) {
				if(LHS_code->getType()->isIntOrIntVectorTy())
					LHS_code = Builder.CreateIntCast(LHS_code, Type::getFloatTy(GlobalContext), true, "inttofloat");
				if(RHS_code->getType()->isIntOrIntVectorTy())
					RHS_code = Builder.CreateIntCast(RHS_code, Type::getFloatTy(GlobalContext), true, "inttofloat");
			}
			if((LHS_code->getType()->isDoubleTy()) || (RHS_code->getType()->isDoubleTy())) {
				if(LHS_code->getType()->isIntOrIntVectorTy())
					LHS_code = Builder.CreateIntCast(LHS_code, Type::getDoubleTy(GlobalContext), true, "inttodouble");
				if(RHS_code->getType()->isIntOrIntVectorTy())
					RHS_code = Builder.CreateIntCast(RHS_code, Type::getDoubleTy(GlobalContext), true, "inttodouble");
				if(LHS_code->getType()->isFPOrFPVectorTy())
					LHS_code = Builder.CreateFPCast(LHS_code, Type::getDoubleTy(GlobalContext), "floattodouble");
				if(RHS_code->getType()->isFPOrFPVectorTy())
					RHS_code = Builder.CreateFPCast(RHS_code, Type::getDoubleTy(GlobalContext), "floattodouble");
			}
		}
		switch(op) {
			case OP_PLUS:
				if(LHS_code->getType()->isIntOrIntVectorTy() && RHS_code->getType()->isIntOrIntVectorTy())
					ret = Builder.CreateAdd(LHS_code, RHS_code, "addtmp");
				else
					ret = Builder.CreateFAdd(LHS_code, RHS_code, "addtmp");
				break;
			case OP_MINUS:
				if(LHS_code->getType()->isIntOrIntVectorTy() && RHS_code->getType()->isIntOrIntVectorTy())
					ret = Builder.CreateSub(LHS_code, RHS_code, "subtmp");
				else
					ret = Builder.CreateFSub(LHS_code, RHS_code, "subtmp");
				break;
			case OP_DIV:
				if(LHS_code->getType()->isIntOrIntVectorTy() && RHS_code->getType()->isIntOrIntVectorTy())
					ret = Builder.CreateSDiv(LHS_code, RHS_code, "divtmp");
				else
					ret = Builder.CreateFDiv(LHS_code, RHS_code, "divtmp");
				break;
			case OP_MUL:
				if(LHS_code->getType()->isIntOrIntVectorTy() && RHS_code->getType()->isIntOrIntVectorTy())
					ret = Builder.CreateMul(LHS_code, RHS_code, "multmp");
				else
					ret = Builder.CreateFMul(LHS_code, RHS_code, "multmp");
				break;
			case OP_MOD:
				if(LHS_code->getType()->isIntOrIntVectorTy() && RHS_code->getType()->isIntOrIntVectorTy())
					ret = Builder.CreateSRem(LHS_code, RHS_code, "remtmp");
				else
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
				ret = (Value *)NamedValues[var_name];
				if(ret != NULL) {
					if(ret->getType()->isIntOrIntVectorTy()) {
						if(RHS_code->getType()->isFPOrFPVectorTy() || RHS_code->getType()->isDoubleTy())
							RHS_code = Builder.CreateFPCast(RHS_code, ret->getType(), "floatconversion");
					} else if(ret->getType()->isFPOrFPVectorTy()) {
						if(RHS_code->getType()->isIntOrIntVectorTy())
							RHS_code = Builder.CreateIntCast(RHS_code, ret->getType(), true, "inttofloat");
						else if(RHS_code->getType()->isDoubleTy())
							RHS_code = Builder.CreateFPCast(RHS_code, ret->getType(), "floatconversion");
					} else if(ret->getType()->isDoubleTy()) {
						if(RHS_code->getType()->isIntOrIntVectorTy())
							RHS_code = Builder.CreateIntCast(RHS_code, ret->getType(), true, "inttodouble");
						else if(RHS_code->getType()->isFPOrFPVectorTy())
							RHS_code = Builder.CreateFPCast(RHS_code, ret->getType(), "floatconversion");
					}
					llvm_store_inst = Builder.CreateStore(RHS_code, ret);
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

std::string BinaryExpression::generateStructCode() {
	std::string ret = "";
	return ret;
}