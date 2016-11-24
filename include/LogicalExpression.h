#ifndef LOGICALEXPRESSION_H
#define LOGICALEXPRESSION_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

class LogicalExpression : public Base_AST
{
public:
	LogicalExpression();
	LogicalExpression(cond_op_types a_op, Base_AST* LHS_AST, Base_AST* RHS_AST) : op(a_op), BinExpr_LHS(LHS_AST), BinExpr_RHS(RHS_AST) {}
	~LogicalExpression();
	void setOperation(cond_op_types a_op);
	void setLHS(Base_AST* LHS_AST);
	void setRHS(Base_AST* RHS_AST);
	
	cond_op_types getOperation();
	Base_AST* getLHS();
	Base_AST* getRHS();

private:
	cond_op_types op;
	Base_AST* BinExpr_LHS;
	Base_AST* BinExpr_RHS;

};

#endif // LOGICALEXPRESSION_H
