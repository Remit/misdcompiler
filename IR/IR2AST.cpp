#include "../include/IR2AST.h"

//This function constructs AST representation of IR graph:
//the AST is unbalanced and grows in the right direction,
//from top to the bottom. The rightmost end node of the AST
//has NULL LHS and RHS pointers.
Base_AST * convertIRtoAST(IR_Graph * graph) {
	SequenceAST * ast = new SequenceAST();
	SequenceAST * cur_ptr = ast;
	
	if(graph != NULL) {
		int considered_op_node_id = graph->getStartTerminalNodeID();
		
		std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(considered_op_node_id);
		
		if(dep_op_ids != NULL) {
			// Main sequential processing loop (loops and if-constructions are processed as elements of sequence
			while(dep_op_ids->size() > 0) {
				IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(considered_op_node_id);
		
				if(op_node != NULL) {
					//Check whether the following op node is conditional node for for-loop
					int i = 0;
					bool found = false;
					while(!found && (i < dep_op_ids->size())) {
						IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
						if(op_node_cur->getInstructionType() == I_FOR_LOOP)
							found = true;
						i++;
					}
					
					if((op_node->getOperationType() == IR_OP_ASSIGNMENT) && found) {
						//Checking the case of for-loop
						ForLoop * st_for = AST_st_forloop(considered_op_node_id, graph);
						cur_ptr->setLHS_E(st_for);
						SequenceAST * new_seq = new SequenceAST();
						cur_ptr->setRHS_E(new_seq);
						cur_ptr = new_seq;
						considered_op_node_id = op_node->getConnectedNodeID();
					} else if(op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) {
						//Checking the case of while-loop, if-then and if-then-else constructs
						if(op_node->getInstructionType() == I_WHILE_LOOP) {
							WhileLoop * st_while = AST_st_whileloop(considered_op_node_id, graph);
							cur_ptr->setLHS_E(st_while);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
						} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
							IfExpression * st_if = AST_st_if(considered_op_node_id, graph);
							cur_ptr->setLHS_E(st_if);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
						}
						
						considered_op_node_id = op_node->getConnectedNodeID();
					} else if(op_node->getOperationType() == IR_OP_BRANCH_BEGIN) {
						//TODO: Checking the case for control flow slicing for structure processing graph
					} else {
						//Linear case
						if(op_node->getOperationType() != IR_OP_BRANCH_END) {
							cur_ptr->setLHS_E(op_node->getNodeASTSubTree());
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
						}
						
						considered_op_node_id = (*dep_op_ids)[0];
					}
				}
				
				dep_op_ids = graph->getDependentOperationNodes(considered_op_node_id);
			}
			
		}
	}
	
	return ast;
}

//Subfunction to convert if-IR to appropriate AST parts
IfExpression * AST_st_if(int node_id, IR_Graph * graph) {
	if(graph != NULL) {
		IR_OperationNode* op_node_cond = ( IR_OperationNode* )graph->getNode(node_id);
		int end_id = op_node_cond->getConnectedNodeID();
		int first_then_id = op_node_cond->getThenID();
		int first_else_id = op_node_cond->getElseID();
		IfExpression * ast_if = (IfExpression *)op_node_cond->getNodeASTSubTree();

		//Then-branch
		
		if(first_then_id > 0) {
			int cur_op_id;
			SequenceAST * ast = new SequenceAST();
			SequenceAST * cur_ptr = ast;
			cur_op_id = first_then_id;
			
			std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
		
			if(dep_op_ids != NULL) {
				// Main sequential processing loop (loops and if-constructions are processed as elements of sequence
				while((dep_op_ids->size() > 0) && (cur_op_id != end_id)) {
					op_node = ( IR_OperationNode* )graph->getNode(cur_op_id);
		
					if(op_node != NULL) {
						//Check whether the following op node is conditional node for for-loop
						int i = 0;
						bool found = false;
						while(!found && (i < dep_op_ids->size())) {
							IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
							if(op_node_cur->getInstructionType() == I_FOR_LOOP)
								found = true;
							i++;
						}
					
						if((op_node->getOperationType() == IR_OP_ASSIGNMENT) && found) {
							//Checking the case of for-loop
							ForLoop * st_for = AST_st_forloop(cur_op_id, graph);
							cur_ptr->setLHS_E(st_for);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
							cur_op_id = op_node->getConnectedNodeID();
						} else if(op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) {
							//Checking the case of while-loop, if-then and if-then-else constructs
							if(op_node->getInstructionType() == I_WHILE_LOOP) {
								WhileLoop * st_while = AST_st_whileloop(cur_op_id, graph);
								cur_ptr->setLHS_E(st_while);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
							} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
								IfExpression * st_if = AST_st_if(cur_op_id, graph);
								cur_ptr->setLHS_E(st_if);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
							}
						
							cur_op_id = op_node->getConnectedNodeID();
						} else {
							//Linear case
							if(op_node->getOperationType() != IR_OP_BRANCH_END) {
								cur_ptr->setLHS_E(op_node->getNodeASTSubTree());
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
							}
						
							cur_op_id = (*dep_op_ids)[0];
						}
					}
				
					dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
				}
			
				//Assigning as then-part for IF expression AST node
				ast_if->setThenExpression(ast);
			}
		}
		
		//Else-branch
		if(first_else_id > 0) {
			int cur_op_id;
			SequenceAST * ast = new SequenceAST();
			SequenceAST * cur_ptr = ast;
			cur_op_id = first_else_id;
			
			std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
		
			if(dep_op_ids != NULL) {
				// Main sequential processing loop (loops and if-constructions are processed as elements of sequence
				while((dep_op_ids->size() > 0) && (cur_op_id != end_id)) {
					op_node = ( IR_OperationNode* )graph->getNode(cur_op_id);
		
					if(op_node != NULL) {
						//Check whether the following op node is conditional node for for-loop
						int i = 0;
						bool found = false;
						while(!found && (i < dep_op_ids->size())) {
							IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
							if(op_node_cur->getInstructionType() == I_FOR_LOOP)
								found = true;
							i++;
						}
					
						if((op_node->getOperationType() == IR_OP_ASSIGNMENT) && found) {
							//Checking the case of for-loop
							ForLoop * st_for = AST_st_forloop(cur_op_id, graph);
							cur_ptr->setLHS_E(st_for);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
							cur_op_id = op_node->getConnectedNodeID();
						} else if(op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) {
							//Checking the case of while-loop, if-then and if-then-else constructs
							if(op_node->getInstructionType() == I_WHILE_LOOP) {
								WhileLoop * st_while = AST_st_whileloop(cur_op_id, graph);
								cur_ptr->setLHS_E(st_while);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
							} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
								IfExpression * st_if = AST_st_if(cur_op_id, graph);
								cur_ptr->setLHS_E(st_if);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
							}
						
							cur_op_id = op_node->getConnectedNodeID();
						} else {
							//Linear case
							if(op_node->getOperationType() != IR_OP_BRANCH_END) {
								cur_ptr->setLHS_E(op_node->getNodeASTSubTree());
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
							}
						
							cur_op_id = (*dep_op_ids)[0];
						}
					}
				
					dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
				}
			
				//Assigning as then-part for IF expression AST node
				ast_if->setElseExpression(ast);
			}
		}
		
	}
	
	return ast_if;
}

WhileLoop * AST_st_whileloop(int node_id, IR_Graph * graph) {
	
}

ForLoop * AST_st_forloop(int node_id, IR_Graph * graph) {
	
}