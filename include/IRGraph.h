/*
 * IRGraph.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IRGRAPH_H_
#define IRGRAPH_H_

#include "IROperationNode.h"
#include "IRDataNode.h"
#include <map>

size_t initial_size = 1000;

class IR_Graph {
public:
	IR_Graph();
	virtual ~IR_Graph();

	void addOperationNode( IR_OperationNode* );
	void addDataNode( IR_DataNode* );
	void addConnection( int id_src, int id_dst );

	void removeNode( int id );
	void removeConnection( int id_src, int id_dst );

	IR_Node* getNode(int id);
	IR_Node* getFirstNode();
	std::vector< IR_Node* > getAdjacentNodes(int id);
	std::vector< IR_Node* > getAdjacentDataNodes(int id);
	std::vector< IR_Node* > getAdjacentOperationNodes(int id);

private:
	std::vector< IR_OperationNode* > operations;
	std::vector< IR_DataNode* > data;
	std::multimap< int, int > connections;
	std::map< int, int > operations_index; // Index of operations nodes; key - global id, value - position in operations vector
	std::map< int, int > data_index; // Index of data nodes; key - global id, value - position in data vector
	int last_id;
	int num_of_reserve_data;
	int num_of_reserve_operations;
};

#endif /* IRGRAPH_H_ */
