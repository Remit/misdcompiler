/*
 * Algorithm.cpp
 *
 *  Created on: 07.10.2016
 *      Author: remit
 */

#include "../include/Algorithm.h"
#include <algorithm>

// Recursive check of presence of structure processing nodes among a chain of cond-dependent nodes
bool check_presence_structure_nodes(int op_id, IR_Graph * graph, std::vector< int > * enclosing_guids, int initial_cond_node_id) {
	bool ret_val = false;
	std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(op_id);
	IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(op_id);
	if((op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) || (op_node->getOperationType() == IR_OP_BRANCH_BEGIN)) {
		if(op_node->getInstructionType() == I_IF) {
			enclosing_guids->push_back(op_id);
			if((dep_op_ids != NULL) && (dep_op_ids->size() > 0)) {
				// Searching for non-end-branch node
				int id_srch = 0;
				int cont_node = (*dep_op_ids)[id_srch];
				bool found_non_end_branch = false;
				while(!found_non_end_branch && (id_srch < dep_op_ids->size())) {
					IR_OperationNode * op_node_srch = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[id_srch]);
					if((op_node_srch != NULL) && (op_node_srch->getOperationType() != IR_OP_BRANCH_END)) {
						found_non_end_branch = true;
						cont_node = (*dep_op_ids)[id_srch];
					}
					id_srch++;
				}

				ret_val = ret_val || check_presence_structure_nodes(cont_node, graph, enclosing_guids, initial_cond_node_id);// Continuing with then-sequence
			}
		} else if(op_node->getInstructionType() == I_IF_ELSE) {
			if((dep_op_ids != NULL) && (dep_op_ids->size() > 1)) {
				enclosing_guids->push_back(op_id);
				IR_OperationNode * dep_op_node = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[0]);
				IR_OperationNode * dep_op_node_alt = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[1]);
				if((dep_op_node->getOperationType() != IR_OP_BRANCH_END) && (dep_op_node_alt->getOperationType() != IR_OP_BRANCH_END) ) {
					ret_val = ret_val || check_presence_structure_nodes((*dep_op_ids)[0], graph, enclosing_guids, initial_cond_node_id);
					if(!ret_val) {
						enclosing_guids->push_back(op_id);
						ret_val = ret_val || check_presence_structure_nodes((*dep_op_ids)[1], graph, enclosing_guids, initial_cond_node_id);
					}
				} else if(dep_op_node_alt->getOperationType() != IR_OP_BRANCH_END) {
					ret_val = ret_val || check_presence_structure_nodes((*dep_op_ids)[1], graph, enclosing_guids, initial_cond_node_id);
				} else {
					ret_val = ret_val || check_presence_structure_nodes((*dep_op_ids)[0], graph, enclosing_guids, initial_cond_node_id);
				}
			}
		} else if((op_node->getInstructionType() == I_FOR_LOOP) || (op_node->getInstructionType() == I_WHILE_LOOP)) {
			std::vector< int >::iterator iter_cons_br_node = std::find(enclosing_guids->begin(),enclosing_guids->end(),op_id);
			if(iter_cons_br_node != enclosing_guids->end()) {// We have processed the loop body
				// Searching for end-branch node
				std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(op_id);
				if(dep_op_ids->size() > 0) {
					int id_srch = 0;
					int cont_node = (*dep_op_ids)[id_srch];
					bool found_non_end_branch = false;
					while(!found_non_end_branch && (id_srch < dep_op_ids->size())) {
						IR_OperationNode * op_node_srch = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[id_srch]);
						if((op_node_srch != NULL) && (op_node_srch->getOperationType() == IR_OP_BRANCH_END)) {
							found_non_end_branch = true;
							cont_node = (*dep_op_ids)[id_srch];
						}
						id_srch++;
					}

					
					ret_val = ret_val || check_presence_structure_nodes(cont_node, graph, enclosing_guids, initial_cond_node_id); // Continuing with end branch node for the loop
				}
			} else {
				enclosing_guids->push_back(op_id);
				std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(op_id);
				if(dep_op_ids->size() > 0) {
					// Searching for non-end-branch node
					int id_srch = 0;
					int cont_node = (*dep_op_ids)[id_srch];
					bool found_non_end_branch = false;
					while(!found_non_end_branch && (id_srch < dep_op_ids->size())) {
						IR_OperationNode * op_node_srch = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[id_srch]);
						if((op_node_srch != NULL) && (op_node_srch->getOperationType() != IR_OP_BRANCH_END)) {
							found_non_end_branch = true;
							cont_node = (*dep_op_ids)[id_srch];
						}
						id_srch++;
					}

					ret_val = ret_val || check_presence_structure_nodes(cont_node, graph, enclosing_guids, initial_cond_node_id); // Continuing with loop-body
				}
			}
		}
	} else if (op_node->getOperationType() == IR_OP_BRANCH_END) {
		int connected_branch_id = op_node->getConnectedNodeID();

		bool found_cond = false;

		std::vector< int >::iterator iter_cons_br_node = std::find(enclosing_guids->begin(),enclosing_guids->end(),connected_branch_id);
		if(iter_cons_br_node != enclosing_guids->end())
			found_cond = true;

		if(found_cond) {
			enclosing_guids->erase(iter_cons_br_node);
			std::vector< int >::iterator iter_cons_br_node = std::find(enclosing_guids->begin(),enclosing_guids->end(),connected_branch_id);
			if(enclosing_guids->size() > 0)
				if(iter_cons_br_node == enclosing_guids->end()) // Continuing only if there is no other path for if-else to achieve this node
					if(enclosing_guids->size() > 0) {
						std::vector< int > * dep_op_ids_next = graph->getDependentOperationNodes(op_id);
						if((dep_op_ids_next != NULL) && (dep_op_ids_next->size() > 0)) {
							ret_val = ret_val || check_presence_structure_nodes((*dep_op_ids_next)[0], graph, enclosing_guids, initial_cond_node_id);
						}
					}
		}
	} else {
		if((op_node->getOperationType() == IR_OP_PROCESSING) && (op_node->getProcType() == IR_SPU)) {
			ret_val = true;
		} else {
			if((dep_op_ids != NULL) && (dep_op_ids->size() > 0))
				ret_val = ret_val || check_presence_structure_nodes((*dep_op_ids)[0], graph, enclosing_guids, initial_cond_node_id);
		}
	}

	return ret_val;
}

// Checking whether there are CPU data nodes among nodes under consideration
bool check_presence_cpu_data_nodes(std::vector< int > * data_nodes, IR_Graph * graph) {
	bool check = false;
	if(data_nodes != NULL) {
		int j = 0;
		while( !check && (j < data_nodes->size())) {
			int data_id = (*data_nodes)[j];
			IR_DataNode* data_node = ( IR_DataNode* )graph->getNode(data_id);
			if(data_node != NULL) {
				if(data_node->getProcType() == IR_CPU) {

					check = true;
				}
			}
			j++;
		}
	}

	return check;
}

IR_Graph* Graph_ArithmeticLogicProcessing( IR_Graph* src_graph ) {
	// Copying program graph to transform it to AL-form
	IR_Graph* alp_graph = new IR_Graph();
	alp_graph->copyGraph(src_graph);
	
	int tag_id = 0;

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
			std::vector< int > * enclosing_condition_ids = new std::vector< int >;
			if((enclosing_condition_id > 0) && check_presence_structure_nodes(op_id,alp_graph,enclosing_condition_ids,op_id)) {
				// Adding tag variable (data node) to store the result of condition calculation
				IR_DataNode *tag_node = new IR_DataNode();
				tag_node->setProcType(IR_CPU);
				tag_node->setDataType(IR_DATA_TAG);
				tag_node->setSimpleType(VAR_INT);
				alp_graph->addDataNode(tag_node);

				// Adding connection from branch condition node to newly added tag data node
				int tag_node_id = alp_graph->getLastDataID();
				alp_graph->addConnection(op_id,tag_node_id);

				// Adding send to SPU operations in each branch after the branch
				// condition nodes and connections from newly added tag data node to
				// send to SPU operations

				for(int j = 0; j < dep_op_ids->size(); j++) {
					int cur_dep_id = (*dep_op_ids)[j];
					IR_OperationNode* dep_node = ( IR_OperationNode* )alp_graph->getNode(cur_dep_id);
					
					IR_OperationNode* send_tag_node = new IR_OperationNode();
					send_tag_node->setOperationType(IR_OP_SEND);
					send_tag_node->setProcType(IR_CPU);
					std::string tag_name = "al_tag_" + std::to_string(tag_id);
					TransferExpr * te = new TransferExpr(tag_name,TR_SEND);
					send_tag_node->setNodeASTSubTree(te);
					alp_graph->addOperationNode(send_tag_node);
					int send_tag_node_id = alp_graph->getLastOperationID();

					alp_graph->addConnection(tag_node_id,send_tag_node_id);
					
					if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_WHILE_LOOP) || (op_node->getInstructionType() == I_FOR_LOOP)) {
						if(cur_dep_id == op_node->getThenID())
							op_node->setThenID(send_tag_node_id);
					} else if(op_node->getInstructionType() == I_IF_ELSE) {
						if(cur_dep_id == op_node->getThenID()) {
							op_node->setThenID(send_tag_node_id);
						} else if(cur_dep_id == op_node->getElseID()) {
							op_node->setElseID(send_tag_node_id);
						}
					}
					
					if(dep_node->getOperationType() != IR_OP_BRANCH_END) {
						alp_graph->addConnection(op_id,send_tag_node_id);
						alp_graph->addConnection(send_tag_node_id,cur_dep_id);
						alp_graph->removeConnection(op_id,cur_dep_id);
					} else {
						std::vector< int > * dep_op_ids_next = alp_graph->getDependentOperationNodes(cur_dep_id);
						if(dep_op_ids_next != NULL) {
							for(int k = 0; k < dep_op_ids_next->size(); k++) {
								alp_graph->addConnection(send_tag_node_id,(*dep_op_ids_next)[k]);
								alp_graph->removeConnection(cur_dep_id,(*dep_op_ids_next)[k]);
							}
						}
						
						alp_graph->addConnection(cur_dep_id,send_tag_node_id);
					}
				}
				
				tag_id++;
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
			int first_transfer_added_id = 0;
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
						TransferExpr * te = new TransferExpr(data_node->getDataName(),TR_SEND);
						op_trans_node->setNodeASTSubTree(te);
						alp_graph->addOperationNode(op_trans_node);
						int op_send_id = alp_graph->getLastOperationID();
						if(first_transfer_added_id == 0)
							first_transfer_added_id = op_send_id;

						// Adding to graph a connection between encountered CPU
						// processed data node and newly created send to SPU node
						alp_graph->addConnection(data_id,op_send_id);

						// Adding connections for predecessors
						for(int k = 0; k < inc_op_ids->size(); k++) {
							alp_graph->addConnection((*inc_op_ids)[k],op_send_id);
						}

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
						TransferExpr * te = new TransferExpr(data_node->getDataName(),TR_RECEIVE);
						op_trans_node->setNodeASTSubTree(te);
						alp_graph->addOperationNode(op_trans_node);
						int op_recv_id = alp_graph->getLastOperationID();
						if(first_transfer_added_id == 0)
							first_transfer_added_id = op_recv_id;

						// Adding to graph a connection between encountered CPU
						// processed result data node and newly created receive from SPU node
						alp_graph->addConnection(op_recv_id,data_id);

						// Adding connections for predecessors
						for(int k = 0; k < inc_op_ids->size(); k++) {
							alp_graph->addConnection((*inc_op_ids)[k],op_recv_id);
						}

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

			if(first_transfer_added_id > 0) {
				for(int k = 0; k < inc_op_ids->size(); k++) {
					IR_OperationNode* inc_op_node = ( IR_OperationNode* )alp_graph->getNode((*inc_op_ids)[k]);
					if((inc_op_node->getInstructionType() == I_IF) || (inc_op_node->getInstructionType() == I_WHILE_LOOP) || (inc_op_node->getInstructionType() == I_FOR_LOOP)) {
						if(op_id == inc_op_node->getThenID())
							inc_op_node->setThenID(first_transfer_added_id);
					} else if(inc_op_node->getInstructionType() == I_IF_ELSE) {
						if(op_id == op_node->getThenID()) {
							inc_op_node->setThenID(first_transfer_added_id);
						} else if(op_id == inc_op_node->getElseID()) {
							inc_op_node->setElseID(first_transfer_added_id);
						}
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
			} else if( (last_recv_added_id == 0) && (last_send_added_id == 0) ) {
				// If no receive and/or send nodes were introduced, adding simple connection
				for(int k = 0; k < inc_op_ids->size(); k++) {
					for(int j = 0; j < dep_op_ids->size(); j++)
						alp_graph->addConnection((*inc_op_ids)[k],(*dep_op_ids)[j]);
						
					IR_OperationNode* inc_op_node = ( IR_OperationNode* )alp_graph->getNode((*inc_op_ids)[k]);
					
					if((inc_op_node->getInstructionType() == I_IF) || (inc_op_node->getInstructionType() == I_WHILE_LOOP) || (inc_op_node->getInstructionType() == I_FOR_LOOP)) {
						if(op_id == inc_op_node->getThenID())
							inc_op_node->setThenID((*dep_op_ids)[0]);
					} else if(inc_op_node->getInstructionType() == I_IF_ELSE) {
						if(op_id == inc_op_node->getThenID()) {
							inc_op_node->setThenID((*dep_op_ids)[0]);
						} else if(op_id == inc_op_node->getElseID()) {
							inc_op_node->setElseID((*dep_op_ids)[0]);
						}
					}
				}
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
	std::vector< int > branch_ids_for_deletion;

	int tag_id = 0;

	// Deleting every CPU-related operation node from graph
	// and providing send/receive instructions to
	// transfer data to and from CPU
	std::vector< int > * op_ids = sp_graph->getOperationNodesIDs();
	int op_cnt = op_ids->size();

	for( int i = 0; i < op_cnt; i++) {
		int op_id = (*op_ids)[i];

		IR_OperationNode* op_node = ( IR_OperationNode* )sp_graph->getNode(op_id);
		if(op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) {
			// Transforming conditional branch node into system of simple
			// branch node, receive node, and tag node.

			std::vector< int > * inc_op_ids = sp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = sp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = sp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = sp_graph->getDependentDataNodes(op_id);
			// Checking whether the conditional branches require data transfer to SPU
			int enclosing_condition_id = op_node->getConnectedNodeID();
			std::vector< int > * enclosing_condition_ids = new std::vector< int >;

			if((enclosing_condition_id > 0) && check_presence_structure_nodes(op_id,sp_graph,enclosing_condition_ids,op_id)) {
				IR_OperationNode* op_recv_node = new IR_OperationNode();
				op_recv_node->setProcType(IR_SPU);
				op_recv_node->setOperationType(IR_OP_RECEIVE);
				std::string tag_name = "sp_tag_" + std::to_string(tag_id);
				TransferExpr * te = new TransferExpr(tag_name,TR_RECEIVE);
				op_recv_node->setNodeASTSubTree(te);
				sp_graph->addOperationNode(op_recv_node);
				int op_recv_node_id = sp_graph->getLastOperationID();

				op_node->setOperationType(IR_OP_BRANCH_BEGIN);
				op_node->setProcType(IR_SPU);
				if(op_node->getInstructionType() == I_FOR_LOOP)
					op_node->setInstructionType(I_WHILE_LOOP);

				IR_DataNode* data_tag_node = new IR_DataNode();
				data_tag_node->setProcType(IR_SPU);
				data_tag_node->setDataType(IR_DATA_TAG);
				data_tag_node->setSimpleType(VAR_INT);
				sp_graph->addDataNode(data_tag_node);
				int data_tag_node_id = sp_graph->getLastDataID();

				int last_loop_body_id = op_node->getLastNodeID_forLoops();

				sp_graph->addConnection(op_recv_node_id,data_tag_node_id);
				sp_graph->addConnection(op_recv_node_id,op_id);
				sp_graph->addConnection(data_tag_node_id,op_id);

				for(int j = 0; j < inc_op_ids->size(); j++) {
					int inc_op_id = (*inc_op_ids)[j];

					if(inc_op_id != last_loop_body_id) {
						sp_graph->addConnection(inc_op_id,op_recv_node_id);
						// Deleting connections with previous nodes
						sp_graph->removeConnection(inc_op_id,op_id);
					}
				}
				
				// If it is a loop then add receive node in loop's body
				if((op_node->getInstructionType() == I_FOR_LOOP) || (op_node->getInstructionType() == I_WHILE_LOOP)) {
					IR_OperationNode* op_recv_node_in_body = new IR_OperationNode();
					op_recv_node_in_body->setProcType(IR_SPU);
					op_recv_node_in_body->setOperationType(IR_OP_RECEIVE);
					std::string tag_name = "sp_tag_" + std::to_string(tag_id);
					TransferExpr * te_in_b = new TransferExpr(tag_name,TR_RECEIVE);
					op_recv_node_in_body->setNodeASTSubTree(te_in_b);
					tag_id++;
					sp_graph->addOperationNode(op_recv_node_in_body);
					int op_recv_node_in_body_id = sp_graph->getLastOperationID();

					sp_graph->addConnection(op_recv_node_in_body_id,data_tag_node_id);
					sp_graph->addConnection(last_loop_body_id,op_recv_node_in_body_id);
					sp_graph->addConnection(op_recv_node_in_body_id,op_id);
					sp_graph->removeConnection(last_loop_body_id,op_id);
					op_node->setLastNodeID_forLoops(op_recv_node_in_body_id);
				}
				
				tag_id++;
			} else {
				// If there are no structure nodes among
				// branches of checked conditional node
				if((op_node->getInstructionType() == I_FOR_LOOP) || (op_node->getInstructionType() == I_WHILE_LOOP)) {
					if(dep_op_ids->size() > 0) {
						int last_body_id = op_node->getLastNodeID_forLoops();
						int k = 0;
						bool found_dep_non_end = false;
						int first_body_id = (*dep_op_ids)[k];
						while(!found_dep_non_end && (k < dep_op_ids->size())) {
							int dep_id = (*dep_op_ids)[k];
							IR_OperationNode* op_node_dep = ( IR_OperationNode* )sp_graph->getNode(dep_id);
							if(op_node_dep->getOperationType() != IR_OP_BRANCH_END) {
								found_dep_non_end = true;
								first_body_id = (*dep_op_ids)[k];
							}

							k++;
						}

						k = 0;
						bool found_dep_end = false;
						int end_loop_id = (*dep_op_ids)[k];
						while(!found_dep_end && (k < dep_op_ids->size())) {
							int dep_id = (*dep_op_ids)[k];
							IR_OperationNode* op_node_dep = ( IR_OperationNode* )sp_graph->getNode(dep_id);
							if(op_node_dep->getOperationType() == IR_OP_BRANCH_END) {
								found_dep_end = true;
								end_loop_id = (*dep_op_ids)[k];
							}

							k++;
						}

						if(found_dep_non_end) {
							if(inc_op_ids != NULL)
								for(int j = 0; j < inc_op_ids->size(); j++) {
									if((*inc_op_ids)[j] != last_body_id) {
										sp_graph->addConnection((*inc_op_ids)[j],first_body_id);
										IR_OperationNode* inc_op_node = ( IR_OperationNode* )sp_graph->getNode((*inc_op_ids)[j]);
					
										if((inc_op_node->getInstructionType() == I_IF) || (inc_op_node->getInstructionType() == I_WHILE_LOOP) || (inc_op_node->getInstructionType() == I_FOR_LOOP)) {
											if(op_id == inc_op_node->getThenID())
												inc_op_node->setThenID(first_body_id);
										} else if(inc_op_node->getInstructionType() == I_IF_ELSE) {
											if(op_id == inc_op_node->getThenID()) {
												inc_op_node->setThenID(first_body_id);
											} else if(op_id == inc_op_node->getElseID()) {
												inc_op_node->setElseID(first_body_id);
											}
										}
									}
								}
						}

						if(found_dep_end) {
							sp_graph->addConnection(last_body_id,end_loop_id);
						}
					}
				} else { // Other cases (not loops)
					for(int j = 0; j < inc_op_ids->size(); j++)
						for(int k = 0; k < dep_op_ids->size(); k++) {
							int inc_id = (*inc_op_ids)[j];
							int dep_id = (*dep_op_ids)[k];
							sp_graph->addConnection(inc_id,dep_id);
						}
				}

				branch_ids_for_deletion.push_back(op_id);
				sp_graph->removeNode(op_id);
			}
		}
	}

	op_ids = sp_graph->getOperationNodesIDs();
	op_cnt = op_ids->size();
	for( int i = 0; i < op_cnt; i++) {
		int op_id = (*op_ids)[i];

		IR_OperationNode* op_node = ( IR_OperationNode* )sp_graph->getNode(op_id);
		if (op_node->getOperationType() == IR_OP_BRANCH_END) {
			// Checking whether end branch node should be deleted with begin condition node.
			// If yes, deleting the current end branch node and
			// knitting remaining parts of graph together.
			std::vector< int > * inc_op_ids = sp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = sp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = sp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = sp_graph->getDependentDataNodes(op_id);
			op_node->setProcType(IR_SPU);

			int beginning_condition_id = op_node->getConnectedNodeID();
			std::vector<int>::iterator iter_search = std::find(branch_ids_for_deletion.begin(), branch_ids_for_deletion.end(), beginning_condition_id);
			if(iter_search != branch_ids_for_deletion.end()) {
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
		}
	}

	op_ids = sp_graph->getOperationNodesIDs();
	op_cnt = op_ids->size();
	for( int i = 0; i < op_cnt; i++) {
		int op_id = (*op_ids)[i];

		IR_OperationNode* op_node = ( IR_OperationNode* )sp_graph->getNode(op_id);
		if(op_node->getProcType() == IR_CPU) {
			// Considering connection possibilities for current node
			std::vector< int > * inc_op_ids = sp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = sp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = sp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = sp_graph->getDependentDataNodes(op_id);

			if((op_node->getOperationType() == IR_OP_PROCESSING) || (op_node->getOperationType() == IR_OP_DEFINITION)) {
				// Connecting input operation nodes to dependent operation nodes.
				// In reality, both sets of operations should consist of one operation node,
				// so it is correct to connect each of input operation nodes with each of
				// dependent operation nodes.
				for(int j = 0; j < inc_op_ids->size(); j++) {
					for(int k = 0; k < dep_op_ids->size(); k++) {
						int inc_id = (*inc_op_ids)[j];
						int dep_id = (*dep_op_ids)[k];
						sp_graph->addConnection(inc_id,dep_id);
					}
					
					IR_OperationNode* inc_op_node = ( IR_OperationNode* )sp_graph->getNode((*inc_op_ids)[j]);
					
					if((inc_op_node->getInstructionType() == I_IF) || (inc_op_node->getInstructionType() == I_WHILE_LOOP) || (inc_op_node->getInstructionType() == I_FOR_LOOP)) {
						if(op_id == inc_op_node->getThenID())
							inc_op_node->setThenID((*dep_op_ids)[0]);
					} else if(inc_op_node->getInstructionType() == I_IF_ELSE) {
						if(op_id == inc_op_node->getThenID()) {
							inc_op_node->setThenID((*dep_op_ids)[0]);
						} else if(op_id == inc_op_node->getElseID()) {
							inc_op_node->setElseID((*dep_op_ids)[0]);
						}
					}
				}

				sp_graph->removeNode(op_id);
			}
		}
	}

	op_ids = sp_graph->getOperationNodesIDs();
	op_cnt = op_ids->size();
	for( int i = 0; i < op_cnt; i++) {
		int op_id = (*op_ids)[i];

		IR_OperationNode* op_node = ( IR_OperationNode* )sp_graph->getNode(op_id);
		if((op_node->getProcType() == IR_SPU) && (op_node->getOperationType() == IR_OP_PROCESSING)) {
			// Considering connection possibilities for current node
			std::vector< int > * inc_op_ids = sp_graph->getIncomingOperationNodes(op_id);
			std::vector< int > * inc_data_ids = sp_graph->getIncomingDataNodes(op_id);
			std::vector< int > * dep_op_ids = sp_graph->getDependentOperationNodes(op_id);
			std::vector< int > * dep_data_ids = sp_graph->getDependentDataNodes(op_id);
			std::vector< int > inc_op_ids_cp = (*inc_op_ids);

			// Considering data nodes that are used as inputs
			// to the current SPU node. Discovering whether some of
			// them are stored in CPU memory and processed by CPU.
			int first_transfer_added_id = 0;
			int last_recv_added_id = 0;

			bool check_cpu_data_presence = check_presence_cpu_data_nodes(inc_data_ids,sp_graph);
			if(check_cpu_data_presence) {
				for(int k = 0; k < inc_op_ids->size(); k++) {
					sp_graph->removeConnection((*inc_op_ids)[k],op_id);
				}

				for( int j = 0; j < inc_data_ids->size(); j++) {
					int data_id = (*inc_data_ids)[j];
					IR_DataNode* data_node = ( IR_DataNode* )sp_graph->getNode(data_id);
					if(data_node != NULL) {
						if(data_node->getProcType() == IR_CPU) {
							// Setting temporary type
							data_node->setDataType(IR_DATA_SIMPLE_TMP);

							// Removing connections with begin branch operation nodes
							std::vector< int > * dep_op_ids_for_dn = sp_graph->getDependentOperationNodes(data_id);
							if(dep_op_ids_for_dn != NULL)
								for(int k = 0; k < dep_op_ids_for_dn->size(); k++) {
									IR_OperationNode* op_node_dep = ( IR_OperationNode* )sp_graph->getNode((*dep_op_ids_for_dn)[k]);
									if(op_node_dep != NULL)
										if(op_node_dep->getOperationType() == IR_OP_BRANCH_BEGIN)
											sp_graph->removeConnection(data_id,(*dep_op_ids_for_dn)[k]);
								}

							// Creating and adding new receive from CPU node to S-graph
							IR_OperationNode* op_trans_node = new IR_OperationNode();
							op_trans_node->setProcType(IR_SPU);
							op_trans_node->setOperationType(IR_OP_RECEIVE);
							TransferExpr * te = new TransferExpr(data_node->getDataName(),TR_RECEIVE);
							op_trans_node->setNodeASTSubTree(te);
							sp_graph->addOperationNode(op_trans_node);
							int op_recv_id = sp_graph->getLastOperationID();
							if(first_transfer_added_id == 0)
								first_transfer_added_id = op_recv_id;

							// Adding to graph a connection between encountered CPU
							// processed data node and newly created receive from CPU node
							sp_graph->addConnection(op_recv_id,data_id);

							// Adding connections for predecessors to new node
							// Removing connections of current node with predecessors
							for(int k = 0; k < inc_op_ids->size(); k++) {
								sp_graph->addConnection((*inc_op_ids)[k],op_recv_id);
							}

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
			}

			// Considering data nodes that are used as outputs
			// to the current SPU node. Discovering whether some of
			// them are stored in CPU memory and processed by CPU.
			int last_send_added_id = 0;

			check_cpu_data_presence = check_presence_cpu_data_nodes(dep_data_ids,sp_graph);
			if(check_cpu_data_presence) {
				// Remove unnecessary connections from current node to dependent ops nodes
				for(int k = 0; k < dep_op_ids->size(); k++) {
					sp_graph->removeConnection(op_id,(*dep_op_ids)[k]);
				}
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
							TransferExpr * te = new TransferExpr(data_node->getDataName(),TR_SEND);
							op_trans_node->setNodeASTSubTree(te);
							sp_graph->addOperationNode(op_trans_node);
							int op_send_id = sp_graph->getLastOperationID();
							if(first_transfer_added_id == 0)
								first_transfer_added_id = op_send_id;

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
			}

			if(first_transfer_added_id > 0) {
				for(int k = 0; k < inc_op_ids_cp.size(); k++) {
					IR_OperationNode* inc_op_node = ( IR_OperationNode* )sp_graph->getNode(inc_op_ids_cp[k]);
					
					if((inc_op_node->getInstructionType() == I_IF) || (inc_op_node->getInstructionType() == I_WHILE_LOOP) || (inc_op_node->getInstructionType() == I_FOR_LOOP)) {
						if(op_id == inc_op_node->getThenID())
							inc_op_node->setThenID(first_transfer_added_id);
					} else if(inc_op_node->getInstructionType() == I_IF_ELSE) {
						if(op_id == inc_op_node->getThenID()) {
							inc_op_node->setThenID(first_transfer_added_id);
						} else if(op_id == inc_op_node->getElseID()) {
							inc_op_node->setElseID(first_transfer_added_id);
						}
					}
				}
			}
			if( (last_send_added_id != 0) && (last_recv_added_id != 0) ) {
				sp_graph->addConnection(last_recv_added_id,op_id);
				for(int j = 0; j < dep_op_ids->size(); j++)
					sp_graph->addConnection(op_id,(*dep_op_ids)[j]);
			} else if(last_send_added_id != 0) {
				// Adding connection between last added send node and dependent
				// nodes for SPU node.
				for(int j = 0; j < dep_op_ids->size(); j++)
					sp_graph->addConnection(last_send_added_id,(*dep_op_ids)[j]);
			} else if(last_recv_added_id != 0) {
				// Adding connection between last added receive node and dependent
				// nodes for SPU node.
				sp_graph->addConnection(last_recv_added_id,op_id);
			}

			// If no receive and/or send nodes were introduced, adding simple connection
			if( (last_recv_added_id == 0) && (last_send_added_id == 0) ) {
				std::cout << "Problem with " << op_id;
				for(int k = 0; k < inc_op_ids->size(); k++)
					for(int j = 0; j < dep_op_ids->size(); j++)
						sp_graph->addConnection((*inc_op_ids)[k],(*dep_op_ids)[j]);
			}
		}
	}

	// Deleting every CPU-related data node from graph
	// (also connections, but not tmp-nodes)
	std::vector< int > * data_ids = sp_graph->getDataNodesIDs();
	int data_cnt = data_ids->size();

	for(int i = 0; i < data_cnt; i++) {
		int data_id = (*data_ids)[i];

		IR_Node* node = sp_graph->getNode(data_id);
		if(node != NULL) {
			IR_DataNode* data_node = ( IR_DataNode* )node;
			if((data_node->getProcType() == IR_CPU) && (data_node->getDataType() != IR_DATA_SIMPLE_TMP))
				sp_graph->removeNode(data_id);
		}
	}

	return sp_graph;
}


