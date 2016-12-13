#include "../include/NumberExpr.h"

NumberExpr::NumberExpr()
{
	value = 0.0;
	lbl = AST_NUMBEREXPR;
}

NumberExpr::~NumberExpr()
{
}

void NumberExpr::setValue(double a_val) {
	value = a_val;
}

double NumberExpr::getValue() {
	return value;
}

Base_AST * NumberExpr::copyAST() {
	NumberExpr * cpy = new NumberExpr(value);
	return cpy;
}
void NumberExpr::print() {
	std::cout << "\n - Number (constant): " <<  value;
}

Value * NumberExpr::generateCode() {
	return ConstantFP::get(getGlobalContext(), APFloat(value));
}