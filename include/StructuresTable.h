/*
 * StructuresTable.h
 *
 *  Created on: 03.09.2016
 *      Author: remit
 */

#ifndef STRUCTURESTABLE_H_
#define STRUCTURESTABLE_H_

#ifndef IRDATANODE_H_
#include "IRDataNode.h"
#endif

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

class StructuresTable {
public:
	StructuresTable();
	virtual ~StructuresTable();
	void InitializeStructureWithData();
	IR_DataNode* getDataNodeByVariableName( std::string structure_name, bool* ok );
	bool isAddedToGraph( std::string structure_name, bool* ok );
	void setAddedToGraph( std::string structure_name, bool* ok );
	void unsetAddedToGraph( std::string structure_name, bool* ok );
	bool getStatusAddedToGraph( std::string structure_name, bool* ok );

private:
	//We should define here some kind of pointer to a structure in SPU mem.
	std::map< std::string, bool > initialized;
	std::map< std::string, bool > added_to_graph;
	std::map< std::string, IR_DataNode* > data_nodes;
};

#endif /* STRUCTURESTABLE_H_ */
