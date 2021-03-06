#include "../include/IR2AST.h"

//This function constructs AST representation of IR graph:
//the AST is unbalanced and grows in the right direction,
//from top to the bottom. The rightmost end node of the AST
//has NULL LHS and RHS pointers.
int convertIRtoAST(IR_Graph * graph, SequenceAST * ast) {
	SequenceAST * cur_ptr = ast;

	if(graph != NULL) {
		int considered_op_node_id = graph->getStartTerminalNodeID();
		
		std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(considered_op_node_id);
		if(dep_op_ids->size() > 0)
			considered_op_node_id = (*dep_op_ids)[0]; //We do not consider terminal nodes
		
		dep_op_ids = graph->getDependentOperationNodes(considered_op_node_id);
		if(dep_op_ids != NULL) {
			// Main sequential processing loop (loops and if-constructions are processed as elements of sequence
			while(dep_op_ids->size() > 0) {
				IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(considered_op_node_id);
		
				if(op_node != NULL) {
					//Check whether the following op node is conditional node for for-loop
					int i = 0;
					int cond_id = -1;
					bool found = false;
					while(!found && (i < dep_op_ids->size())) {
						IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
						if(op_node_cur->getInstructionType() == I_FOR_LOOP) {
							found = true;
							cond_id = (*dep_op_ids)[i];
						}
						i++;
					}
					
					if((op_node->getOperationType() == IR_OP_PROCESSING) && found) {
						//Checking the case of for-loop
						
						ForLoop * st_for = AST_st_forloop(considered_op_node_id, graph);
						cur_ptr->setLHS_E(st_for);
						SequenceAST * new_seq = new SequenceAST();
						cur_ptr->setRHS_E(new_seq);
						cur_ptr = new_seq;
						
						
						std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cond_id);
						bool found_end = false;
						if(dep_op_ids_loop->size() > 0) {
							int j = 0;
							while( (j < dep_op_ids_loop->size()) && !found_end) {
								IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
								if(op_node_cur_loop != NULL)
									if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
										considered_op_node_id = (*dep_op_ids_loop)[j];
										found_end = true;
									}
								j++;
							}
						}
					} else if((op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) || (op_node->getOperationType() == IR_OP_BRANCH_BEGIN)) {
						//Checking the case of while-loop, if-then and if-then-else constructs
						if(op_node->getInstructionType() == I_WHILE_LOOP) {
							
							WhileLoop * st_while = AST_st_whileloop(considered_op_node_id, graph);
							cur_ptr->setLHS_E(st_while);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
							
							//Searching for end branch node for loop
							std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(considered_op_node_id);
							bool found_end = false;
							if(dep_op_ids_loop->size() > 0) {
								int j = 0;
								while( (j < dep_op_ids_loop->size()) && !found_end) {
									IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
									if(op_node_cur_loop != NULL)
										if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
											considered_op_node_id = (*dep_op_ids_loop)[j];
											found_end = true;
										}
									j++;
								}
							}
						} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
							IfExpression * st_if = AST_st_if(considered_op_node_id, graph);
							cur_ptr->setLHS_E(st_if);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
							considered_op_node_id = op_node->getConnectedNodeID();
						}
						
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
	
	return 0;
}

//Subfunction to convert if-IR to appropriate AST parts
IfExpression * AST_st_if(int node_id, IR_Graph * graph) {
	IfExpression * ast_if = NULL;
	
	if(graph != NULL) {
		IR_OperationNode* op_node_cond = ( IR_OperationNode* )graph->getNode(node_id);
		int end_id = op_node_cond->getConnectedNodeID();
		int first_then_id = op_node_cond->getThenID();
		int first_else_id = op_node_cond->getElseID();
		ast_if = (IfExpression *)op_node_cond->getNodeASTSubTree();
		ast_if->setParentOpNode(node_id);
		std::vector< int > * dep_data_ids = graph->getDependentDataNodes(node_id);
		if(dep_data_ids != NULL) {
			for(int i = 0; i < dep_data_ids->size(); i++) {
				IR_DataNode* tag_node = ( IR_DataNode* )graph->getNode((*dep_data_ids)[i]);
				if((tag_node != NULL) && (tag_node->isTag()))
					ast_if->setALtagName(tag_node->getDataName());
			}
		}
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
					
					IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(cur_op_id);
		
					if(op_node != NULL) {
						//Check whether the following op node is conditional node for for-loop
						int i = 0;
						int cond_id = -1;
						bool found = false;
						while(!found && (i < dep_op_ids->size())) {
							IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
							if(op_node_cur->getInstructionType() == I_FOR_LOOP) {
								found = true;
								cond_id = (*dep_op_ids)[i];
							}
							i++;
						}
					
						if((op_node->getOperationType() == IR_OP_PROCESSING) && found) {
							
							//Checking the case of for-loop
							ForLoop * st_for = AST_st_forloop(cur_op_id, graph);
							cur_ptr->setLHS_E(st_for);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
							
							//Searching for end branch node for loop
							std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cond_id);
							bool found_end = false;
							if(dep_op_ids_loop->size() > 0) {
								int j = 0;
								while( (j < dep_op_ids_loop->size()) && !found_end) {
									IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
									if(op_node_cur_loop != NULL)
										if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
											cur_op_id = (*dep_op_ids_loop)[j];
											found_end = true;
										}
									j++;
								}
							}
						} else if((op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) || (op_node->getOperationType() == IR_OP_BRANCH_BEGIN)) {
							//Checking the case of while-loop, if-then and if-then-else constructs
							if(op_node->getInstructionType() == I_WHILE_LOOP) {
								WhileLoop * st_while = AST_st_whileloop(cur_op_id, graph);
								cur_ptr->setLHS_E(st_while);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
								
								//Searching for end branch node for loop
								std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cur_op_id);
								bool found_end = false;
								if(dep_op_ids_loop->size() > 0) {
									int j = 0;
									while( (j < dep_op_ids_loop->size()) && !found_end) {
										IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
										if(op_node_cur_loop != NULL)
											if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
												cur_op_id = (*dep_op_ids_loop)[j];
												found_end = true;
											}
										j++;
									}
								}
							} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
								IfExpression * st_if = AST_st_if(cur_op_id, graph);
								cur_ptr->setLHS_E(st_if);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
								cur_op_id = op_node->getConnectedNodeID();
							}
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
		if((op_node_cond->getInstructionType() == I_IF_ELSE) && (first_else_id > 0)) {
			int cur_op_id;
			SequenceAST * ast = new SequenceAST();
			SequenceAST * cur_ptr = ast;
			cur_op_id = first_else_id;
			
			std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
		
			if(dep_op_ids != NULL) {
				// Main sequential processing loop (loops and if-constructions are processed as elements of sequence
				while((dep_op_ids->size() > 0) && (cur_op_id != end_id)) {
					IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(cur_op_id);
		
					if(op_node != NULL) {
						//Check whether the following op node is conditional node for for-loop
						int i = 0;
						int cond_id = -1;
						bool found = false;
						while(!found && (i < dep_op_ids->size())) {
							IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
							if(op_node_cur->getInstructionType() == I_FOR_LOOP) {
								found = true;
								cond_id = (*dep_op_ids)[i];
							}
							i++;
						}
					
						if((op_node->getOperationType() == IR_OP_PROCESSING) && found) {
							//Checking the case of for-loop
							ForLoop * st_for = AST_st_forloop(cur_op_id, graph);
							cur_ptr->setLHS_E(st_for);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;
							
							//Searching for end branch node for loop
							std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cond_id);
							bool found_end = false;
							if(dep_op_ids_loop->size() > 0) {
								int j = 0;
								while( (j < dep_op_ids_loop->size()) && !found_end) {
									IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
									if(op_node_cur_loop != NULL)
										if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
											cur_op_id = (*dep_op_ids_loop)[j];
											found_end = true;
										}
									j++;
								}
							}
						} else if((op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) || (op_node->getOperationType() == IR_OP_BRANCH_BEGIN)) {
							//Checking the case of while-loop, if-then and if-then-else constructs
							if(op_node->getInstructionType() == I_WHILE_LOOP) {
								WhileLoop * st_while = AST_st_whileloop(cur_op_id, graph);
								cur_ptr->setLHS_E(st_while);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
								
								//Searching for end branch node for loop
								std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cur_op_id);
								bool found_end = false;
								if(dep_op_ids_loop->size() > 0) {
									int j = 0;
									while( (j < dep_op_ids_loop->size()) && !found_end) {
										IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
										if(op_node_cur_loop != NULL)
											if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
												cur_op_id = (*dep_op_ids_loop)[j];
												found_end = true;
											}
										j++;
									}
								}
							} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
								IfExpression * st_if = AST_st_if(cur_op_id, graph);
								cur_ptr->setLHS_E(st_if);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
								cur_op_id = op_node->getConnectedNodeID();
							}
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
	WhileLoop * ast_while = NULL;
	
	if(graph != NULL) {
		IR_OperationNode* op_node_cond = ( IR_OperationNode* )graph->getNode(node_id);
		int end_id = op_node_cond->getConnectedNodeID();
		ast_while = (WhileLoop *)op_node_cond->getNodeASTSubTree();
		ast_while->setParentOpNode(node_id);
		std::vector< int > * dep_data_ids = graph->getDependentDataNodes(node_id);
		if(dep_data_ids != NULL) {
			for(int i = 0; i < dep_data_ids->size(); i++) {
				IR_DataNode* tag_node = ( IR_DataNode* )graph->getNode((*dep_data_ids)[i]);
				if((tag_node != NULL) && (tag_node->isTag()))
					ast_while->setALtagName(tag_node->getDataName());
			}
		}
		std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(node_id);
		int cur_op_id;
		//Getting the first body-of-loop node		
		bool found_body = false;
		if(dep_op_ids->size() > 0) {
			int j = 0;
			while( (j < dep_op_ids->size()) && !found_body) {
				IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[j]);
				if(op_node_cur_loop != NULL)
					if(op_node_cur_loop->getOperationType() != IR_OP_BRANCH_END) {
						cur_op_id = (*dep_op_ids)[j];
						found_body = true;
					}
				j++;
			}
		}

		//While loop body
		if(cur_op_id > 0) {
			SequenceAST * ast = new SequenceAST();
			SequenceAST * cur_ptr = ast;
			
			dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
		
			if(dep_op_ids != NULL) {
				// Main sequential processing loop (loops and if-constructions are processed as elements of sequence
				while((dep_op_ids->size() > 0) && (cur_op_id != end_id) && (cur_op_id != node_id)) {
					IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(cur_op_id);
		
					if(op_node != NULL) {
						//Check whether the following op node is conditional node for for-loop
						int i = 0;
						int cond_id = -1;
						bool found = false;
						while(!found && (i < dep_op_ids->size())) {
							IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
							if(op_node_cur->getInstructionType() == I_FOR_LOOP) {
								found = true;
								cond_id = (*dep_op_ids)[i];
							}
							i++;
						}
						if((op_node->getOperationType() == IR_OP_PROCESSING) && found) {
							//Checking the case of for-loop
							ForLoop * st_for = AST_st_forloop(cur_op_id, graph);
							cur_ptr->setLHS_E(st_for);
							SequenceAST * new_seq = new SequenceAST();
							cur_ptr->setRHS_E(new_seq);
							cur_ptr = new_seq;

							//Searching for end branch node for loop
							std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cond_id);
							bool found_end = false;
							if(dep_op_ids_loop->size() > 0) {
								int j = 0;
								while( (j < dep_op_ids_loop->size()) && !found_end) {
									IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
									if(op_node_cur_loop != NULL)
										if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
											cur_op_id = (*dep_op_ids_loop)[j];
											found_end = true;
										}
									j++;
								}
							}
						} else if((op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) || (op_node->getOperationType() == IR_OP_BRANCH_BEGIN)) {
							//Checking the case of while-loop, if-then and if-then-else constructs
							if(op_node->getInstructionType() == I_WHILE_LOOP) {
								WhileLoop * st_while = AST_st_whileloop(cur_op_id, graph);
								cur_ptr->setLHS_E(st_while);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
								
								//Searching for end branch node for loop
								std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cur_op_id);
								bool found_end = false;
								if(dep_op_ids_loop->size() > 0) {
									int j = 0;
									while( (j < dep_op_ids_loop->size()) && !found_end) {
										IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
										if(op_node_cur_loop != NULL)
											if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
												cur_op_id = (*dep_op_ids_loop)[j];
												found_end = true;
											}
										j++;
									}
								}
							} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
								IfExpression * st_if = AST_st_if(cur_op_id, graph);
								cur_ptr->setLHS_E(st_if);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
								cur_op_id = op_node->getConnectedNodeID();
							}
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
			
				//Assigning as the body of while loop
				ast_while->setBody(ast);
			}
		}
	}
	
	return ast_while;
}

ForLoop * AST_st_forloop(int node_id, IR_Graph * graph) {
	ForLoop * ast_for = NULL;
	
	if(graph != NULL) {
		//Start - assignment of start iteration value
		IR_OperationNode* op_node_start = ( IR_OperationNode* )graph->getNode(node_id);
		std::vector< int > * dep_data_ids = graph->getDependentDataNodes(node_id);
		BinaryExpression * startAST = (BinaryExpression *)op_node_start->getNodeASTSubTree();
		
		std::vector< int > * dep_op_ids = graph->getDependentOperationNodes(node_id);
		int cond_node_id;
		//Getting the conditional node
		if(dep_op_ids->size() > 0) {
			cond_node_id = (*dep_op_ids)[0];
		}
		
		dep_data_ids = graph->getDependentDataNodes(cond_node_id);
		IR_OperationNode* op_node_cond = ( IR_OperationNode* )graph->getNode(cond_node_id);
		int end_id = op_node_cond->getConnectedNodeID();
		ast_for = (ForLoop *)op_node_cond->getNodeASTSubTree();
		ast_for->setParentOpNode(cond_node_id);
		if(dep_data_ids != NULL) {
			for(int i = 0; i < dep_data_ids->size(); i++) {
				IR_DataNode* tag_node = ( IR_DataNode* )graph->getNode((*dep_data_ids)[i]);
				if((tag_node != NULL) && (tag_node->isTag()))
					ast_for->setALtagName(tag_node->getDataName());
			}
		}
		// Setting the name of the counter for the purposes of code generation
		if((dep_data_ids != NULL) && (dep_data_ids->size() > 0)) {
			int counter_node_id = (*dep_data_ids)[0];
			IR_DataNode * cnt_data_node = ( IR_DataNode* )graph->getNode(counter_node_id);
			if(cnt_data_node != NULL)
				ast_for->setCounterName(cnt_data_node->getDataName());
		}
		ast_for->setStart(startAST);
		
		dep_op_ids = graph->getDependentOperationNodes(cond_node_id);
		int cur_op_id;
		//Getting the first body-of-loop node		
		bool found_body = false;
		if(dep_op_ids->size() > 0) {
			int j = 0;
			while( (j < dep_op_ids->size()) && !found_body) {
				IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[j]);
				if(op_node_cur_loop != NULL)
					if(op_node_cur_loop->getOperationType() != IR_OP_BRANCH_END) {
						cur_op_id = (*dep_op_ids)[j];
						found_body = true;
					}
				j++;
			}
		}

		//For-loop body
		if(cur_op_id > 0) {
			SequenceAST * ast = new SequenceAST();
			SequenceAST * cur_ptr = ast;
			
			dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
			
			if(dep_op_ids != NULL) {
				// Main sequential processing loop (loops and if-constructions are processed as elements of sequence
				while((dep_op_ids->size() > 0) && (cur_op_id != end_id) && (cur_op_id != node_id)) {					
					IR_OperationNode* op_node = ( IR_OperationNode* )graph->getNode(cur_op_id);
		
					if(op_node != NULL) {
						//Checking whether current node is the ending node for the body of the if-loop i.e. the step node
						bool found_end = false;
						if(dep_op_ids->size() > 0) {
							int j = 0;
							while((j < dep_op_ids->size()) && !found_end) {
								int id_lookahead = (*dep_op_ids)[j];
								if(id_lookahead == cond_node_id)
									found_end = true;
								j++;
							}
						}
						
						if(found_end) {
							BinaryExpression * stepAST = (BinaryExpression *)op_node->getNodeASTSubTree();
							ast_for->setStep(stepAST);
							cur_op_id = (*dep_op_ids)[0];
						} else {
							//Check whether the following op node is conditional node for for-loop
							int i = 0;
							int cond_id = -1;
							bool found = false;
							while(!found && (i < dep_op_ids->size())) {
								IR_OperationNode* op_node_cur = ( IR_OperationNode* )graph->getNode((*dep_op_ids)[i]);
								if(op_node_cur->getInstructionType() == I_FOR_LOOP) {
									found = true;
									cond_id = (*dep_op_ids)[i];
								}
								i++;
							}
					
							if((op_node->getOperationType() == IR_OP_PROCESSING) && found) {
								//Checking the case of for-loop
								ForLoop * st_for = AST_st_forloop(cur_op_id, graph);
								cur_ptr->setLHS_E(st_for);
								SequenceAST * new_seq = new SequenceAST();
								cur_ptr->setRHS_E(new_seq);
								cur_ptr = new_seq;
								
								//Searching for end branch node for loop
								std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cond_id);
								bool found_end = false;
								if(dep_op_ids_loop->size() > 0) {
									int j = 0;
									while( (j < dep_op_ids_loop->size()) && !found_end) {
										IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
										if(op_node_cur_loop != NULL)
											if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
												cur_op_id = (*dep_op_ids_loop)[j];
												found_end = true;
											}
										j++;
									}
								}
							} else if((op_node->getOperationType() == IR_OP_BRANCH_COND_BEGIN) || (op_node->getOperationType() == IR_OP_BRANCH_BEGIN)) {
								//Checking the case of while-loop, if-then and if-then-else constructs
								if(op_node->getInstructionType() == I_WHILE_LOOP) {
									WhileLoop * st_while = AST_st_whileloop(cur_op_id, graph);
									cur_ptr->setLHS_E(st_while);
									SequenceAST * new_seq = new SequenceAST();
									cur_ptr->setRHS_E(new_seq);
									cur_ptr = new_seq;
									
									//Searching for end branch node for loop
									std::vector< int > * dep_op_ids_loop = graph->getDependentOperationNodes(cur_op_id);
									bool found_end = false;
									if(dep_op_ids_loop->size() > 0) {
										int j = 0;
										while( (j < dep_op_ids_loop->size()) && !found_end) {
											IR_OperationNode* op_node_cur_loop = ( IR_OperationNode* )graph->getNode((*dep_op_ids_loop)[j]);
											if(op_node_cur_loop != NULL)
												if(op_node_cur_loop->getOperationType() == IR_OP_BRANCH_END) {
													cur_op_id = (*dep_op_ids_loop)[j];
													found_end = true;
												}
											j++;
										}
									}
								} else if((op_node->getInstructionType() == I_IF) || (op_node->getInstructionType() == I_IF_ELSE)) {
									IfExpression * st_if = AST_st_if(cur_op_id, graph);
									cur_ptr->setLHS_E(st_if);
									SequenceAST * new_seq = new SequenceAST();
									cur_ptr->setRHS_E(new_seq);
									cur_ptr = new_seq;
									cur_op_id = op_node->getConnectedNodeID();
								}
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
					}
				
					dep_op_ids = graph->getDependentOperationNodes(cur_op_id);
				}
			
				//Assigning as body of the for-loop
				ast_for->setBody(ast);
			}
		}
	}
	
	return ast_for;
}