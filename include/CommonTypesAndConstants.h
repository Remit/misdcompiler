#ifndef COMMON_TYPES_AND_CONSTANTS
#define COMMON_TYPES_AND_CONSTANTS

#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>

extern int num_of_structures_for_usage;

typedef enum {
	IR_SPU,\
	IR_CPU,\
	IR_BOTH
} proc_type; // Type of node by processor.

typedef enum {
	IR_OP_TERMINATOR,\
	IR_OP_PROCESSING,\
	IR_OP_BRANCH_BEGIN,\
	IR_OP_BRANCH_END,\
	IR_OP_BRANCH_COND_BEGIN,\
	IR_OP_SEND,\
	IR_OP_RECEIVE
} operation_type; // Type of operation in node.

typedef enum {
	IR_DATA_STRUCTURE,\
	IR_DATA_SIMPLE,\
	IR_DATA_TAG,\
	IR_UNDEFINED
} data_type; // Type of data nodes.

#endif
