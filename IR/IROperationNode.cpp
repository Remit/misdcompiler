/*
 * IROperationNode.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "../include/IROperationNode.h"

IR_OperationNode::IR_OperationNode()
{
    connected_node_gid = -1;
    last_loop_node_gid = -1;
    instructionType = I_UNDEFINED;
    defined_vars = NULL;
	input_names = NULL;
	output_name = NULL;
}

IR_OperationNode::~IR_OperationNode()
{
    if(defined_vars != NULL)
		delete[] defined_vars;
	if(input_names != NULL)
		delete[] input_names;
	if(output_name != NULL)
		delete output_name;
}

void IR_OperationNode::setNodeASTSubTree(Base_AST* a_subTree)
{
    if(a_subTree != NULL)
	nodeASTSubTree = a_subTree;
}

void IR_OperationNode::setOperationType(operation_type a_operationType)
{
    operationType = a_operationType;
}

Base_AST* IR_OperationNode::getNodeASTSubTree()
{
    return nodeASTSubTree;
}

operation_type IR_OperationNode::getOperationType()
{
    return operationType;
}

Base_AST* IR_OperationNode::getNodeASTSubTreeCopy()
{
    // TODO describe copy method for AST
    Base_AST* ret_AST = NULL;
    return ret_AST;
}

void IR_OperationNode::print()
{
    switch(operationType) {
    case IR_OP_TERMINATOR:
		std::cout << "terminator type";
		break;
    case IR_OP_PROCESSING:
		std::cout << "processing type";
		break;
    case IR_OP_BRANCH_BEGIN:
		std::cout << "branch begin type";
		break;
    case IR_OP_BRANCH_END:
		std::cout << "branch end type";
		break;
    case IR_OP_BRANCH_COND_BEGIN:
		std::cout << "conditional branch begin type";
		break;
    case IR_OP_SEND:
		std::cout << "send type";
		break;
    case IR_OP_RECEIVE:
		std::cout << "receive type";
		break;
	case IR_OP_DEFINITION:
		std::cout << "definition type";
		break;
    }
}

void IR_OperationNode::setConnectedNodeID(int gid)
{
    connected_node_gid = gid;
}

int IR_OperationNode::getConnectedNodeID()
{
    return connected_node_gid;
}

void IR_OperationNode::setLastNodeID_forLoops(int gid)
{
    last_loop_node_gid = gid;
}

int IR_OperationNode::getLastNodeID_forLoops()
{
    return last_loop_node_gid;
}

void IR_OperationNode::setInstructionType(low_level_instruction_type a_instructionType)
{
    instructionType = a_instructionType;
}

low_level_instruction_type IR_OperationNode::getInstructionType()
{
    return instructionType;
}

void IR_OperationNode::setDefinedVars(std::vector<std::string> * def_vars)
{
    unsigned int sz = def_vars->size();
    defined_vars = new std::vector<std::string>;
    defined_vars->reserve(sz);
    std::string tmp_str;
    for(unsigned int i = 0; i < sz; i++) {
		tmp_str = (*def_vars)[i];
		defined_vars->push_back(tmp_str);
    }
	
	return;
}

std::vector<std::string> * IR_OperationNode::getDefinedVars()
{
	std::vector<std::string> * ret_defined_vars = new std::vector<std::string>;
	unsigned int sz = defined_vars->size();
	ret_defined_vars->reserve(sz);
    std::string tmp_str;
    for(unsigned int i = 0; i < sz; i++) {
		tmp_str = (*defined_vars)[i];
		ret_defined_vars->push_back(tmp_str);
    }
	
	return ret_defined_vars;
}

void IR_OperationNode::setInputNames(std::vector<std::string>* a_input_names) {
    unsigned int sz = a_input_names->size();
    input_names = new std::vector<std::string>;
    input_names->reserve(sz);
    std::string tmp_str;
    for(unsigned int i = 0; i < sz; i++) {
		tmp_str = (*a_input_names)[i];
		input_names->push_back(tmp_str);
    }
	
	return;
}

void IR_OperationNode::setOutputName(std::string* a_output_name) {
	output_name = new std::string;
	std::string tmp_str = (*a_output_name);
	(*output_name) = tmp_str;
	return;
}

std::vector<std::string>* IR_OperationNode::getInputNames() {
	std::vector<std::string> * ret_input_names = new std::vector<std::string>;
	unsigned int sz = input_names->size();
	ret_input_names->reserve(sz);
    std::string tmp_str;
    for(unsigned int i = 0; i < sz; i++) {
		tmp_str = (*input_names)[i];
		ret_input_names->push_back(tmp_str);
    }
	
	return ret_input_names;
}

std::string* IR_OperationNode::getOutputName() {
	std::string * ret_output_name = new std::string;
	std::string tmp_str = (*output_name);
	(*ret_output_name) = tmp_str;
	return ret_output_name;
}

std::string IR_OperationNode::getPicturePath() {
	std::string pic_path;
	pic_path = "Cytospace/images/";
	proc_type pr = getProcType();
	if((pr == IR_CPU) || (pr == IR_BOTH))
		pic_path += "cpu/";
	else if(pr == IR_SPU)
		pic_path += "spu/";

	switch(operationType) {
	case IR_OP_TERMINATOR:
		pic_path += "Terminator";
		break;
	case IR_OP_PROCESSING:
		pic_path += "Processing";
		break;
	case IR_OP_BRANCH_BEGIN:
		pic_path += "Branch_begin";
		break;
	case IR_OP_BRANCH_END:
		pic_path += "Branch_end";
		break;
	case IR_OP_BRANCH_COND_BEGIN:
		pic_path += "Branch_cond_begin";
		break;
	case IR_OP_SEND:
		pic_path += "Send";
		break;
	case IR_OP_RECEIVE:
		pic_path += "Receive";
		break;
	case IR_OP_DEFINITION:
		pic_path += "Define";
		break;
	}

	pic_path += ".jpg";
	return pic_path;
}
