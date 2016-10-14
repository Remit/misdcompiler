/*
 * IRGraph.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IRGRAPH_H_
#define IRGRAPH_H_

#ifndef IROPERATIONNODE_H_
#include "IROperationNode.h"
#endif

#ifndef IRDATANODE_H_
#include "IRDataNode.h"
#endif

#define initial_size 1000

class IR_Graph {
public:
	IR_Graph();
	virtual ~IR_Graph();

	void addOperationNode( IR_OperationNode* node);
	void addDataNode( IR_DataNode* node);
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

	std::vector< int > * getDependentOperationNodes(int id);
	std::vector< int > * getDependentDataNodes(int id);
	std::vector< int > * getIncomingOperationNodes(int id);
	std::vector< int > * getIncomingDataNodes(int id);
	std::vector< int > * getOperationNodesIDs();
	std::vector< int > * getDataNodesIDs();

	int getNumOfOperations();
	int getNumOfData();
	int getNumOfConnections();
	int getLastID();

	// Methods to output graphs for the purpose of check
	void printConnections();
	void printNodes();

	// Methods to copy graph
	void copyGraph(IR_Graph* copiedGraph);
	IR_OperationNode* getOperationCopy(int index);
	IR_DataNode* getDataCopy(int index);

private:
	std::vector< IR_OperationNode* > operations;
	std::vector< IR_DataNode* > data;
	std::multimap< int, int > connections;
	std::map< int, int > operations_index; // Index of operations nodes; key - global id, value - position in operations vector
	std::map< int, int > data_index; // Index of data nodes; key - global id, value - position in data vector
	int num_of_reserve_data;
	int num_of_reserve_operations;
	int last_operation_id;
	int last_data_id;
	bool full_clean;// Controlling the destructor's behavior; true - destroy nodes too (normal state); false - destroy everything except for nodes

	// Methods needed to append graphs
	IR_OperationNode* getOperation(int index);
	IR_DataNode* getData(int index);
	int getConnectionSrc(int index);
	int getConnectionDst(int index);
};

#endif /* IRGRAPH_H_ */
