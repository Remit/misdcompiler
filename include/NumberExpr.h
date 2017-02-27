#ifndef NUMBEREXPR_H
#define NUMBEREXPR_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class NumberExpr : public Base_AST
{
public:
	NumberExpr();
	NumberExpr(double a_val, variable_type a_type_of_num) : value(a_val), type_of_num(a_type_of_num) { lbl = AST_NUMBEREXPR; }
	~NumberExpr();
	
	void setValue(double a_val);
	void setType(variable_type a_type_of_num);
	double getValue();
	variable_type getType();
	
	Base_AST * copyAST();
	
	void print(std::ostream * print_stream);
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();

private:
	double value;
	variable_type type_of_num;

};

#endif // NUMBEREXPR_H
