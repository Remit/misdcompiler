#ifndef NUMBEREXPR_H
#define NUMBEREXPR_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

class NumberExpr : public Base_AST
{
public:
	NumberExpr();
	NumberExpr(double a_val) : value(a_val) { lbl = AST_NUMBEREXPR; }
	~NumberExpr();
	
	void setValue(double a_val);
	double getValue();
	
	Base_AST * copyAST();
	
	void print();

private:
	double value;

};

#endif // NUMBEREXPR_H
