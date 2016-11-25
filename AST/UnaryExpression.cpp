#include "../include/UnaryExpression.h"

UnaryExpression::UnaryExpression()
{
    op = OP_UNARY_UNDEFINED;
	UnaryExpr_RHS = NULL;
	lbl = AST_UNARYEXPRESSION;
}

UnaryExpression::~UnaryExpression()
{
}

void UnaryExpression::setOperation(unary_op_types a_op) {
	op = a_op;
}

void UnaryExpression::setRHS(Base_AST* RHS_AST) {
	UnaryExpr_RHS = RHS_AST;
}

unary_op_types UnaryExpression::getOperation() {
	return op;
}

Base_AST* UnaryExpression::getRHS() {
	return UnaryExpr_RHS;
}

Base_AST * UnaryExpression::copyAST() {
	UnaryExpression * cpy = new UnaryExpression();
	cpy->setOperation(op);
	if(UnaryExpr_RHS != NULL)
		cpy->setRHS(UnaryExpr_RHS->copyAST());
		
	return cpy;
}

void UnaryExpression::print() {
	std::string op_str;
	switch(op) {
    case OP_NOT:
		op_str = " ! ";
		break;
    case OP_UMINUS:
		op_str = " - ";
		break;
    case OP_UNARY_UNDEFINED:
		op_str = " ? ";
		break;
	}
	
	std::cout << "\n - Unary Expression: " << op_str;
	if(UnaryExpr_RHS != NULL) {
		std::cout << "\n - Right side of expression: ";
		UnaryExpr_RHS->print();
	}
}