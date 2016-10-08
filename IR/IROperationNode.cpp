/*
 * IROperationNode.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "../include/IROperationNode.h"

IR_OperationNode::IR_OperationNode() {
	// TODO Auto-generated constructor stub

}

IR_OperationNode::~IR_OperationNode() {
	// TODO Auto-generated destructor stub
}

void IR_OperationNode::setNodeASTSubTree( Base_AST* a_subTree ) {
	if(a_subTree != NULL)
		nodeASTSubTree = a_subTree;
}

void IR_OperationNode::setOperationType(operation_type a_operationType) {
	operationType = a_operationType;
}

Base_AST* IR_OperationNode::getNodeASTSubTree() {
	return nodeASTSubTree;
}

operation_type IR_OperationNode::getOperationType() {
	return operationType;
}

Base_AST* IR_OperationNode::getNodeASTSubTreeCopy() {
	//TODO describe copy method for AST
	Base_AST* ret_AST = NULL;
	return ret_AST;
}

void IR_OperationNode::print() {
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
	}
}
