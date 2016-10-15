/*
 * Algorithm.cpp
 *
 *  Created on: 07.10.2016
 *      Author: remit
 */

#include "../include/Algorithm.h"

// Check of presence of structure node among specific nodes of graph
bool check_presence_str_node(std::vector< int > * op_nodes, IR_Graph * graph) {
	bool ret_val = false;
	int i = 0;
	while( (i < op_nodes->size()) && !ret_val) {
		int op_id = (*op_nodes)[i];
		IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(op_id);
		if(op_node->getProcType() == IR_SPU)
			ret_val = true;
		i++;
	}

	return ret_val;
}

// Checking whether we have an enclosing condition node among specific nodes
bool check_presence_enclosing_condition(std::vector< int > * op_nodes, int enclosing_guid) {
	bool ret_val = false;
	int i = 0;
	while( (i < op_nodes->size()) && !ret_val) {
		int op_id = (*op_nodes)[i];
		if(op_id == enclosing_guid)
			ret_val = true;
		i++;
	}

	return ret_val;
}

// Recursive check of presence of structure processing nodes among a chain of cond-dependent nodes
bool check_presence_structure_nodes(std::vector< int > * dependent_op_nodes, IR_Graph * graph, int enclosing_guid) {
	bool ret_val = false;
	if(check_presence_str_node(dependent_op_nodes,graph)) {
		ret_val = true;
	} else if(check_presence_enclosing_condition(dependent_op_nodes,enclosing_guid)) {
		ret_val = false;
	} else {
		for(int i = 0; i < dependent_op_nodes->size(); i++) {
			int op_id = (*dependent_op_nodes)[i];
			std::vector< int > * dependent_op_nodes_next = graph->getDependentOperationNodes(op_id);
			bool sub_ret = check_presence_structure_nodes(dependent_op_nodes_next,graph,enclosing_guid);
			ret_val = ret_val || sub_ret;
		}
	}

	return ret_val;
}

IR_Graph* Graph_ArithmeticLogicProcessing( IR_Graph* src_graph ) {
	// Copying program graph to transform it to AL-form
	IR_Graph* alp_graph = new IR_Graph();
	alp_graph->copyGraph(src_graph);

	// Deleting every SPU-related operation node from graph
	// and providing send/receive instructions to
	// transfer data to and from SPU
	std::vector< int > * op_ids = alp_graph->getOperationNodesIDs();
	int op_cnt = op_ids->size();

	for( int i = 0; i < op_cnt; i++) {
		int op_id = (*op_ids)[i];

		IR_OperationNode* op_node = ( IR_OperationNode* )alp_graph->getNode(op_id);
		if(op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) {
			// Considering connection possibilities for current node
			std::vector< int > * inc_op_ids = alp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = alp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = alp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = alp_graph->getDependentDataNodes(op_id);

			// Checking whether the conditional branches require data transfer to SPU

			int enclosing_condition_id = op_node->getConnectedNodeID();
			if((enclosing_condition_id > 0) && check_presence_structure_nodes(dep_op_ids,alp_graph,enclosing_condition_id)) {
				// Adding tag variable (data node) to store the result of condition calculation
				IR_DataNode *tag_node = new IR_DataNode();
				tag_node->setProcType(IR_CPU);
				tag_node->setDataType(IR_DATA_TAG);
				tag_node->setSimpleType(0);
				alp_graph->addDataNode(tag_node);

				// Adding connection from branch condition node to newly added tag data node
				int tag_node_id = alp_graph->getLastDataID();
				alp_graph->addConnection(op_id,tag_node_id);

				// Adding send to SPU operations in each branch after the branch
				// condition nodes and connections from newly added tag data node to
				// send to SPU operations

				for(int j = 0; j < dep_op_ids->size(); j++) {
					IR_OperationNode* send_tag_node = new IR_OperationNode();
					send_tag_node->setOperationType(IR_OP_SEND);
					send_tag_node->setProcType(IR_CPU);
					alp_graph->addOperationNode(send_tag_node);
					int send_tag_node_id = alp_graph->getLastOperationID();
					int cur_dep_id = (*dep_op_ids)[j];

					alp_graph->addConnection(op_id,send_tag_node_id);
					alp_graph->addConnection(tag_node_id,send_tag_node_id);
					alp_graph->addConnection(send_tag_node_id,cur_dep_id);
					alp_graph->removeConnection(op_id,cur_dep_id);
				}
			}
		}
	}

	for(int i = 0; i < op_cnt; i++) {
		int op_id = (*op_ids)[i];

		IR_OperationNode* op_node = ( IR_OperationNode* )alp_graph->getNode(op_id);
		if(op_node->getProcType() == IR_SPU) {
			// Considering connection possibilities for current node
			std::vector< int > * inc_op_ids = alp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = alp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = alp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = alp_graph->getDependentDataNodes(op_id);
			// Considering data nodes that are used as inputs
			// to the current SPU node. Discovering whether some of
			// them are stored in CPU memory and processed by CPU.
			int last_send_added_id = 0;
			for( int j = 0; j < inc_data_ids->size(); j++) {

				int data_id = (*inc_data_ids)[j];
				IR_DataNode* data_node = ( IR_DataNode* )alp_graph->getNode(data_id);
				if(data_node != NULL) {
					if(data_node->getProcType() == IR_CPU) {

						// Creating and adding new send to SPU node to AL-graph
						IR_OperationNode* op_trans_node = new IR_OperationNode();
						op_trans_node->setProcType(IR_CPU);
						op_trans_node->setOperationType(IR_OP_SEND);
						alp_graph->addOperationNode(op_trans_node);
						int op_send_id = alp_graph->getLastOperationID();

						// Adding to graph a connection between encountered CPU
						// processed data node and newly created send to SPU node
						alp_graph->addConnection(data_id,op_send_id);

						// Adding connections for predecessors
						for(int k = 0; k < inc_op_ids->size(); k++)
							alp_graph->addConnection((*inc_op_ids)[k],op_send_id);

						// Send node is now a sole predecessor for other
						// possible send nodes
						inc_op_ids->clear();
						inc_op_ids->reserve(1);
						inc_op_ids->push_back(op_send_id);

						// Saving last added id in order to add connection
						// between last added send node and dependent operation nodes
						last_send_added_id = op_send_id;
					}
				}
			}

			// Considering data nodes that are used as outputs
			// to the current SPU node. Discovering whether some of
			// them are stored in CPU memory and processed by CPU.
			int last_recv_added_id = 0;

			for( int j = 0; j < dep_data_ids->size(); j++) {
				int data_id = (*dep_data_ids)[j];
				IR_DataNode* data_node = ( IR_DataNode* )alp_graph->getNode(data_id);
				if(data_node != NULL) {
					if(data_node->getProcType() == IR_CPU) {

						// Creating and adding new receive from SPU node to AL-graph
						IR_OperationNode* op_trans_node = new IR_OperationNode();
						op_trans_node->setProcType(IR_CPU);
						op_trans_node->setOperationType(IR_OP_RECEIVE);
						alp_graph->addOperationNode(op_trans_node);
						int op_recv_id = alp_graph->getLastOperationID();

						// Adding to graph a connection between encountered CPU
						// processed result data node and newly created receive from SPU node
						alp_graph->addConnection(op_recv_id,data_id);

						// Adding connections for predecessors
						for(int k = 0; k < inc_op_ids->size(); k++)
							alp_graph->addConnection((*inc_op_ids)[k],op_recv_id);

						// Receive node is now a sole predecessor for other
						// possible receive nodes
						inc_op_ids->clear();
						inc_op_ids->reserve(1);
						inc_op_ids->push_back(op_recv_id);

						// Saving last added id in order to add connection
						// between last added receive node and dependent operation nodes
						last_recv_added_id = op_recv_id;
					}
				}
			}

			if( (last_send_added_id != 0) && (last_recv_added_id != 0) ) {
				for(int j = 0; j < dep_op_ids->size(); j++)
					alp_graph->addConnection(last_recv_added_id,(*dep_op_ids)[j]);
			} else if(last_send_added_id != 0) {
				// Adding connection between last added send node and dependent
				// nodes for SPU node.
				for(int j = 0; j < dep_op_ids->size(); j++)
					alp_graph->addConnection(last_send_added_id,(*dep_op_ids)[j]);
			} else if(last_recv_added_id != 0) {
				// Adding connection between last added receive node and dependent
				// nodes for SPU node.
				for(int j = 0; j < dep_op_ids->size(); j++)
					alp_graph->addConnection(last_recv_added_id,(*dep_op_ids)[j]);
			}

			// If no receive and/or send nodes were introduced, adding simple connection
			if( (last_recv_added_id == 0) && (last_send_added_id == 0) ) {
				for(int k = 0; k < inc_op_ids->size(); k++)
					for(int j = 0; j < dep_op_ids->size(); j++)
						alp_graph->addConnection((*inc_op_ids)[k],(*dep_op_ids)[j]);
			}

			// Removing SPU node and connections from graph
			alp_graph->removeNode(op_id);
		}
	}

	// Deleting every SPU-related data node from graph
	// (also connections)
	std::vector< int > * data_ids = alp_graph->getDataNodesIDs();
	int data_cnt = data_ids->size();

	for(int i = 0; i < data_cnt; i++) {
		int data_id = (*data_ids)[i];

		IR_Node* node = alp_graph->getNode(data_id);
		if(node != NULL) {
			IR_DataNode* data_node = ( IR_DataNode* )node;
			if(data_node->getProcType() == IR_SPU)
				alp_graph->removeNode(data_id);
		}
	}

	return alp_graph;
}

IR_Graph* Graph_StructureProcessing( IR_Graph* src_graph ) {
	// Copying program graph to transform it to SP-form
	IR_Graph* sp_graph = new IR_Graph();
	sp_graph->copyGraph(src_graph);

	// Deleting every CPU-related operation node from graph
	// and providing send/receive instructions to
	// transfer data to and from CPU
	std::vector< int > * op_ids = sp_graph->getOperationNodesIDs();
	int op_cnt = op_ids->size();

	for( int i = 0; i < op_cnt; i++) {
		int op_id = (*op_ids)[i];

		IR_OperationNode* op_node = ( IR_OperationNode* )sp_graph->getNode(op_id);
		if(op_node->getProcType() == IR_CPU) {
			// Considering connection possibilities for current node
			std::vector< int > * inc_op_ids = sp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = sp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = sp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = sp_graph->getDependentDataNodes(op_id);

			if(op_node->getOperationType() == IR_OP_PROCESSING) {
				// Connecting input operation nodes to dependent operation nodes.
				// In reality, both sets of operations should consist of one operation node,
				// so it is correct to connect each of input operation nodes with each of
				// dependent operation nodes.
				for(int j = 0; j < inc_op_ids->size(); j++)
					for(int k = 0; k < dep_op_ids->size(); k++) {
						int inc_id = (*inc_op_ids)[j];
						int dep_id = (*dep_op_ids)[k];
						sp_graph->addConnection(inc_id,dep_id);
					}

				sp_graph->removeNode(op_id);
			} else if(op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) {
				// Transforming conditional branch node into system of simple
				// branch node, receive node, and tag node.

				// Checking whether the conditional branches require data transfer to SPU
				int enclosing_condition_id = op_node->getConnectedNodeID();
				if((enclosing_condition_id > 0) && check_presence_structure_nodes(dep_op_ids,sp_graph,enclosing_condition_id)) {
					IR_OperationNode* op_recv_node = new IR_OperationNode();
					op_recv_node->setProcType(IR_SPU);
					op_recv_node->setOperationType(IR_OP_RECEIVE);
					sp_graph->addOperationNode(op_recv_node);
					int op_recv_node_id = sp_graph->getLastOperationID();

					IR_OperationNode* op_simple_branch_node = new IR_OperationNode();
					op_simple_branch_node->setProcType(IR_SPU);
					op_simple_branch_node->setOperationType(IR_OP_BRANCH_BEGIN);
					sp_graph->addOperationNode(op_simple_branch_node);
					int op_simple_branch_node_id = sp_graph->getLastOperationID();

					IR_DataNode* data_tag_node = new IR_DataNode();
					data_tag_node->setProcType(IR_SPU);
					data_tag_node->setDataType(IR_DATA_TAG);
					data_tag_node->setSimpleType(0);
					sp_graph->addDataNode(data_tag_node);
					int data_tag_node_id = sp_graph->getLastDataID();

					sp_graph->addConnection(op_recv_node_id,data_tag_node_id);
					sp_graph->addConnection(op_recv_node_id,op_simple_branch_node_id);
					sp_graph->addConnection(data_tag_node_id,op_simple_branch_node_id);

					for(int j = 0; j < inc_op_ids->size(); j++) {
						int inc_op_id = (*inc_op_ids)[j];
						sp_graph->addConnection(inc_op_id,op_recv_node_id);
					}

					for(int j = 0; j < dep_op_ids->size(); j++) {
						int dep_op_id = (*dep_op_ids)[j];
						sp_graph->addConnection(op_simple_branch_node_id,dep_op_id);
					}
				} else {
					// Deleting conditionals if there are no structure nodes among
					// branches of checked conditional node

					// Deleting conditional node
					for(int j = 0; j < inc_op_ids->size(); j++)
						for(int k = 0; k < dep_op_ids->size(); k++) {
							int inc_id = (*inc_op_ids)[j];
							int dep_id = (*dep_op_ids)[k];
							sp_graph->addConnection(inc_id,dep_id);
						}

					sp_graph->removeNode(op_id);
				}
			} else if (op_node->getOperationType() == IR_OP_BRANCH_END) {
				// Checking whether conditional begin node is still in graph.
				// If not, deleting the current end branch node and
				// knitting remaining parts of graph together.
				int beginning_condition_id = op_node->getConnectedNodeID();
				IR_Node* op_node = sp_graph->getNode(beginning_condition_id);
				if(op_node == NULL) {
					for(int j = 0; j < inc_op_ids->size(); j++)
						for(int k = 0; k < dep_op_ids->size(); k++) {
							int inc_id = (*inc_op_ids)[j];
							int dep_id = (*dep_op_ids)[k];
							sp_graph->addConnection(inc_id,dep_id);
						}

					sp_graph->removeNode(op_id);
				}
			}
		} else if(op_node->getProcType() == IR_SPU) {
			// Considering connection possibilities for current node
			std::vector< int > * inc_op_ids = sp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = sp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = sp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = sp_graph->getDependentDataNodes(op_id);

			// Considering data nodes that are used as inputs
			// to the current SPU node. Discovering whether some of
			// them are stored in CPU memory and processed by CPU.
			int last_recv_added_id = 0;

			for( int j = 0; j < inc_data_ids->size(); j++) {
				int data_id = (*inc_data_ids)[j];
				IR_DataNode* data_node = ( IR_DataNode* )sp_graph->getNode(data_id);
				if(data_node != NULL) {
					if(data_node->getProcType() == IR_CPU) {
						// Setting temporary type
						data_node->setDataType(IR_DATA_SIMPLE_TMP);

						// Creating and adding new receive from CPU node to S-graph
						IR_OperationNode* op_trans_node = new IR_OperationNode();
						op_trans_node->setProcType(IR_CPU);
						op_trans_node->setOperationType(IR_OP_RECEIVE);
						sp_graph->addOperationNode(op_trans_node);
						int op_recv_id = sp_graph->getLastOperationID();

						// Adding to graph a connection between encountered CPU
						// processed data node and newly created receive from CPU node
						sp_graph->addConnection(op_recv_id,data_id);

						// Adding connections for predecessors
						for(int k = 0; k < inc_op_ids->size(); k++)
							sp_graph->addConnection((*inc_op_ids)[k],op_recv_id);

						// Receive node is now a sole predecessor for other
						// possible receive nodes
						inc_op_ids->clear();
						inc_op_ids->reserve(1);
						inc_op_ids->push_back(op_recv_id);

						// Saving last added id in order to add connection
						// between last added send node and dependent operation nodes
						last_recv_added_id = op_recv_id;
					}
				}
			}

			if(last_recv_added_id != 0) {
				// Adding connection between last added receive node and
				// SPU node.
				sp_graph->addConnection(last_recv_added_id,op_id);
			}

			// Considering data nodes that are used as outputs
			// to the current SPU node. Discovering whether some of
			// them are stored in CPU memory and processed by CPU.
			int last_send_added_id = 0;

			for( int j = 0; j < dep_data_ids->size(); j++) {
				int data_id = (*dep_data_ids)[j];
				IR_DataNode* data_node = ( IR_DataNode* )sp_graph->getNode(data_id);
				if(data_node != NULL) {
					if(data_node->getProcType() == IR_CPU) {
						// Setting temporary type
						data_node->setDataType(IR_DATA_SIMPLE_TMP);

						// Creating and adding new send from SPU node to S-graph
						IR_OperationNode* op_trans_node = new IR_OperationNode();
						op_trans_node->setProcType(IR_SPU);
						op_trans_node->setOperationType(IR_OP_SEND);
						sp_graph->addOperationNode(op_trans_node);
						int op_send_id = sp_graph->getLastOperationID();

						// Adding to graph a connection between encountered CPU
						// processed result data node and newly created send to CPU node
						sp_graph->addConnection(data_id,op_send_id);

						// Adding connections for predecessor - SPU proc. node
						sp_graph->addConnection(op_id,op_send_id);

						// Send node is now a sole predecessor for other
						// possible send nodes
						inc_op_ids->clear();
						inc_op_ids->reserve(1);
						inc_op_ids->push_back(op_send_id);

						// Saving last added id in order to add connection
						// between last added send node and dependent operation nodes
						last_send_added_id = op_send_id;
					}
				}
			}

			if(last_send_added_id != 0) {
				// Adding connection between last added send node and dependent
				// nodes for SPU node.
				for(int j = 0; j < dep_op_ids->size(); j++)
					sp_graph->addConnection(last_send_added_id,(*dep_op_ids)[j]);
			}
		}
	}

	// Deleting every CPU-related data node from graph
	// (also connections, but not tmp-nodes)
	std::vector< int > * data_ids = sp_graph->getDataNodesIDs();
	int data_cnt = data_ids->size();

	for(int i = 0; i < data_cnt; i++) {
		int data_id = (*data_ids)[i];

		IR_DataNode* data_node = ( IR_DataNode* )sp_graph->getNode(data_id);
		if( (data_node->getProcType() == IR_CPU) && (data_node->getDataType() != IR_DATA_SIMPLE_TMP))
			sp_graph->removeNode(data_id);
	}

	return sp_graph;
}

