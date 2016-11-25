#include "../include/StructuresExpression.h"

StructuresExpression::StructuresExpression()
{
	struct_op = OP_STRUCT_UNDEFINED;
	arg1 = NULL;
	arg2 = NULL;
	arg3 = NULL;
	lbl = AST_STRUCTURESEXPRESSION;
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

Base_AST * StructuresExpression::copyAST() {
	StructuresExpression * cpy = new StructuresExpression();
	cpy->setOperation(struct_op);
	if(arg1!= NULL)
		cpy->setArg1(arg1->copyAST());
	if(arg2!= NULL)
		cpy->setArg2(arg2->copyAST());
	if(arg3!= NULL)
		cpy->setArg3(arg3->copyAST());
	
	return cpy;
}

void StructuresExpression::print() {
	std::string op_str;

	switch(struct_op) {
    case OP_SEARCH_STR:
		op_str = " SRCH ";
		break;
    case OP_SEARCH_SML_STR:
		op_str = " SRCH< ";
		break;
    case OP_SEARCH_GRT_STR:
		op_str = " SRCH> ";
		break;
    case OP_INSERT_STR:
		op_str = " INSERT ";
		break;
    case OP_DELETE_FROM_STR:
		op_str = " DEL ";
		break;
	case OP_NEXT_STR:
		op_str = " NEXT ";
		break;
	case OP_DELETE_STR:
		op_str = " DEL_STR ";
		break;
	case OP_MAX_STR:
		op_str = " MAX ";
		break;
	case OP_MIN_STR:
		op_str = " MIN ";
		break;
	case OP_POWER_STR:
		op_str = " POWER ";
		break;
	case OP_UNION_STR:
		op_str = " UNION ";
		break;
	case OP_INTERSECT_STR:
		op_str = " INTERSECT ";
		break;
	case OP_NOT_STR:
		op_str = " NOT ";
		break;
	case OP_GT_STR:
		op_str = " SECTION> ";
		break;
	case OP_LT_STR:
		op_str = " SECTION< ";
		break;
	case OP_LTE_STR:
		op_str = " SECTION<= ";
		break;
	case OP_GTE_STR:
		op_str = " SECTION>= ";
		break;
	case OP_SEND_TO_SPU:
		op_str = " SEND => SPU ";
		break;
	case OP_SEND_TO_CPU:
		op_str = " SEND => CPU ";
		break;
	case OP_RECEIVE_FROM_SPU:
		op_str = " RECV <= SPU ";
		break;
	case OP_RECEIVE_FROM_CPU:
		op_str = " RECV <= CPU ";
		break;
	case OP_STRUCT_UNDEFINED:
		op_str = " ? ";
		break;
    }
	
	std::cout << "\n - Structures processing expression: " << op_str;
	if(arg1 != NULL) {
		std::cout << "\n - First argument: ";
		arg1->print();
	}
	if(arg2 != NULL) {
		std::cout << "\n - Second argument: ";
		arg2->print();
	}
	if(arg3 != NULL) {
		std::cout << "\n - Third argument: ";
		arg3->print();
	}
}