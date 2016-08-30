/*
 * build.cpp
 *
 *  Created on: 28.08.2016
 *      Author: remit
 */

#include "build.h"

//Building assignment node
void buildAssignNode( data_type dt ) {
	int id_src = programGraph.getLastOperationID();
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_PROCESSING);
	if(( dt == IR_DATA_SIMPLE ) || (dt == IR_DATA_TAG))
		op_node->setProcType(IR_CPU);
	else if(dt == IR_DATA_STRUCTURE)
		op_node->setProcType(IR_SPU);

	programGraph.addOperationNode(op_node);
	int id_dst = programGraph.getLastOperationID();
	programGraph.addConnection(id_src,id_dst);
}

//Building terminal node
IR_OperationNode* buildTerminalNode() {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_TERMINATOR);
	op_node->setProcType(IR_BOTH);
	return op_node;
}

// Building Data Node and storing it with the variable name in the variable table
void buildDataNode(std::string identifier_name, proc_type p_type) {
	IR_DataNode* data_node = new IR_DataNode();
	data_node->setProcType(p_type);
	var_table.addVariableToTable(identifier_name,data_node);
}

// Updating data type of data node in variables table
void updateDataNode_DataType(std::string identifier_name, data_type dt) {
	bool* ok;
	var_table.setDataType(identifier_name,dt,ok);
}
