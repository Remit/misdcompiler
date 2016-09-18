/*
 * VariablesTable.h
 *
 *  Created on: 30.08.2016
 *      Author: remit
 */

#ifndef VARIABLESTABLE_H_
#define VARIABLESTABLE_H_

#ifndef IRDATANODE_H_
#include "IRDataNode.h"
#endif

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

class VariablesTable {
public:
	VariablesTable();
	virtual ~VariablesTable();
	void addVariableToTable( std::string variable_name, IR_DataNode* data_node );
	int assignValueToVariable( std::string variable_name, int value );
	void setDataType( std::string variable_name, data_type dt, bool* ok );
	void setSimpleDataType( std::string variable_name, int dt, bool* ok );

	float getVariableValue( std::string variable_name, bool* ok );
	data_type getVarDataType( std::string variable_name, bool* ok );
	IR_DataNode* getDataNodeByVariableName( std::string variable_name, bool* ok );
	void setAddedToGraph( std::string variable_name, int gid, bool* ok );
	void unsetAddedToGraph( std::string variable_name, bool* ok );
	bool getStatusAddedToGraph( std::string variable_name, bool* ok );
	int getGIDbyName( std::string variable_name, bool* ok );
	void print();

private:
	std::map< std::string, float > values;
	std::map< std::string, bool > initialized;
	std::map< std::string, int > added_to_graph;
	std::map< std::string, IR_DataNode* > data_nodes;
};

#endif /* VARIABLESTABLE_H_ */
