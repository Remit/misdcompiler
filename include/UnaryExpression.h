#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

class UnaryExpression : public Base_AST
{
public:
	UnaryExpression();
	UnaryExpression(unary_op_types a_op, Base_AST* RHS_AST) : op(a_op), UnaryExpr_RHS(RHS_AST) { lbl = AST_UNARYEXPRESSION; }
	~UnaryExpression();
	void setOperation(unary_op_types a_op);
	void setRHS(Base_AST* RHS_AST);
	
	unary_op_types getOperation();
	Base_AST* getRHS();
	
	Base_AST * copyAST();
	
	void print();

private:
	unary_op_types op;
	Base_AST* UnaryExpr_RHS;
};

#endif // UNARYEXPRESSION_H
