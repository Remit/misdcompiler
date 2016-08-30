/*
 * IRGraph.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "IRGraph.h"

IR_Graph::IR_Graph() {
	operations.reserve(initial_size);
	data.reserve(initial_size);
	last_id = 0;
	num_of_reserve_data = 1;
	num_of_reserve_operations = 1;
	full_clean = true;
}

IR_Graph::~IR_Graph() {
	if(full_clean) {
		int num_of_ops = operations.size();
		for(int i = 0; i < num_of_ops; i++)
			delete operations[i];

		int num_of_datas = data.size();
		for(int i = 0; i < num_of_datas; i++)
			delete data[i];
	}
}

void IR_Graph::addOperationNode(IR_OperationNode* a_OperationNode) {
	if( a_OperationNode != NULL ) {
		// Increasing memory for nodes if needed
		int current_num_of_ops = operations.size();
		if(current_num_of_ops == num_of_reserve_operations * initial_size) {
			num_of_reserve_operations++;
			operations.reserve(num_of_reserve_operations * initial_size);
		}

		last_id++;
		a_OperationNode->setID(last_id);
		operations.push_back(a_OperationNode);
		operations_index[last_id] = operations.size() - 1;
	}
}

void IR_Graph::addDataNode(IR_DataNode* a_DataNode) { //Needs update to preserve a logic of one data node per one data declaration
	if( a_DataNode != NULL ) {
		// Increasing memory for nodes if needed
		int current_num_of_datas = data.size();
		if(current_num_of_datas == num_of_reserve_data * initial_size) {
			num_of_reserve_data++;
			data.reserve(num_of_reserve_data * initial_size);
		}

		last_id++;
		a_DataNode->setID(last_id);
		data.push_back(a_DataNode);
		data_index[last_id] = data.size() - 1;
	}
}

void IR_Graph::addConnection(int id_src, int id_dst) {
	// Checking whether connection is already in the table.
	// Adding connection if it is not in the connection table.

	std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
	range_found = connections.equal_range(id_src);
	if(range_found.first != range_found.second) {
		std::multimap<int,int>::iterator iter = range_found.first;
		std::multimap<int,int>::iterator end = range_found.second;
		bool connection_found = false;

		while( (connection_found == false) || (iter != end) ) {
			if(iter->second == id_dst)
				connection_found = true;
			++iter;
		}

		if(!connection_found)
			connections[id_src] = id_dst;
	}
}

void IR_Graph::removeNode(int a_id) {
	std::map<int,int>::iterator it;
	it = operations_index.find(a_id);
	bool node_found = false;
	if( it == operations_index.end()) {
		it = data_index.find(a_id);
		// Deleting an element from data vertices in case a_id is a global id for data node
		if(it != data_index.end()){
			node_found = true;
			data_index.erase(a_id);
			int pos = it->second;
			delete data[pos];
			data.erase(data.begin() + pos);
		}
	} else {// Deleting an element from operations vertices in case a_id is a global id for operation node
		node_found = true;
		operations_index.erase(a_id);
		int pos = it->second;
		delete operations[pos];
		operations.erase(operations.begin() + pos);
	}

	if(node_found) { // Removing connections
		// Removing connections - direct order
		removeConnection(a_id,-1);
		// Removing connections - inverse order
		removeConnection(-1,a_id);
	}
}

void IR_Graph::removeConnection(int id_src, int id_dst) {
	if( (id_src == -1) && (id_dst > -1) ) { // Removing all connections terminated at id_dst
		for(std::multimap<int,int>::iterator it = connections.begin(); it != connections.end();) {
			if(it->second == id_dst) {
				std::multimap<int,int>::iterator tmp = it;
				++tmp;
				connections.erase(it);
				it = tmp;
			} else {
				++it;
			}
		}
	} else if( (id_src > -1) && (id_dst == -1) ) { // Removing all connections beginning at id_src
		std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
		range_found = connections.equal_range(id_src);
		if(range_found.first != range_found.second) {
			std::multimap<int,int>::iterator begin_range = range_found.first;
			std::multimap<int,int>::iterator end_range = range_found.second;
			connections.erase(begin_range,end_range);
		}
	} else if( (id_src == -1) && (id_dst == -1)) { // Removing all connections
		std::multimap<int,int>::iterator it = connections.begin();
		while(it != connections.end()) {
			std::multimap<int,int>::iterator tmp = it;
			++tmp;
			connections.erase(it);
			it = tmp;
		}
	} else if( (id_src > -1) && (id_dst > -1)) { // Removing single connection from id_src to id_dst
		std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
		range_found = connections.equal_range(id_src);
		if(range_found.first != range_found.second) {
			std::multimap<int,int>::iterator iter = range_found.first;
			std::multimap<int,int>::iterator end = range_found.second;
			bool connection_found = false;

			while( (connection_found == false) || (iter != end) ) {
				if(iter->second == id_dst) {
					connection_found = true;
					connections.erase(iter);
				}
				++iter;
			}
		}
	}
}

IR_Node* IR_Graph::getNode(int a_id) {
	std::map<char,int>::iterator it;
	it = operations_index.find(a_id);
	IR_Node* ret_node;
	if( it == operations_index.end()) {
			it = data_index.find(a_id);
			if(it != data_index.end()) {
				int pos = it->second;
				ret_node = data[pos];
			}
	} else {
		int pos = it->second;
		ret_node = operations[pos];
	}

	return ret_node;
}

IR_Node* IR_Graph::getFirstNode() {
	IR_Node* first_node;
	if(operations.size() > 0) {
		std::vector<IR_OperationNode*>::iterator it = operations.begin();
		first_node = *it;
	}

	return first_node;
}

std::vector< IR_Node* > IR_Graph::getAdjacentNodes(int id) {
	std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
	range_found = connections.equal_range(id);
	std::vector< IR_Node* > adjacentNodes_ls;

	if(range_found.first != range_found.second) {
		std::multimap<int,int>::iterator iter = range_found.first;
		std::multimap<int,int>::iterator end = range_found.second;
		int num_of_adj_nodes = end - iter + 1;
		adjacentNodes_ls.reserve(num_of_adj_nodes);

		while(iter != end) {
			int adj_node_id = iter->second;
			IR_Node* adj_node = getNode(adj_node_id);
			adjacentNodes_ls.push_back(adj_node);
			++iter;
		}
	}

	return adjacentNodes_ls;
}

std::vector< IR_Node* > IR_Graph::getAdjacentDataNodes(int id) {
	std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
	range_found = connections.equal_range(id);
	std::vector< IR_Node* > adjacentNodes_ls;

	if(range_found.first != range_found.second) {
		std::multimap<int,int>::iterator iter = range_found.first;
		std::multimap<int,int>::iterator end = range_found.second;
		int num_of_adj_nodes = end - iter + 1;
		adjacentNodes_ls.reserve(num_of_adj_nodes);

		while(iter != end) {
			int adj_node_id = iter->second;
			std::map<int,int>::iterator it;
			it = data_index.find(adj_node_id);
			if(it != data_index.end()) {
				IR_Node* adj_node = getNode(adj_node_id);
				adjacentNodes_ls.push_back(adj_node);
			}
			++iter;
		}
	}

	return adjacentNodes_ls;
}

std::vector< IR_Node* > IR_Graph::getAdjacentOperationNodes(int id) {
	std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
	range_found = connections.equal_range(id);
	std::vector< IR_Node* > adjacentNodes_ls;

	if(range_found.first != range_found.second) {
		std::multimap<int,int>::iterator iter = range_found.first;
		std::multimap<int,int>::iterator end = range_found.second;
		int num_of_adj_nodes = end - iter + 1;
		adjacentNodes_ls.reserve(num_of_adj_nodes);

		while(iter != end) {
			int adj_node_id = iter->second;
			std::map<int,int>::iterator it;
			it = operations_index.find(adj_node_id);
			if(it != operations_index.end()) {
				IR_Node* adj_node = getNode(adj_node_id);
				adjacentNodes_ls.push_back(adj_node);
			}
			++iter;
		}
	}

	return adjacentNodes_ls;
}

int IR_Graph::getLastOperationID() {
	int id = -1;
	if(operations_index.size() > 0)
		id = operations_index.rbegin()->first;
	return id;
}

int IR_Graph::getLastDataID() {
	int id = -1;
	if(data_index.size() > 0)
		id = data_index.rbegin()->first;
	return id;
}

void IR_Graph::appendGraph(IR_Graph* appendedGraph) {
	if( appendedGraph != NULL ) {
		appendedGraph->setClean(false);

		// Appending operations and data nodes pointers
		int num_of_ops_appended_graph = appendedGraph->getNumOfOperations();
		int num_of_data_appended_graph = appendedGraph->getNumOfData();

		if(num_of_ops_appended_graph > 0) {
			int src = getLastOperationID();
			IR_OperationNode* op_node = appendedGraph->getOperation(0);
			addOperationNode(op_node);
			// Adding connection between operation nodes of two graphs
			if( src > 0 ) {
				int dst = getLastOperationID();
				addConnection(src,dst);
			}
		}
		for(int i = 1; i < num_of_ops_appended_graph; i++) {
			IR_OperationNode* op_node = appendedGraph->getOperation(i);
			addOperationNode(op_node);
		}
		for(int i = 0; i < num_of_data_appended_graph; i++) {
			IR_DataNode* data_node = appendedGraph->getData(i);
			addDataNode(data_node);
		}

		// Appending connections
		int connections_num = appendedGraph->getNumOfConnections();
		for(int i = 0; i < connections_num; i++) {
			int src = appendedGraph->getConnectionSrc(i);
			int dst = appendedGraph->getConnectionDst(i);
			if(( src > 0 ) && ( dst > 0 ))
				addConnection(src,dst);
		}

		delete appendedGraph;
	}

}

int IR_Graph::getNumOfOperations() {
	return operations.size();
}

int IR_Graph::getNumOfData() {
	return data.size();
}

void IR_Graph::setClean(bool a_full_clean) {
	full_clean = a_full_clean;
}

IR_OperationNode* IR_Graph::getOperation(int index) {
	IR_OperationNode* return_node;
	if(index > operations.size() - 1)
		return_node = NULL;
	else
		return_node = operations[index];

	return return_node;
}

IR_DataNode* IR_Graph::getData(int index) {
	IR_DataNode* return_node;
	if(index > data.size() - 1)
		return_node = NULL;
	else
		return_node = data[index];

	return return_node;
}

int IR_Graph::getNumOfConnections() {
	return connections.size();
}

int IR_Graph::getConnectionSrc(int index) {
	std::multimap< int, int >::iterator connection = connections.begin();
	int src;
	if(index > connections.size() - 1)
		src = -1;
	else {
		std::advance(connection,index);
		src = connection->first;
	}
	return src;
}

int IR_Graph::getConnectionDst(int index) {
	std::multimap< int, int >::iterator connection = connections.begin();
	int dst;
	if(index > connections.size() - 1)
		dst = -1;
	else {
		std::advance(connection,index);
		dst = connection->second;
	}
	return dst;
}
