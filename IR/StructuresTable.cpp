/*
 * StructuresTable.cpp
 *
 *  Created on: 03.09.2016
 *      Author: remit
 */

#include "../include/StructuresTable.h"
#include <sstream>

StructuresTable::StructuresTable() {
	// The number of structures is constant, so we initialize them simultaneously.
	// Structures can be erased by deleting data from SPU mem (or disassigning pointer to a certain structure in SPU mem).
	// Structures can be modified using external data. The format of the data must be provided beforehand.
	std::ostringstream stream_for_string;
	for(int i = 1; i <= num_of_structures_for_usage; i++ ) {
		IR_DataNode* data_node = new IR_DataNode();
		data_node->setDataType(IR_DATA_STRUCTURE);
		data_node->setProcType(IR_SPU);
		stream_for_string << i;
		std::string converted_num(stream_for_string.str());
		std::string structure_name = "STRUCT" + converted_num;
		initialized[structure_name] = false;
		data_nodes[structure_name] = data_node;
		added_to_graph[structure_name] = false;
	}
}

StructuresTable::~StructuresTable() {
	// TODO Auto-generated destructor stub
}

void StructuresTable::InitializeStructureWithData() {
	//Need to provide a mechanism to convert the data from some typical form into SPU processed form
}

IR_DataNode* StructuresTable::getDataNodeByVariableName( std::string structure_name, bool* ok ) {
	IR_DataNode* ret = NULL;
	std::map< std::string, IR_DataNode* >::iterator it;
	it = data_nodes.find(structure_name);
	if( it == data_nodes.end())
		*ok = false;
	else {
		ret = it->second;
		*ok = true;
	}

	return ret;
}

bool StructuresTable::isAddedToGraph( std::string structure_name, bool* ok ) {
	bool ret = false;
	std::map< std::string, bool >::iterator it;
	it = added_to_graph.find(structure_name);
	if( it == added_to_graph.end())
		*ok = false;
	else {
		ret = it->second;
		*ok = true;
	}

	return ret;
}

void StructuresTable::setAddedToGraph( std::string structure_name, bool* ok ) {
	std::map< std::string, bool >::iterator it;
	it = added_to_graph.find(structure_name);
	if( it == added_to_graph.end())
		*ok = false;
	else {
		added_to_graph[structure_name] = true;
		*ok = true;
	}
}

void StructuresTable::unsetAddedToGraph( std::string structure_name, bool* ok ) {
	std::map< std::string, bool >::iterator it;
	it = added_to_graph.find(structure_name);
	if( it == added_to_graph.end())
		*ok = false;
	else {
		added_to_graph[structure_name] = false;
		*ok = true;
	}
}
