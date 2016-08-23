/*
 * IRNode.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 *
 *  This class represents a basic building block
 *  of program intermediate representation (IR)
 *  as a program graph. IR in its current form
 *  if to be used to divide program graph into
 *  program graph for arithmetic and logical
 *  operations and program graph for operations
 *  on data structures. Each IR_Node contains
 *  a fragment of AST for the whole program in
 *  order to make possible further AST reconstruction
 *  for both resulting graphs.
 *
 */

#ifndef IRNODE_H_
#define IRNODE_H_

//Include section ---BEGIN---
#include "CommonTypesAndConstants.h"

//Include section ---END---

class IR_Node {
public:
	IR_Node();
	virtual ~IR_Node();
	//Access to values in fields
	int getID();
	proc_type getProcType();

	//Setting values in fields
	void setID(int a_id);
	void setProcType(proc_type a_ProcType);

private:
	proc_type typeOfProcessor; //Type of processing unit which can be used to process the node
	int id; //A unique identifier of the node

};

#endif /* IRNODE_H_ */
