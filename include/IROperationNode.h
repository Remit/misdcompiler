/*
 * IROperationNode.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IROPERATIONNODE_H_
#define IROPERATIONNODE_H_

//Include section ---BEGIN---
#include "IRNode.h"
#include "BaseAST.h"

//Include section ---END---

class IR_OperationNode: public IR_Node {
public:
	IR_OperationNode();
	virtual ~IR_OperationNode();

	void setNodeASTSubTree( Base_AST* a_subTree );
	void setOperationType(operation_type a_operationType);

	Base_AST* getNodeASTSubTree();
	operation_type getOperationType();

private:
	Base_AST* nodeASTSubTree; // A part of AST tree growing from this operation node
	operation_type operationType;
};

#endif /* IROPERATIONNODE_H_ */
