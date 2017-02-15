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

void UnaryExpression::print(std::ostream * print_stream) {
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
	
	* print_stream << "\n - Unary Expression: " << op_str;
	if(UnaryExpr_RHS != NULL) {
		* print_stream << "\n - Right side of expression: ";
		UnaryExpr_RHS->print(print_stream);
	}
}

Value * UnaryExpression::generateCode() {
	Value * ret;
	Value * RHS_code = NULL;
	
	if(UnaryExpr_RHS != NULL)
		RHS_code = UnaryExpr_RHS->generateCode();
		
	if(UnaryExpr_RHS == NULL)
		ret = NULL;
	else {
		switch(op) {
			case OP_NOT:
				ret = Builder.CreateNot(RHS_code, "nottmp");
				break;
			case OP_UMINUS:
				ret = Builder.CreateNeg(RHS_code, "negtmp");
				break;
			case OP_UNARY_UNDEFINED:
				ret = NULL;
				break;
		}
	}
	
	return ret;
}

std::string UnaryExpression::generateStructCode() {
	std::string ret = "";
	return ret;
}