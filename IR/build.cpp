/*
 * build.cpp
 *
 *  Created on: 28.08.2016
 *      Author: remit
 */

#include "../include/build.h"

VariablesTable var_table;
StructuresTable struct_table;

//Building assignment node
IR_OperationNode* buildAssignNode( data_type dt ) {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_PROCESSING);
	if(( dt == IR_DATA_SIMPLE ) || (dt == IR_DATA_TAG))
		op_node->setProcType(IR_CPU);
	else if(dt == IR_DATA_STRUCTURE)
		op_node->setProcType(IR_SPU);

	return op_node;
}

//Building terminal node
IR_OperationNode* buildTerminalNode() {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_TERMINATOR);
	op_node->setProcType(IR_BOTH);
	return op_node;
}

// Building branch node that begins the sequence of alternatives (without explicit conditioning)
IR_OperationNode* buildBeginBranchNode() {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_BRANCH_BEGIN);
	op_node->setProcType(IR_BOTH);
	return op_node;
}

// Building branch node that ends the sequence of alternative control flows
IR_OperationNode* buildEndBranchNode() {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_BRANCH_END);
	op_node->setProcType(IR_BOTH);
	return op_node;
}

// Building branch node that checks some form of condition and decides which control flow will be active
IR_OperationNode* buildConditionalBeginBranchNode() {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_BRANCH_COND_BEGIN);
	op_node->setProcType(IR_CPU);
	return op_node;
}

// Building Data Node and storing it with the variable name in the variable table
void buildDataNode(std::string identifier_name, proc_type p_type, data_type dt) {
	IR_DataNode* data_node = new IR_DataNode();
	data_node->setDataType(dt);
	data_node->setProcType(p_type);
	var_table.addVariableToTable(identifier_name,data_node);
}

// Updating data type of data node in variables table
void updateDataNode_SimpleDataType(std::string identifier_name, int dt) {
	bool* ok;
	var_table.setSimpleDataType(identifier_name,dt,ok);
}

// Building data node for structures table
void addStructDataNodeToGraph(std::string identifier_name) {
	bool* ok;
	struct_table.setAddedToGraph(identifier_name, ok);
}

IR_DataNode* getStructureNodeByName( std::string structure_name ) {
	bool* ok;
	IR_DataNode* data_node = struct_table.getDataNodeByVariableName( structure_name, ok );
	return data_node;
}

IR_DataNode* getVariableNodeByName( std::string variable_name ) {
	bool* ok;
	IR_DataNode* data_node = var_table.getDataNodeByVariableName( variable_name, ok );
	return data_node;
}

// Getting variable type by name
data_type getIdentType( std::string variable_name ) {
	bool* ok;
	data_type type_of_variable = var_table.getVarDataType(variable_name, ok);
	return type_of_variable;
}
