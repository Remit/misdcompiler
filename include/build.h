/*
 * build.h
 *
 *  Created on: 28.08.2016
 *      Author: remit
 */

#ifndef BUILD_H_
#define BUILD_H_

#ifndef IRGRAPH_H_
#include "IRGraph.h"
#endif

#ifndef VARIABLESTABLE_H_
#include "VariablesTable.h"
#endif

#ifndef STRUCTURESTABLE_H_
#include "StructuresTable.h"
#endif

IR_OperationNode* buildAssignNode( data_type dt );
IR_OperationNode* buildTerminalNode();
IR_OperationNode* buildBeginBranchNode();
IR_OperationNode* buildEndBranchNode();
IR_OperationNode* buildConditionalBeginBranchNode();
IR_DataNode* getStructureNodeByName( std::string structure_name );
IR_DataNode* getVariableNodeByName( std::string variable_name );
data_type getIdentType( std::string variable_name );

void buildDataNode(std::string identifier_name, proc_type p_type, data_type dt);
void updateDataNode_SimpleDataType(std::string identifier_name, int dt);
void addStructDataNodeToGraph(std::string identifier_name);
void addVariableDataNodeToGraph(std::string identifier_name, int gid);
bool isAddedToGraph(std::string identifier_name, bool * ok);
int identNameToGID(std::string identifier_name);

#endif /* BUILD_H_ */
