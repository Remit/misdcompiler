/*
 * IROperationNode.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IROPERATIONNODE_H_
#define IROPERATIONNODE_H_

//Include section ---BEGIN---
#ifndef IRNODE_H_
#include "IRNode.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

//Include section ---END---

class IR_OperationNode: public IR_Node {
public:
	IR_OperationNode();
	virtual ~IR_OperationNode();

	void setNodeASTSubTree( Base_AST* a_subTree );
	void setOperationType(operation_type a_operationType);

	Base_AST* getNodeASTSubTree();
	Base_AST* getNodeASTSubTreeCopy();
	operation_type getOperationType();

	void setConnectedNodeID(int gid);
	int getConnectedNodeID();

	void print();

private:
	Base_AST* nodeASTSubTree; // A part of AST tree growing from this operation node
	operation_type operationType;
	int connected_node_gid; // Global ID of node from node pair (used for end condition nodes in if-then-else and loop stmts)
};

#endif /* IROPERATIONNODE_H_ */
