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
	void appendGraph( IR_Graph* appendedGraph );
	void appendGraph( IR_Graph* appendedGraph, int src_node );
	void setClean( bool full_clean );

	void removeNode( int id );
	void removeConnection( int id_src, int id_dst );

	IR_Node* getNode(int id);
	IR_Node* getFirstNode();
	int getLastOperationID();
	int getLastDataID();
	int getFirstOperationID();

	std::vector< IR_Node* > getAdjacentNodes(int id);
	std::vector< IR_Node* > getAdjacentDataNodes(int id);
	std::vector< IR_Node* > getAdjacentOperationNodes(int id);

	// Methods needed to append graphs
	int getNumOfOperations();
	int getNumOfData();
	int getNumOfConnections();
	IR_OperationNode* getOperation(int index);
	IR_DataNode* getData(int index);
	int getConnectionSrc(int index);
	int getConnectionDst(int index);

private:
	std::vector< IR_OperationNode* > operations;
	std::vector< IR_DataNode* > data;
	std::multimap< int, int > connections;
	std::map< int, int > operations_index; // Index of operations nodes; key - global id, value - position in operations vector
	std::map< int, int > data_index; // Index of data nodes; key - global id, value - position in data vector
	int last_id;
	int num_of_reserve_data;
	int num_of_reserve_operations;
	bool full_clean;// Controlling the destructor's behavior; true - destroy nodes too (normal state); false - destroy everything except for nodes
};

#endif /* IRGRAPH_H_ */
