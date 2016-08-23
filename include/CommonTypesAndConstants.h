#include <stdlib.h>
#include <vector>

typedef enum {
	IR_SPU,\
	IR_CPU
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
	IR_DATA_TAG
} data_type; // Type of data nodes.