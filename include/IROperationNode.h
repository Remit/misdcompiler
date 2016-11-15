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
	void setLastNodeID_forLoops(int gid);
	int getLastNodeID_forLoops();
	
	void setInstructionType(low_level_instruction_type a_instructionType);
	low_level_instruction_type getInstructionType();
	void setDefinedVars(std::vector< std::string > * def_vars);
	std::vector< std::string > * getDefinedVars();
	
	void setInputNames(std::vector< std::string > * a_input_names);
	void setOutputName(std::string * a_output_name);
	std::vector< std::string > * getInputNames();
	std::string * getOutputName();

	// Visualisation
	void print();
	std::string getPicturePath();
	
	//Scopes
	void setScopesIDs(std::vector< std::string > a_scopes_ids);
	std::vector< std::string > getScopesIDs();

private:
//ATTENTION: When adding a field to a node, do not forget to add code to copy method!
	Base_AST* nodeASTSubTree; // A part of AST tree growing from this operation node
	operation_type operationType;
	int connected_node_gid; // Global ID of node from node pair (used for end condition nodes in if-then-else and loop stmts)
	int last_loop_node_gid; // Global ID of the last operation node in the body of loop
	low_level_instruction_type instructionType; // Low-level type of the instruction in this node, used to transform graph in AST
//Field only for definition nodes
	std::vector< std::string > * defined_vars;
//Data input
	std::vector< std::string > * input_names;
//Data output
	std::string * output_name;
//Scopes names in which we use current operation
	std::vector< std::string > scopes_ids;
};

#endif /* IROPERATIONNODE_H_ */
