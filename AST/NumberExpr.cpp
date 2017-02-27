#include "../include/NumberExpr.h"

NumberExpr::NumberExpr()
{
	value = 0.0;
	lbl = AST_NUMBEREXPR;
	type_of_num = VAR_UNDEFINED;
}

NumberExpr::~NumberExpr()
{
}

void NumberExpr::setValue(double a_val) {
	value = a_val;
}

void NumberExpr::setType(variable_type a_type_of_num) {
	type_of_num = a_type_of_num;
}

double NumberExpr::getValue() {
	return value;
}

variable_type NumberExpr::getType() {
	return type_of_num;
}
	
Base_AST * NumberExpr::copyAST() {
	NumberExpr * cpy = new NumberExpr(value, type_of_num);
	return cpy;
}
void NumberExpr::print(std::ostream * print_stream) {
	* print_stream << "\n - Number (constant): " <<  value;
}

Value * NumberExpr::generateCode() {
	if(type_of_num == VAR_INT)
		return ConstantInt::get(Type::getInt16Ty(GlobalContext), (int)value);
	else if(type_of_num == VAR_FLOAT)
		return ConstantFP::get(GlobalContext, APFloat(value));
}

std::string NumberExpr::generateStructCode() {
	std::string ret = std::to_string(value);
	return ret;
}