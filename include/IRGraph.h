/*
 * IRGraph.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IRGRAPH_H_
#define IRGRAPH_H_

#include <iostream>
#include <fstream>

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
	int getStartTerminalNodeID();

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

	// Visualising a graph using cytospace
	void visualise(std::string full_filename);
	void calculate_coords();// Calculating coordinates in order to correctly output a graph

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

	std::map< int, int > x_coords;// X coordinates of all graph nodes (gid - key)
	std::map< int, int > y_coords;// Y coordinates of all graph nodes (gid - key)
	std::map< int, int > y_levels;// Level of hierarchy of a node in graph (topmost - 0)
	std::map< int, int > x_levels;// Level of hierarchy of a node in graph (leftmost - 0)
	std::map< int, int > max_level_by_loop;

	void range_nodes_by_y(int dep_node, int cur_level);
	void range_nodes_by_x(int dep_node, int cur_level);
	int calculate_num_of_branch_nodes(int node_id, int br_id);
	std::vector< int > considered_branch_nodes;
	std::vector< int > branch_nodes_search_stack;

	// Methods needed to append graphs
	IR_OperationNode* getOperation(int index);
	IR_DataNode* getData(int index);
	int getConnectionSrc(int index);
	int getConnectionDst(int index);
	
};

#endif /* IRGRAPH_H_ */
