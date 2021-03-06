/*
 * build.cpp
 *
 *  Created on: 28.08.2016
 *      Author: remit
 */

#include "../include/build.h"

VariablesTable * var_table;
StructuresTable * struct_table;

// Initializing necessary structures for repeated estimation of time
void initialize_for_repeat() {
	var_table = new VariablesTable();
	struct_table = new StructuresTable();
}

//Building assignment node
IR_OperationNode* buildAssignNode( data_type dt, std::vector< std::string > * idents_ptr, Base_AST * expr, std::vector <std::string > * scopes_ids_list, structures_proc_op_types struct_op ) {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_PROCESSING);
	std::string scope_back_id = scopes_ids_list->back();

	if(( dt == IR_DATA_SIMPLE ) || (dt == IR_DATA_TAG)) {
		op_node->setProcType(IR_CPU);
		
		if(idents_ptr->size() == 1) {
			bool * ok = new bool();

			IR_DataNode * dn = var_table->getDataNodeByVariableName((*idents_ptr)[0],ok,scopes_ids_list);
			if(dn != NULL) {
				std::string var_name = (*idents_ptr)[0] + "-" + scope_back_id;
				VariableExpr * var_assigned = new VariableExpr(var_name,dn->getSimpleType(),false);
				BinaryExpression * bin_expr = new BinaryExpression(OP_ASSIGN,var_assigned,expr);
				op_node->setNodeASTSubTree(bin_expr);
			}
		}
	} else if(dt == IR_DATA_STRUCTURE) {
		StructuresExpression * struct_processing = new StructuresExpression();
		op_node->setProcType(IR_SPU);
		struct_processing->setOperation(struct_op);
		
		if(idents_ptr->size() > 0) {
			bool * ok = new bool();
			IR_DataNode * dn = var_table->getDataNodeByVariableName((*idents_ptr)[0],ok,scopes_ids_list);
			
			if(dn == NULL) {
				
				dn = struct_table->getDataNodeByVariableName((*idents_ptr)[0],ok);
				if(dn != NULL) {
					StructureExpr * ident = NULL;
					ident = new StructureExpr((*idents_ptr)[0]);
					struct_processing->setArg1(ident);
				}
			} else {
				VariableExpr * ident = NULL;
				std::string var_name = (*idents_ptr)[0] + "-" + scope_back_id;
				ident = new VariableExpr(var_name,dn->getSimpleType(),false);
				struct_processing->setArg1(ident);
			}
		}
		if(idents_ptr->size() > 1) {
			bool * ok = new bool();
			IR_DataNode * dn = var_table->getDataNodeByVariableName((*idents_ptr)[1],ok,scopes_ids_list);
			
			if(dn == NULL) {
				dn = struct_table->getDataNodeByVariableName((*idents_ptr)[1],ok);
				if(dn != NULL) {
					StructureExpr * ident = NULL;
					ident = new StructureExpr((*idents_ptr)[1]);
					struct_processing->setArg2(ident);
				}
			} else {
				VariableExpr * ident = NULL;
				std::string var_name = (*idents_ptr)[1] + "-" + scope_back_id;
				ident = new VariableExpr(var_name,dn->getSimpleType(),false);
				struct_processing->setArg2(ident);
			}
		}
		if(idents_ptr->size() > 2) {
			bool * ok = new bool();
			IR_DataNode * dn = var_table->getDataNodeByVariableName((*idents_ptr)[2],ok,scopes_ids_list);
			
			if(dn == NULL) {
				dn = struct_table->getDataNodeByVariableName((*idents_ptr)[2],ok);
				if(dn != NULL) {
					StructureExpr * ident = NULL;
					ident = new StructureExpr((*idents_ptr)[2]);
					struct_processing->setArg3(ident);
				}
			} else {
				VariableExpr * ident = NULL;
				std::string var_name = (*idents_ptr)[2] + "-" + scope_back_id;
				ident = new VariableExpr(var_name,dn->getSimpleType(),false);
				struct_processing->setArg3(ident);
			}
		}
		
		op_node->setNodeASTSubTree(struct_processing);
	}

	return op_node;
}

//Building definition node in order to correctly transform graph to AST and then to proceed to llvm
IR_OperationNode* buildDefineNode( std::vector< std::string > * def_vars, variable_type type_of_vars, std::string scope_id) {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_DEFINITION);
	std::vector< std::string > * def_vars_full = new std::vector< std::string >;
	for(int i = 0; i < def_vars->size(); i++) {
		std::string full_def_name;
		if(scope_id.compare("") != 0)
			full_def_name = (*def_vars)[i] + "-" + scope_id;
		else
			full_def_name = (*def_vars)[i];
		def_vars_full->push_back(full_def_name);
	}
	
	op_node->setDefinedVars(def_vars_full);
	op_node->setProcType(IR_CPU);
	
	//Creating an AST node for definition
	if((def_vars_full != NULL) && (def_vars_full->size() > 0)) {
		DefineExpr * def_ast = new DefineExpr(def_vars_full, type_of_vars);
		op_node->setNodeASTSubTree(def_ast);
	}

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
IR_OperationNode* buildEndBranchNode( low_level_instruction_type llit) {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_BRANCH_END);
	op_node->setProcType(IR_BOTH);
	op_node->setInstructionType(llit);
	return op_node;
}

// Building branch node that checks some form of condition and decides which control flow will be active
IR_OperationNode* buildConditionalBeginBranchNode( LogicalExpression * le, low_level_instruction_type llit) {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_BRANCH_COND_BEGIN);
	op_node->setProcType(IR_CPU);
	op_node->setInstructionType(llit);
	
	if((llit == I_IF) || (llit == I_IF_ELSE)) {
		IfExpression * ifexpr = new IfExpression(le,NULL,NULL);
		op_node->setNodeASTSubTree(ifexpr);
	} else if(llit == I_FOR_LOOP) {
		ForLoop * forloop = new ForLoop(NULL,le,NULL,NULL);
		op_node->setNodeASTSubTree(forloop);
	} else if(llit == I_WHILE_LOOP) {
		WhileLoop * whileloop = new WhileLoop(le,NULL);
		op_node->setNodeASTSubTree(whileloop);
	}

	return op_node;
}

// Building Data Node and storing it with the variable name in the variable table
int buildDataNode(std::string identifier_name, data_type dt, int id, std::string scope_name) {
	int ret;
	std::string var_name_in_table = identifier_name + "-" + scope_name;
	bool * ok = new bool();
	int gid = var_table->getGIDbyName( var_name_in_table, ok);
	if( (* ok) != true) {
		IR_DataNode* data_node = new IR_DataNode();
		data_node->setID(id);
		data_node->setDataType(dt);
		data_node->setProcType(IR_CPU);
		data_node->setDataName(var_name_in_table);
		var_table->addVariableToTable(var_name_in_table,data_node);
		ret = 0;
	} else {
		ret = 1;
	}
	
	return ret;
}

// Updating data type of data node in variables table
void updateDataNode_SimpleDataType(std::string identifier_name, variable_type dt, std::vector <std::string > * scopes_ids_list) {
	bool* ok = new bool();
	var_table->setSimpleDataType(identifier_name,dt,ok,scopes_ids_list);
}

// Building data node for structures table
void addStructDataNodeToGraph(std::string identifier_name) {
	bool* ok  = new bool();
	struct_table->setAddedToGraph(identifier_name, ok);
}

void addVariableDataNodeToGraph(std::string identifier_name, int gid) {
	bool* ok  = new bool();
	var_table->setAddedToGraph(identifier_name, gid, ok);
}

IR_DataNode* getStructureNodeByName( std::string structure_name ) {
	bool* ok  = new bool();
	IR_DataNode* data_node = struct_table->getDataNodeByVariableName( structure_name, ok );
	return data_node;
}

IR_DataNode* getVariableNodeByName( std::string variable_name, std::vector <std::string > * scopes_ids_list ) {
	bool* ok = new bool();
	IR_DataNode* data_node = NULL;
	
	data_node = var_table->getDataNodeByVariableName( variable_name, ok, scopes_ids_list );
		
	return data_node;
}

// Getting variable type by name
data_type getIdentType( std::string variable_name, std::vector <std::string > * scopes_ids_list ) {
	bool* ok = new bool();
	data_type type_of_variable = IR_UNDEFINED;

	type_of_variable = var_table->getVarDataType( variable_name, ok, scopes_ids_list );

	return type_of_variable;
}

// Getting to know whether variable/structure is added to a graph or not.
bool isAddedToGraph(std::string identifier_name, bool * ok) {
	bool ret = false;

	bool added_as_var;
	bool * ok_var = new bool();
	added_as_var = var_table->getStatusAddedToGraph(identifier_name, ok_var);

	bool added_as_struct;
	bool * ok_struct = new bool();
	added_as_struct = struct_table->getStatusAddedToGraph(identifier_name, ok_struct);

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
	ret = var_table->getGIDbyName(identifier_name, ok);
	return ret; // must add for structs too
}

// Updating added to graph table after renumeration of nodes
void updateAddedToGraph(std::map<int,int> updateBlock) {
	var_table->updateAddedToGraph(updateBlock);
}

void printAddedToGraph() {
	var_table->printAddedToGraph();
}

//Build binary expression AST subtree
Base_AST * buildBinaryExpression(Base_AST * left, Base_AST * right, bin_op_types type_of_op) {
	BinaryExpression * binary_ast = new BinaryExpression(type_of_op, left, right);
	return binary_ast;
}

//Build unary expression AST subtree
Base_AST * buildUnaryExpression(Base_AST * ast, unary_op_types type_of_op) { 
	UnaryExpression * unary_ast = new UnaryExpression(type_of_op, ast);
	return unary_ast;
}

//Build variable (identifier)
VariableExpr * buildVariableExpr(std::string var_name, std::vector <std::string > * scopes_ids_list ) {
	bool * ok = new bool();
	IR_DataNode * dn = NULL;

	dn = var_table->getDataNodeByVariableName( var_name, ok, scopes_ids_list );

	VariableExpr * var_expr = NULL;
	if(dn != NULL)
		var_expr = new VariableExpr(dn->getDataName(),dn->getSimpleType(),false);

	return var_expr;
}

//Build number
NumberExpr * buildNumberExpr( double value, variable_type num_type ) {
	NumberExpr * num_expr = new NumberExpr(value, num_type);
	return num_expr;
}

// Build logical expression for conditions
LogicalExpression * buildLogicalExpr(Base_AST * left, Base_AST * right, cond_op_types type_of_op, std::vector< std::string > * exp_bool_vars_list) {
	LogicalExpression * logical_ast = new LogicalExpression(type_of_op,left,right,exp_bool_vars_list);
	return logical_ast;
}

// Clearing and preparing for the next iteration to estimate the time
void finish_for_repeat() {
	delete var_table;
	delete struct_table;
}