#ifndef STRUCTURESEXPRESSION_H
#define STRUCTURESEXPRESSION_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class StructuresExpression : public Base_AST
{
public:
	StructuresExpression();
	StructuresExpression(structures_proc_op_types a_op, Base_AST* a_arg1, Base_AST* a_arg2, Base_AST* a_arg3) : struct_op(a_op), arg1(a_arg1), arg2(a_arg2), arg3(a_arg3) { lbl = AST_STRUCTURESEXPRESSION; }
	~StructuresExpression();
	void setOperation(structures_proc_op_types a_op);
	void setArg1(Base_AST* a_arg1);
	void setArg2(Base_AST* a_arg2);
	void setArg3(Base_AST* a_arg3);
	
	structures_proc_op_types getOperation();
	Base_AST* getArg1();
	Base_AST* getArg2();
	Base_AST* getArg3();
	
	Base_AST * copyAST();
	
	void print(std::ostream * print_stream);
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();

private:
	structures_proc_op_types struct_op;
	Base_AST* arg1;
	Base_AST* arg2;
	Base_AST* arg3;
};

#endif // STRUCTURESEXPRESSION_H
