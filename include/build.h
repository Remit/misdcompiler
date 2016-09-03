/*
 * build.h
 *
 *  Created on: 28.08.2016
 *      Author: remit
 */

#ifndef BUILD_H_
#define BUILD_H_

#include "IRGraph.h"
#include "VariablesTable.h"
#include "StructuresTable.h"

IR_Graph programGraph;
VariablesTable var_table;
StructuresTable struct_table;

IR_OperationNode* buildAssignNode( data_type dt );
IR_OperationNode* buildTerminalNode();
IR_OperationNode* buildBeginBranchNode();
IR_OperationNode* buildEndBranchNode();
IR_OperationNode* buildConditionalBeginBranchNode();
IR_DataNode* getStructureNodeByName( std::string structure_name );
IR_DataNode* getVariableNodeByName( std::string variable_name );

void buildDataNode(std::string identifier_name, proc_type p_type);
void updateDataNode_DataType(std::string identifier_name, data_type dt);
void addStructDataNodeToGraph(std::string identifier_name);

#endif /* BUILD_H_ */
