/*
 * Algorithm
 *
 *  Created on: 07.10.2016
 *      Author: remit
 */

#ifndef ALGORITHM_
#define ALGORITHM_

#include "IRGraph.h"
#include "TransferExpr.h"
#include "build.h"

// Function to construct a graph only with arithmetical or logical processing
// operation nodes and data nodes with data processed only by CPU.
int Graph_ArithmeticLogicProcessing( IR_Graph* src_graph, IR_Graph* al_graph );

// Function to construct a graph only with structures processing
// operation nodes and data nodes with data processed only by SPU.
int Graph_StructureProcessing( IR_Graph* src_graph, IR_Graph* sp_graph );

#endif /* ALGORITHM_ */
