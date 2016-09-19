/*
 * VariablesTable.cpp
 *
 *  Created on: 30.08.2016
 *      Author: remit
 */

#include "../include/VariablesTable.h"

VariablesTable::VariablesTable() {
	// TODO Auto-generated constructor stub

}

VariablesTable::~VariablesTable() {
	// TODO Auto-generated destructor stub
}

void VariablesTable::addVariableToTable( std::string variable_name, IR_DataNode* data_node ) {
	std::map< std::string, float >::iterator it;
	it = values.find(variable_name);
	if( it == values.end()) {
		values[variable_name] = 0;
		initialized[variable_name] = false;
		added_to_graph[variable_name] = -1;
		data_nodes[variable_name] = data_node;
	}
}

int VariablesTable::assignValueToVariable( std::string variable_name, int value ) {
	int ret = 0; // 0 - no errors; there is such variable in the table
	std::map< std::string, float >::iterator it;
	it = values.find(variable_name);
	if( it == values.end())
		ret = 1; // 1 - error, no such variable in the table
	else {
		values[variable_name] = value;
		initialized[variable_name] = true;
	}

	return ret;
}

float VariablesTable::getVariableValue( std::string variable_name, bool* ok ) {
	float ret = 0.0;
	std::map< std::string, float >::iterator it;
	it = values.find(variable_name);
	if( it == values.end())
		*ok = false;
	else {
		std::map< std::string, bool >::iterator it_init;
		it_init = initialized.find(variable_name);
		if(!it_init->second)
			*ok = false;
		else {
			ret = it->second;
			*ok = true;
		}
	}

	return ret;
}

data_type VariablesTable::getVarDataType( std::string variable_name, bool* ok ) {
	IR_DataNode* node = NULL;
	data_type ret;
	std::map< std::string, IR_DataNode* >::iterator it;
	it = data_nodes.find(variable_name);
	if( it == data_nodes.end())
	{
		*ok = false;
		ret = IR_UNDEFINED;
	}
	else {
		node = it->second;
		ret = node->getDataType();
		*ok = true;
	}

	return ret;
}

IR_DataNode* VariablesTable::getDataNodeByVariableName( std::string variable_name, bool* ok ) {
	IR_DataNode* ret = NULL;
	std::map< std::string, IR_DataNode* >::iterator it;
	it = data_nodes.find(variable_name);
	if( it == data_nodes.end())
		*ok = false;
	else {
		ret = it->second;
		*ok = true;
	}

	return ret;
}

void VariablesTable::setDataType( std::string variable_name, data_type dt, bool* ok ) {
	std::map< std::string, IR_DataNode* >::iterator it;
	it = data_nodes.find(variable_name);
	if( it == data_nodes.end())
		*ok = false;
	else {
		it->second->setDataType(dt);
		*ok = true;
	}
}

void VariablesTable::setSimpleDataType( std::string variable_name, int dt, bool* ok ) {
	std::map< std::string, IR_DataNode* >::iterator it;
	it = data_nodes.find(variable_name);
	if( it == data_nodes.end())
		*ok = false;
	else {
		it->second->setSimpleType(dt);
		*ok = true;
	}
}

void VariablesTable::setAddedToGraph( std::string variable_name, int gid, bool* ok ) {
	std::map< std::string, int >::iterator it;
	it = added_to_graph.find(variable_name);
	if( it == added_to_graph.end())
		*ok = false;
	else {
		added_to_graph[variable_name] = gid;
		*ok = true;
	}
}

void VariablesTable::unsetAddedToGraph( std::string variable_name, bool* ok ) {
	std::map< std::string, int >::iterator it;
	it = added_to_graph.find(variable_name);
	if( it == added_to_graph.end())
		*ok = false;
	else {
		added_to_graph[variable_name] = -1;
		*ok = true;
	}
}

void VariablesTable::print() {
	std::map< std::string, IR_DataNode* >::iterator it = data_nodes.begin();
	while(it != data_nodes.end()) {
		std::cout << it->first << std::endl;
		it++;
	}
}

void VariablesTable::printAddedToGraph() {
	std::map<std::string,int>::iterator it;
	for(it = added_to_graph.begin(); it != added_to_graph.end(); it++) {
		std::cout << it->first << " - " << it->second << std::endl;
	}
}

bool VariablesTable::getStatusAddedToGraph( std::string variable_name, bool* ok ) {
	std::map< std::string, int >::iterator it;
	bool ret = false;
	it = added_to_graph.find(variable_name);
	if( it == added_to_graph.end())
		*ok = false;
	else {
		if(added_to_graph[variable_name] > 0)
			ret = true;
		else
			ret = false;
		*ok = true;
	}

	return ret;
}

int VariablesTable::getGIDbyName( std::string variable_name, bool* ok ) {
	std::map< std::string, int >::iterator it;
	int ret = -1;
	it = added_to_graph.find(variable_name);
	if( it == added_to_graph.end())
		*ok = false;
	else {
		ret = added_to_graph[variable_name];
		*ok = true;
	}

	return ret;
}

void VariablesTable::updateAddedToGraph(std::map<int,int> updateBlock) {
	std::map<int,int>::iterator it;
	std::map<std::string,int>::iterator it_added;
	for (it = updateBlock.begin(); it != updateBlock.end(); ++it ) {
		int old_id = it->first;
		int new_id = it->second;
		bool found = false;
		it_added = added_to_graph.begin();
		while( (it_added != added_to_graph.end()) && !found ) {
			int added_old_id = it_added->second;

			if(old_id == added_old_id) {
				std::string key = it_added->first;
				added_to_graph[key] = new_id;
				found = true;
			}

			++it_added;
		}
	}
}
