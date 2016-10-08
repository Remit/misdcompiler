/*
 * Algorithm
 *
 *  Created on: 07.10.2016
 *      Author: remit
 */

#ifndef ALGORITHM_
#define ALGORITHM_

#include "IRGraph.h"

// Function to construct a graph only with arithmetical or logical processing
// operation nodes and data nodes with data processed only by CPU.
IR_Graph* Graph_ArithmeticLogicProcessing( IR_Graph* src_graph );

// Function to construct a graph only with structures processing
// operation nodes and data nodes with data processed only by SPU.
IR_Graph* Graph_StructureProcessing( IR_Graph* src_graph );

#endif /* ALGORITHM_ */
