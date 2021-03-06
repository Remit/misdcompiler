/*
 * build.h
 *
 *  Created on: 28.08.2016
 *      Author: remit
 */

#ifndef BUILD_H_
#define BUILD_H_

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef IRGRAPH_H_
#include "IRGraph.h"
#endif

#ifndef VARIABLEEXPR_H
#include "VariableExpr.h"
#endif

#ifndef NUMBEREXPR_H
#include "NumberExpr.h"
#endif

#ifndef STRUCTUREEXPR_H
#include "StructureExpr.h"
#endif

#ifndef STRUCTURESEXPRESSION_H
#include "StructuresExpression.h"
#endif

#ifndef SEQUENCEAST_H
#include "SequenceAST.h"
#endif

#ifndef BINARYEXPRESSION_H
#include "BinaryExpression.h"
#endif

#ifndef LOGICALEXPRESSION_H
#include "LogicalExpression.h"
#endif

#ifndef UNARYEXPRESSION_H
#include "UnaryExpression.h"
#endif

#ifndef VARIABLESTABLE_H_
#include "VariablesTable.h"
#endif

#ifndef STRUCTURESTABLE_H_
#include "StructuresTable.h"
#endif

#ifndef IFEXPRESSION_H_
#include "IfExpression.h"
#endif

#ifndef WHILELOOP_H_
#include "WhileLoop.h"
#endif

#ifndef FORLOOP_H_
#include "ForLoop.h"
#endif

#ifndef DEFINEEXPR_H_
#include "DefineExpr.h"
#endif

IR_OperationNode* buildAssignNode( data_type dt, std::vector< std::string > * idents_ptr, Base_AST * expr, std::vector <std::string > * scopes_ids_list, structures_proc_op_types struct_op );
IR_OperationNode* buildDefineNode( std::vector< std::string > * def_vars, variable_type type_of_vars, std::string scope_id);
IR_OperationNode* buildTerminalNode();
IR_OperationNode* buildBeginBranchNode();
IR_OperationNode* buildEndBranchNode( low_level_instruction_type llit );
IR_OperationNode* buildConditionalBeginBranchNode( LogicalExpression * le, low_level_instruction_type llit);
IR_DataNode* getStructureNodeByName( std::string structure_name );
IR_DataNode* getVariableNodeByName( std::string variable_name, std::vector <std::string > * scopes_ids_list );
data_type getIdentType( std::string variable_name, std::vector <std::string > * scopes_ids_list );
Base_AST * buildBinaryExpression(Base_AST * left, Base_AST * right, bin_op_types type_of_op);
Base_AST * buildUnaryExpression(Base_AST * ast, unary_op_types type_of_op);
VariableExpr * buildVariableExpr(std::string var_name, std::vector <std::string > * scopes_ids_list);
NumberExpr * buildNumberExpr( double value, variable_type num_type );
LogicalExpression * buildLogicalExpr(Base_AST * left, Base_AST * right, cond_op_types type_of_op, std::vector< std::string > * exp_bool_vars_list );

int buildDataNode(std::string identifier_name, data_type dt, int id, std::string scope_name);
void updateDataNode_SimpleDataType(std::string identifier_name, variable_type dt, std::vector <std::string > * scopes_ids_list);
void addStructDataNodeToGraph(std::string identifier_name);
void addVariableDataNodeToGraph(std::string identifier_name, int gid);
bool isAddedToGraph(std::string identifier_name, bool * ok);
int identNameToGID(std::string identifier_name);
void updateAddedToGraph(std::map<int,int> updateBlock);
void printAddedToGraph();
void finish_for_repeat();
void initialize_for_repeat();

#endif /* BUILD_H_ */
