/*
 * IRGraph.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "../include/IRGraph.h"

IR_Graph::IR_Graph() {
	operations.reserve(initial_size);
	data.reserve(initial_size);
	num_of_reserve_data = 1;
	num_of_reserve_operations = 1;
	last_operation_id = -1;
	last_data_id = -1;
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

		int last_id = a_OperationNode->getID();
		if(last_id < 0) {
			// Calculating global id for a node, which was created
			// outside the parser (i.e. when slicing)
			int max_gid = -1;
			std::map<int,int>::iterator seek_iter;
			for(seek_iter = operations_index.begin(); seek_iter != operations_index.end(); seek_iter++) {
				int found_gid = seek_iter->first;
				if(found_gid > max_gid)
					max_gid = found_gid;
			}

			for(seek_iter = data_index.begin(); seek_iter != data_index.end(); seek_iter++) {
				int found_gid = seek_iter->first;
				if(found_gid > max_gid)
					max_gid = found_gid;
			}

			last_id = max_gid + 1;
		}
		operations.push_back(a_OperationNode);
		operations_index[last_id] = operations.size() - 1;
		last_operation_id = last_id;
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

		int last_id = a_DataNode->getID();
		if(last_id < 0) {
			// Calculating global id for a node, which was created
			// outside the parser (i.e. when slicing)
			int max_gid = -1;
			std::map<int,int>::iterator seek_iter;
			for(seek_iter = operations_index.begin(); seek_iter != operations_index.end(); seek_iter++) {
				int found_gid = seek_iter->first;
				if(found_gid > max_gid)
					max_gid = found_gid;
			}

			for(seek_iter = data_index.begin(); seek_iter != data_index.end(); seek_iter++) {
				int found_gid = seek_iter->first;
				if(found_gid > max_gid)
					max_gid = found_gid;
			}

			last_id = max_gid + 1;
		}
		data.push_back(a_DataNode);
		data_index[last_id] = data.size() - 1;
		last_data_id = last_id;
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

		while( (connection_found == false) && (iter != end) ) {
			if(iter->second == id_dst)
				connection_found = true;
			++iter;
		}

		if(!connection_found)
			connections.insert({ id_src, id_dst });
	} else {
		connections.insert({ id_src, id_dst });
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
			// Correcting links to nodes
			std::map<int,int>::iterator iter;
			for(iter = data_index.begin(); iter != data_index.end(); iter++) {
				if(iter->second > pos)
					iter->second--;
			}
		}
	} else {// Deleting an element from operations vertices in case a_id is a global id for operation node
		node_found = true;
		operations_index.erase(a_id);
		int pos = it->second;
		delete operations[pos];
		operations.erase(operations.begin() + pos);
		std::map<int,int>::iterator iter;
		for(iter = operations_index.begin(); iter != operations_index.end(); iter++) {
			if(iter->second > pos)
				iter->second--;
		}
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
	std::map<int,int>::iterator it;
	it = operations_index.find(a_id);
	IR_Node* ret_node;
	if( it == operations_index.end()) {
			it = data_index.find(a_id);
			if(it != data_index.end()) {
				int pos = it->second;
				ret_node = data[pos];
			} else {
				ret_node = NULL;
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

std::vector< int > * IR_Graph::getOperationNodesIDs() {
	std::vector< int > * operationNodesIDs = new std::vector< int >;
	int num_of_ops = getNumOfOperations();
	operationNodesIDs->reserve(num_of_ops);
	std::map< int, int >::iterator it;
	for(it = operations_index.begin(); it != operations_index.end(); it++) {
		operationNodesIDs->push_back(it->first);
	}

	return operationNodesIDs;
}

std::vector< int > * IR_Graph::getDataNodesIDs() {
	std::vector< int > * dataNodesIDs = new std::vector< int >;
	int num_of_datas = getNumOfData();
	dataNodesIDs->reserve(num_of_datas);
	std::map<int,int>::iterator it;
	for(it = data_index.begin(); it != data_index.end(); it++) {
		dataNodesIDs->push_back(it->first);
	}

	return dataNodesIDs;
}

std::vector< int > * IR_Graph::getDependentOperationNodes(int id) {
	std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
	range_found = connections.equal_range(id);
	std::vector< int > * dependentNodes_ls = new std::vector< int >;

	if(range_found.first != range_found.second) {
		std::multimap<int,int>::iterator iter = range_found.first;
		std::multimap<int,int>::iterator end = range_found.second;
		int num_of_dependent_nodes = std::distance(connections.begin(),end) - std::distance(connections.begin(),iter) + 1;
		dependentNodes_ls->reserve(num_of_dependent_nodes);

		while(iter != end) {
			int dependent_node_id = iter->second;
			std::map<int,int>::iterator it;
			it = operations_index.find(dependent_node_id);
			if(it != operations_index.end())
				dependentNodes_ls->push_back(dependent_node_id);
			++iter;
		}
	}

	return dependentNodes_ls;
}

std::vector< int > * IR_Graph::getDependentDataNodes(int id) {
	std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> range_found;
	range_found = connections.equal_range(id);
	std::vector< int > * dependentNodes_ls = new std::vector< int >;

	if(range_found.first != range_found.second) {
		std::multimap<int,int>::iterator iter = range_found.first;
		std::multimap<int,int>::iterator end = range_found.second;
		int num_of_dependent_nodes = std::distance(connections.begin(),end) - std::distance(connections.begin(),iter) + 1;
		dependentNodes_ls->reserve(num_of_dependent_nodes);

		while(iter != end) {
			int dependent_node_id = iter->second;
			std::map<int,int>::iterator it;
			it = data_index.find(dependent_node_id);
			if(it != data_index.end())
				dependentNodes_ls->push_back(dependent_node_id);
			++iter;
		}
	}

	return dependentNodes_ls;
}

std::vector< int > * IR_Graph::getIncomingOperationNodes(int id) {
	std::vector< int > * incomingNodes_ls = new std::vector< int >;
	int sz = 0;

	std::multimap<int,int>::iterator iter = connections.begin();
	std::multimap<int,int>::iterator end = connections.end();

	while(iter != end) {
		incomingNodes_ls->reserve(++sz);
		int src = iter->first;
		int dst = iter->second;

		if(dst == id) {
			std::map<int,int>::iterator it;
			it = operations_index.find(src);
			if(it != operations_index.end())
				incomingNodes_ls->push_back(src);
		}

		++iter;
	}

	return incomingNodes_ls;
}

std::vector< int > * IR_Graph::getIncomingDataNodes(int id) {
	std::vector< int > * incomingNodes_ls = new std::vector< int >;
	int sz = 0;

	std::multimap<int,int>::iterator iter = connections.begin();
	std::multimap<int,int>::iterator end = connections.end();

	while(iter != end) {
		incomingNodes_ls->reserve(++sz);
		int src = iter->first;
		int dst = iter->second;

		if(dst == id) {
			std::map<int,int>::iterator it;
			it = data_index.find(src);
			if(it != data_index.end())
				incomingNodes_ls->push_back(src);
		}

		++iter;
	}

	return incomingNodes_ls;
}

int IR_Graph::getLastOperationID() {
	int id = -1;
	if(operations_index.size() > 0)
		id = last_operation_id;
	return id;
}

int IR_Graph::getLastDataID() {
	int id = -1;
	if(data_index.size() > 0)
		id = last_data_id;
	return id;
}

int IR_Graph::getFirstOperationID() {
	int id = -1;
	if(operations_index.size() > 0)
		id = operations_index.begin()->first;
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
			int dst = op_node->getID();
			addOperationNode(op_node);
			// Adding connection between operation nodes of two graphs
			if( src > 0 )
				addConnection(src,dst);
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

void IR_Graph::appendGraph( IR_Graph* appendedGraph, int src_node ) {
	std::map< int, int > gid_changes;
	if( appendedGraph != NULL ) {
		appendedGraph->setClean(false);

		// Appending operations and data nodes pointers
		int num_of_ops_appended_graph = appendedGraph->getNumOfOperations();
		int num_of_data_appended_graph = appendedGraph->getNumOfData();

		if(num_of_ops_appended_graph > 0) {
			IR_OperationNode* op_node = appendedGraph->getOperation(0);
			int dst = op_node->getID();
			addOperationNode(op_node);
			// Adding connection between operation nodes of two graphs
			if( src_node > 0 )
				addConnection(src_node,dst);
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

void IR_Graph::copyGraph(IR_Graph* copiedGraph) {
	if( copiedGraph != NULL ) {
		copiedGraph->setClean(false);

		// Appending operations and data nodes pointers
		int num_of_ops_appended_graph = copiedGraph->getNumOfOperations();
		int num_of_data_appended_graph = copiedGraph->getNumOfData();

		if(num_of_ops_appended_graph > 0) {
			int src = getLastOperationID();
			IR_OperationNode* op_node = copiedGraph->getOperationCopy(0);
			int dst = op_node->getID();
			addOperationNode(op_node);
			// Adding connection between operation nodes of two graphs
			if( src > 0 )
				addConnection(src,dst);
		}
		for(int i = 1; i < num_of_ops_appended_graph; i++) {
			IR_OperationNode* op_node = copiedGraph->getOperationCopy(i);
			addOperationNode(op_node);
		}
		for(int i = 0; i < num_of_data_appended_graph; i++) {
			IR_DataNode* data_node = copiedGraph->getDataCopy(i);
			addDataNode(data_node);
		}

		// Appending connections
		int connections_num = copiedGraph->getNumOfConnections();
		for(int i = 0; i < connections_num; i++) {
			int src = copiedGraph->getConnectionSrc(i);
			int dst = copiedGraph->getConnectionDst(i);
			if(( src > 0 ) && ( dst > 0 ))
				addConnection(src,dst);
		}
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

IR_OperationNode* IR_Graph::getOperationCopy(int index) {
	IR_OperationNode* return_node;
	if(index > operations.size() - 1)
		return_node = NULL;
	else {
		return_node = new IR_OperationNode();
		IR_OperationNode* tmp_node = operations[index];
		return_node->setID(tmp_node->getID());
		return_node->setNodeASTSubTree(tmp_node->getNodeASTSubTreeCopy());
		return_node->setOperationType(tmp_node->getOperationType());
		return_node->setProcType(tmp_node->getProcType());
	}

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

IR_DataNode* IR_Graph::getDataCopy(int index) {
	IR_DataNode* return_node;
	if(index > data.size() - 1)
		return_node = NULL;
	else {
		return_node = new IR_DataNode();
		IR_DataNode* tmp_node = data[index];
		return_node->setID(tmp_node->getID());
		return_node->setDataType(tmp_node->getDataType());
		return_node->setSimpleType(tmp_node->getSimpleType());
		return_node->setProcType(tmp_node->getProcType());
	}

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

void IR_Graph::printConnections() {
	std::cout << std::endl << "Connections: " << std::endl;
	if(connections.begin() == connections.end())
		std::cout << "EMPTY!";
	std::multimap< int, int >::iterator connection;
	for( connection = connections.begin(); connection != connections.end(); connection++ )
		std::cout << "From " << connection->first << " to " << connection->second << std::endl;
}

void IR_Graph::printNodes() {
	std::cout << "Operation nodes: " << std::endl;
	std::map< int, int >::iterator op_node;
	int op_gid, op_id;
	IR_OperationNode* cur_op_node;
	for( op_node = operations_index.begin(); op_node != operations_index.end(); op_node++ ) {
		op_gid = op_node->first;
		op_id = op_node->second;
		cur_op_node = operations[op_id];
		std::cout << "Node # " << op_gid << " --- node info: ";
		cur_op_node->print();
		std::cout << std::endl;
	}

	std::cout << std::endl << "Data nodes: " << std::endl;
	std::map< int, int >::iterator data_node;
	int data_gid, data_id;
	IR_DataNode* cur_data_node;
	for( data_node = data_index.begin(); data_node != data_index.end(); data_node++ ) {
		data_gid = data_node->first;
		data_id = data_node->second;
		cur_data_node = data[data_id];
		std::cout << "Node # " << data_gid << " --- node info: ";
		cur_data_node->print();
		std::cout << std::endl;
	}
}
