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