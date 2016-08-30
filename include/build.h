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

IR_Graph programGraph;
VariablesTable var_table;

void buildAssignNode( data_type dt );
IR_OperationNode* buildTerminalNode();
void buildBeginBranchNode();
void buildEndBranchNode();
void buildConditionalBeginBranchNode();
void buildSendNode();
void buildReceiveNode();

void buildDataNode(std::string identifier_name, proc_type p_type);
void updateDataNode_DataType(std::string identifier_name, data_type dt);

#endif /* BUILD_H_ */
