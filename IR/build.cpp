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

//Building definition node in order to correctly transform graph to AST and then to proceed to llvm
IR_OperationNode* buildDefineNode( std::vector< std::string > * def_vars) {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_DEFINITION);
	op_node->setDefinedVars(def_vars);
	op_node->setProcType(IR_CPU);
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
int buildDataNode(std::string identifier_name, data_type dt, int id, std::string scope_name) {
	int ret;
	std::string var_name_in_table = identifier_name + "-" + scope_name;
	bool * ok = new bool();
	int gid = var_table.getGIDbyName( var_name_in_table, ok );
	if( (* ok) != true) {
		IR_DataNode* data_node = new IR_DataNode();
		data_node->setID(id);
		data_node->setDataType(dt);
		data_node->setProcType(IR_CPU);
		data_node->setDataName(var_name_in_table);
		var_table.addVariableToTable(var_name_in_table,data_node);
		ret = 0;
	} else {
		ret = 1;
	}
	
	return ret;
}

// Updating data type of data node in variables table
void updateDataNode_SimpleDataType(std::string identifier_name, int dt) {
	bool* ok = new bool();
	var_table.setSimpleDataType(identifier_name,dt,ok);
}

// Building data node for structures table
void addStructDataNodeToGraph(std::string identifier_name) {
	bool* ok  = new bool();
	struct_table.setAddedToGraph(identifier_name, ok);
}

void addVariableDataNodeToGraph(std::string identifier_name, int gid) {
	bool* ok  = new bool();
	var_table.setAddedToGraph(identifier_name, gid, ok);
}

IR_DataNode* getStructureNodeByName( std::string structure_name ) {
	bool* ok  = new bool();
	IR_DataNode* data_node = struct_table.getDataNodeByVariableName( structure_name, ok );
	return data_node;
}

IR_DataNode* getVariableNodeByName( std::string variable_name, std::vector <std::string > * scopes_ids_list ) {
	bool* ok = new bool();
	bool found = false;
	IR_DataNode* data_node = NULL;
	
	while(!found && (scopes_ids_list->size() > 0)) {
		std::string last_scope_id = scopes_ids_list->back();
		std::string variable_name_with_scope_id = variable_name + "-" + last_scope_id;
		scopes_ids_list->pop_back();
		data_node = var_table.getDataNodeByVariableName( variable_name_with_scope_id, ok );
		if((*ok))
			found = true;
	}
		
	return data_node;
}

// Getting variable type by name
data_type getIdentType( std::string variable_name ) {
	bool* ok = new bool();
	data_type type_of_variable = var_table.getVarDataType(variable_name, ok);
	return type_of_variable;
}

// Getting to know whether variable/structure is added to a graph or not.
bool isAddedToGraph(std::string identifier_name, bool * ok) {
	bool ret = false;

	bool added_as_var;
	bool * ok_var = new bool();
	added_as_var = var_table.getStatusAddedToGraph(identifier_name, ok_var);

	bool added_as_struct;
	bool * ok_struct = new bool();
	added_as_struct = struct_table.getStatusAddedToGraph(identifier_name, ok_struct);

	if( ((* ok_var) == false) && ((* ok_struct) == false) )
		(* ok) = false;
	else {
		(* ok) = true;
		if( ((* ok_struct) == true) )
			ret = added_as_struct;
		else
			ret = added_as_var;
	}

	return ret;
}

int identNameToGID(std::string identifier_name) {
	int ret;
	bool* ok = new bool();
	ret = var_table.getGIDbyName(identifier_name, ok);
	return ret; // must add for structs too
}

// Updating added to graph table after renumeration of nodes
void updateAddedToGraph(std::map<int,int> updateBlock) {
	var_table.updateAddedToGraph(updateBlock);
}

void printAddedToGraph() {
	var_table.printAddedToGraph();
}
