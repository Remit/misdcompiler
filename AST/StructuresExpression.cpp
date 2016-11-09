#include "../include/StructuresExpression.h"

StructuresExpression::StructuresExpression()
{
	struct_op = OP_STRUCT_UNDEFINED;
	arg1 = NULL;
	arg2 = NULL;
	arg3 = NULL;
}

StructuresExpression::~StructuresExpression()
{
}

void StructuresExpression::setOperation(structures_proc_op_types a_op) {
	struct_op = a_op;
}

void StructuresExpression::setArg1(Base_AST* a_arg1) {
	arg1 = a_arg1;
}

void StructuresExpression::setArg2(Base_AST* a_arg2) {
	arg2 = a_arg2;
}
	
void StructuresExpression::setArg3(Base_AST* a_arg3) {
	arg3 = a_arg3;
}

structures_proc_op_types StructuresExpression::getOperation() {
	return struct_op;
}

Base_AST* StructuresExpression::getArg1() {
	return arg1;
}

Base_AST* StructuresExpression::getArg2() {
	return arg2;
}

Base_AST* StructuresExpression::getArg3() {
	return arg3;
}