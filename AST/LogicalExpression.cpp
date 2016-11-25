#include "../include/LogicalExpression.h"

LogicalExpression::LogicalExpression()
{
	op = OP_LOGICAL_UNDEFINED;
	BinExpr_LHS = NULL;
	BinExpr_RHS = NULL;
	lbl = AST_LOGICALEXPRESSION;
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