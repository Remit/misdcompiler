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

void StructuresExpression::print(std::ostream * print_stream) {
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
	case OP_STRUCT_UNDEFINED:
		op_str = " ? ";
		break;
    }
	
	* print_stream << "\n - Structures processing expression: " << op_str;
	if(arg1 != NULL) {
		* print_stream << "\n - First argument: ";
		arg1->print(print_stream);
	}
	if(arg2 != NULL) {
		* print_stream << "\n - Second argument: ";
		arg2->print(print_stream);
	}
	if(arg3 != NULL) {
		* print_stream << "\n - Third argument: ";
		arg3->print(print_stream);
	}
}

Value * StructuresExpression::generateCode() {
	Value * ret = NULL;
	return ret;
}

std::string StructuresExpression::generateStructCode() {
	std::string ret = "";
	std::string arg1_str = "";
	std::string arg2_str = "";
	std::string arg3_str = "";
	int operand_1;
	int operand_2;
	int operand_3;
	
	
	SP_IR[mem_point].tag[0] = true;
	SP_IR[mem_point].tag[1] = true;
	SP_IR[mem_point].tag[2] = true;
	
	// Writing arguments to the instruction representation
	if(arg1 != NULL) {
		arg1_str = arg1->generateStructCode();
		if(arg1_str.compare("") == 0) // If the argument is to be received
			SP_IR[mem_point].tag[0] = false;
		else if(arg1_str.substr(0,6).compare("STRUCT") == 0) // If the argument is structure
			SP_IR[mem_point].op[0] = std::stol(arg1_str.substr(6,1));
		else // If the argument is a number
			SP_IR[mem_point].op[0] = std::stol(arg1_str);
	}
	if(arg2 != NULL) {
		arg2_str = arg2->generateStructCode();
		if(arg2_str.compare("") == 0) // If the argument is to be received
			SP_IR[mem_point].tag[1] = false;
		else if(arg2_str.substr(0,6).compare("STRUCT") == 0) // If the argument is structure
			SP_IR[mem_point].op[1] = std::stol(arg2_str.substr(6,1));
		else // If the argument is a number
			SP_IR[mem_point].op[1] = std::stol(arg2_str);
	}
	if(arg3 != NULL) {
		arg3_str = arg3->generateStructCode();
		if(arg3_str.compare("") == 0) // If the argument is to be received
			SP_IR[mem_point].tag[2] = false;
		else if(arg3_str.substr(0,6).compare("STRUCT") == 0) // If the argument is structure
			SP_IR[mem_point].op[2] = std::stol(arg3_str.substr(6,1));
		else // If the argument is a number
			SP_IR[mem_point].op[2] = std::stol(arg3_str);
	}
	
	// Writing operation code and queue format to the instruction representation
	bool queue = false;
	int opcode;
	switch(struct_op) {
		case OP_SEARCH_STR:
			opcode = SEARCH;
			queue = true;
			break;
		case OP_SEARCH_SML_STR:
			opcode = 0; // TODO:
			queue = true;
			break;
		case OP_SEARCH_GRT_STR:
			opcode = 0; // TODO:
			queue = true;
			break;
		case OP_INSERT_STR:
			opcode = ADD;
			break;
		case OP_DELETE_FROM_STR:
			opcode = DEL;
			break;
		case OP_NEXT_STR:
			opcode = NEXT;
			queue = true;
			break;
		case OP_DELETE_STR:
			opcode = DELS;
			break;
		case OP_MAX_STR:
			opcode = MAX;
			queue = true;
			break;
		case OP_MIN_STR:
			opcode = MIN;
			queue = true;
			break;
		case OP_POWER_STR:
			opcode = POWER;
			queue = true;
			break;
		case OP_UNION_STR:
			opcode = OR;
			break;
		case OP_INTERSECT_STR:
			opcode = AND;
			break;
		case OP_NOT_STR:
			opcode = NOT;
			break;
		case OP_GT_STR:
			opcode = GR;
			break;
		case OP_LT_STR:
			opcode = LS;
			break;
		case OP_LTE_STR:
			opcode = LSEQ;
			break;
		case OP_GTE_STR:
			opcode = GREQ;
			break;
		case OP_STRUCT_UNDEFINED:
			opcode = 0;
			break;
	}
	
	SP_IR[mem_point].q = queue;
	SP_IR[mem_point].opcode = opcode;
	
	// These to be set on when parsing on the level of structures
	strcpy(SP_IR[mem_point].jmp_label,"");
	strcpy(SP_IR[mem_point].label,"");
	SP_IR[mem_point].jmp_adr = -1;
	
	if(mem_point != (MEM_LENGTH - 2)) {
		mem_point++;
	} else {
		printf("Error: not enough memory for SPU code (MEM_LENGTH too small).");
		return ret;
	}
	
	return ret;
}
