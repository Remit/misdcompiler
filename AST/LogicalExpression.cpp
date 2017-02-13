#include "../include/LogicalExpression.h"

LogicalExpression::LogicalExpression()
{
	op = OP_LOGICAL_UNDEFINED;
	BinExpr_LHS = NULL;
	BinExpr_RHS = NULL;
	lbl = AST_LOGICALEXPRESSION;
	exp_bool_vars_list = NULL;
}

LogicalExpression::LogicalExpression(cond_op_types a_op, Base_AST* LHS_AST, Base_AST* RHS_AST, std::vector< std::string > * a_exp_bool_vars_list) {
	op = a_op;
	BinExpr_LHS = LHS_AST;
	BinExpr_RHS = RHS_AST;
	lbl = AST_LOGICALEXPRESSION;
	exp_bool_vars_list = a_exp_bool_vars_list;
}

LogicalExpression::~LogicalExpression()
{
}

void LogicalExpression::setOperation(cond_op_types a_op) {
	op = a_op;
}

void LogicalExpression::setLHS(Base_AST* LHS_AST) {
	BinExpr_LHS = LHS_AST;
}

void LogicalExpression::setRHS(Base_AST* RHS_AST) {
	BinExpr_RHS = RHS_AST;
}

cond_op_types LogicalExpression::getOperation() {
	return op;
}

Base_AST* LogicalExpression::getLHS() {
	return BinExpr_LHS;
}

Base_AST* LogicalExpression::getRHS() {
	return BinExpr_RHS;
}

std::vector< std::string > * LogicalExpression::getBoolVarsList_ptr() {
	return exp_bool_vars_list;
}

Base_AST * LogicalExpression::copyAST() {
	LogicalExpression * cpy = new LogicalExpression();
	cpy->setOperation(op);
	if(BinExpr_LHS != NULL)
		cpy->setLHS(BinExpr_LHS->copyAST());
	if(BinExpr_RHS != NULL)
		cpy->setRHS(BinExpr_RHS->copyAST());
	
	return cpy;
}

void LogicalExpression::print() {
	std::string op_str;
	
	switch(op) {
    case OP_LT:
		op_str = " < ";
		break;
    case OP_GT:
		op_str = " > ";
		break;
    case OP_LTE:
		op_str = " <= ";
		break;
    case OP_GTE:
		op_str = " >= ";
		break;
    case OP_EQ:
		op_str = " == ";
		break;
	case OP_LOGICAL_UNDEFINED:
		op_str = " ? ";
		break;
    }
	
	std::cout << "\n - Logical expression: " << op_str;
	if(BinExpr_LHS != NULL) {
		std::cout << "\n - Left operand: ";
		BinExpr_LHS->print();
	}
	if(BinExpr_RHS != NULL) {
		std::cout << "\n - Right operand: ";
		BinExpr_RHS->print();
	}
}

Value * LogicalExpression::generateCode() {
	Value * ret;
	Value * LHS_code = NULL;
	Value * RHS_code = NULL;
	
	if(BinExpr_LHS != NULL)
		LHS_code = BinExpr_LHS->generateCode();
	if(BinExpr_RHS != NULL)
		RHS_code = BinExpr_RHS->generateCode();
		
	
	if((BinExpr_LHS == NULL) || (BinExpr_RHS == NULL))
		ret = NULL;
	else { // Considering different cases of compared types. We need the compared values to be of the same type. If we have at least one double then we transform the other to double as well.
		if((LHS_code->getType()->isIntOrIntVectorTy()) && (RHS_code->getType()->isIntOrIntVectorTy())) {
			switch(op) {
				case OP_LT:
					ret = Builder.CreateICmpULT(LHS_code, RHS_code, "cmplttmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boollttmp");
					break;
				case OP_GT:
					ret = Builder.CreateICmpUGT(LHS_code, RHS_code, "cmpgttmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolgttmp");
					break;
				case OP_LTE:
					ret = Builder.CreateICmpULE(LHS_code, RHS_code, "cmpltetmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolltetmp");
					break;
				case OP_GTE:
					ret = Builder.CreateICmpUGE(LHS_code, RHS_code, "cmpgtetmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolgtetmp");
					break;
				case OP_EQ:
					ret = Builder.CreateICmpEQ(LHS_code, RHS_code, "cmpeqtmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "booleqtmp");
					break;
				case OP_LOGICAL_UNDEFINED:
					ret = NULL;
					break;
			}
		} else if((LHS_code->getType()->isDoubleTy()) || (RHS_code->getType()->isDoubleTy())) {
			if(!LHS_code->getType()->isDoubleTy())
				LHS_code = Builder.CreateIntCast(LHS_code, Type::getDoubleTy(GlobalContext), true, "inttofloat");
			if(!RHS_code->getType()->isDoubleTy())
				RHS_code = Builder.CreateIntCast(RHS_code, Type::getDoubleTy(GlobalContext), true, "inttofloat");
			switch(op) {
				case OP_LT:
					ret = Builder.CreateFCmpULT(LHS_code, RHS_code, "cmplttmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boollttmp");
					break;
				case OP_GT:
					ret = Builder.CreateFCmpUGT(LHS_code, RHS_code, "cmpgttmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolgttmp");
					break;
				case OP_LTE:
					ret = Builder.CreateFCmpULE(LHS_code, RHS_code, "cmpltetmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolltetmp");
					break;
				case OP_GTE:
					ret = Builder.CreateFCmpUGE(LHS_code, RHS_code, "cmpgtetmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolgtetmp");
					break;
				case OP_EQ:
					ret = Builder.CreateFCmpUEQ(LHS_code, RHS_code, "cmpeqtmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "booleqtmp");
					break;
				case OP_LOGICAL_UNDEFINED:
					ret = NULL;
					break;
			}
		} else if((LHS_code->getType()->isFPOrFPVectorTy()) || (RHS_code->getType()->isFPOrFPVectorTy())) {
			if(!LHS_code->getType()->isFPOrFPVectorTy())
				LHS_code = Builder.CreateIntCast(LHS_code, Type::getFloatTy(GlobalContext), true, "inttofloat");
			if(!RHS_code->getType()->isFPOrFPVectorTy())
				RHS_code = Builder.CreateIntCast(RHS_code, Type::getFloatTy(GlobalContext), true, "inttofloat");
			switch(op) {
				case OP_LT:
					ret = Builder.CreateFCmpULT(LHS_code, RHS_code, "cmplttmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boollttmp");
					break;
				case OP_GT:
					ret = Builder.CreateFCmpUGT(LHS_code, RHS_code, "cmpgttmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolgttmp");
					break;
				case OP_LTE:
					ret = Builder.CreateFCmpULE(LHS_code, RHS_code, "cmpltetmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolltetmp");
					break;
				case OP_GTE:
					ret = Builder.CreateFCmpUGE(LHS_code, RHS_code, "cmpgtetmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "boolgtetmp");
					break;
				case OP_EQ:
					ret = Builder.CreateFCmpUEQ(LHS_code, RHS_code, "cmpeqtmp");
					//ret = Builder.CreateUIToFP(ret, Type::getDoubleTy(GlobalContext), "booleqtmp");
					break;
				case OP_LOGICAL_UNDEFINED:
					ret = NULL;
					break;
			}
		} else {
			std::cout << "LHS and RHS of comparison must be of the same type." << std::endl;
		}
	}

	
	return ret;
}

std::string LogicalExpression::generateStructCode() {
	std::string ret = "";
	return ret;
}