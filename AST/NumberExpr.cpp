#include "../include/NumberExpr.h"

NumberExpr::NumberExpr()
{
	value = 0.0;
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
