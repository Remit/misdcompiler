/*
 * IROperationNode.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "IROperationNode.h"

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
