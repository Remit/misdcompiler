#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef VARIABLEEXPR_H
#include "VariableExpr.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class BinaryExpression : public Base_AST
{
public:
	BinaryExpression();
	BinaryExpression(bin_op_types a_op, Base_AST* LHS_AST, Base_AST* RHS_AST) : op(a_op), BinExpr_LHS(LHS_AST), BinExpr_RHS(RHS_AST) { lbl = AST_BINARYEXPRESSION; }
	~BinaryExpression();
	void setOperation(bin_op_types a_op);
	void setLHS(Base_AST* LHS_AST);
	void setRHS(Base_AST* RHS_AST);
	
	bin_op_types getOperation();
	Base_AST* getLHS();
	Base_AST* getRHS();
	
	Base_AST * copyAST();
	
	void print();
	
	virtual Value *generateCode();

private:
	bin_op_types op;
	Base_AST* BinExpr_LHS;
	Base_AST* BinExpr_RHS;

};

#endif // BINARYEXPRESSION_H
