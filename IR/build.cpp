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
IR_OperationNode* buildAssignNode( data_type dt, std::vector< std::string > * idents_ptr, Base_AST * expr, std::vector <std::string > * scopes_ids_list ) {
	IR_OperationNode* op_node = NULL;
	
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_PROCESSING);

	if(( dt == IR_DATA_SIMPLE ) || (dt == IR_DATA_TAG)) {
		op_node->setProcType(IR_CPU);
		
		if(idents_ptr->size() == 1) {
			bool * ok = new bool();

			IR_DataNode * dn = var_table.getDataNodeByVariableName((*idents_ptr)[0],ok,scopes_ids_list);
			if(dn != NULL) {
				VariableExpr * var_assigned = new VariableExpr((*idents_ptr)[0],dn->getSimpleType(),false);
				BinaryExpression * bin_expr = new BinaryExpression(OP_ASSIGN,var_assigned,expr);
				op_node->setNodeASTSubTree(bin_expr);
			}
		}
	} else if(dt == IR_DATA_STRUCTURE) {
		StructuresExpression * struct_processing = new StructuresExpression();
		op_node->setProcType(IR_SPU);
		
		if(idents_ptr->size() > 0) {
			bool * ok = new bool();
			IR_DataNode * dn = var_table.getDataNodeByVariableName((*idents_ptr)[0],ok,scopes_ids_list);
			
			if(dn == NULL) {
				dn = struct_table.getDataNodeByVariableName((*idents_ptr)[0],ok);
				if(dn != NULL) {
					StructureExpr * ident = NULL;
					ident = new StructureExpr((*idents_ptr)[0]);
					struct_processing->setArg1(ident);
				}
			} else {
				VariableExpr * ident = NULL;
				ident = new VariableExpr((*idents_ptr)[0],dn->getSimpleType(),false);
				struct_processing->setArg1(ident);
			}
		}
		if(idents_ptr->size() > 1) {
			bool * ok = new bool();
			IR_DataNode * dn = var_table.getDataNodeByVariableName((*idents_ptr)[1],ok,scopes_ids_list);
			
			if(dn == NULL) {
				dn = struct_table.getDataNodeByVariableName((*idents_ptr)[1],ok);
				if(dn != NULL) {
					StructureExpr * ident = NULL;
					ident = new StructureExpr((*idents_ptr)[1]);
					struct_processing->setArg1(ident);
				}
			} else {
				VariableExpr * ident = NULL;
				ident = new VariableExpr((*idents_ptr)[1],dn->getSimpleType(),false);
				struct_processing->setArg2(ident);
			}
		}
		if(idents_ptr->size() > 2) {
			bool * ok = new bool();
			IR_DataNode * dn = var_table.getDataNodeByVariableName((*idents_ptr)[2],ok,scopes_ids_list);
			
			if(dn == NULL) {
				dn = struct_table.getDataNodeByVariableName((*idents_ptr)[2],ok);
				if(dn != NULL) {
					StructureExpr * ident = NULL;
					ident = new StructureExpr((*idents_ptr)[2]);
					struct_processing->setArg1(ident);
				}
			} else {
				VariableExpr * ident = NULL;
				ident = new VariableExpr((*idents_ptr)[2],dn->getSimpleType(),false);
				struct_processing->setArg2(ident);
			}
		}
		
		op_node->setNodeASTSubTree(struct_processing);
	}

	return op_node;
}

//Building definition node in order to correctly transform graph to AST and then to proceed to llvm
IR_OperationNode* buildDefineNode( std::vector< std::string > * def_vars, variable_type type_of_vars) {
	IR_OperationNode* op_node = NULL;
	op_node = new IR_OperationNode();
	op_node->setOperationType(IR_OP_DEFINITION);
	op_node->setDefinedVars(def_vars);
	op_node->setProcType(IR_CPU);
	
	//Creating and assigning ASTs for each declared variable
	if((def_vars != NULL) && (def_vars->size() > 0)) {
		if(def_vars->size() == 1) {
			VariableExpr * var_decl = new VariableExpr((*def_vars)[0],type_of_vars,true);
			op_node->setNodeASTSubTree(var_decl);
		} else {
			std::vector< std::string >::iterator iter;
			std::vector< std::string >::iterator iter_pre_end = --def_vars->end();
			SequenceAST * start_node = new SequenceAST();
			VariableExpr * var_decl = new VariableExpr((*def_vars)[0],type_of_vars,true);
			start_node->setLHS_E(var_decl);
			SequenceAST * prev_node = start_node;
			
			for(iter = ++def_vars->begin(); iter != iter_pre_end; iter++) {
				SequenceAST * cur_node = new SequenceAST();
				var_decl = new VariableExpr((*iter),type_of_vars,true);
				cur_node->setLHS_E(var_decl);
				prev_node->setRHS_E(cur_node);
				prev_node = cur_node;
			}
			
			// Last node
			if(iter != def_vars->end()) {
				var_decl = new VariableExpr((*iter),type_of_vars,true);
				prev_node->setRHS_E(var_decl);
			}
			
			op_node->setNodeASTSubTree(start_node);
		}
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
	int gid = var_table.getGIDbyName( var_name_in_table, ok);
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
void updateDataNode_SimpleDataType(std::string identifier_name, variable_type dt, std::vector <std::string > * scopes_ids_list) {
	bool* ok = new bool();
	var_table.setSimpleDataType(identifier_name,dt,ok,scopes_ids_list);
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
	IR_DataNode* data_node = NULL;
	
	data_node = var_table.getDataNodeByVariableName( variable_name, ok, scopes_ids_list );
		
	return data_node;
}

// Getting variable type by name
data_type getIdentType( std::string variable_name, std::vector <std::string > * scopes_ids_list ) {
	bool* ok = new bool();
	data_type type_of_variable = IR_UNDEFINED;

	type_of_variable = var_table.getVarDataType( variable_name, ok, scopes_ids_list );

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

	dn = var_table.getDataNodeByVariableName( var_name, ok, scopes_ids_list );

	VariableExpr * var_expr = NULL;
	if(dn != NULL)
		var_expr = new VariableExpr(var_name,dn->getSimpleType(),false);

	return var_expr;
}

//Build number
NumberExpr * buildNumberExpr( double value ) {
	NumberExpr * num_expr = new NumberExpr(value);
	return num_expr;
}

// Build logical expression for conditions
LogicalExpression * buildLogicalExpr(Base_AST * left, Base_AST * right, cond_op_types type_of_op) {
	LogicalExpression * logical_ast = new LogicalExpression(type_of_op,left,right);
	return logical_ast;
}
