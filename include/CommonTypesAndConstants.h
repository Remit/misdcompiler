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
} proc_type; // Type of node by processor

typedef enum {
	IR_OP_TERMINATOR,\
	IR_OP_PROCESSING,\
	IR_OP_BRANCH_BEGIN,\
	IR_OP_BRANCH_END,\
	IR_OP_BRANCH_COND_BEGIN,\
	IR_OP_SEND,\
	IR_OP_RECEIVE,\
	IR_OP_DEFINITION
} operation_type; // Type of operation in node

typedef enum {
	IR_DATA_STRUCTURE,\
	IR_DATA_SIMPLE,\
	IR_DATA_SIMPLE_TMP,\
	IR_DATA_TAG,\
	IR_UNDEFINED
} data_type; // Type of data nodes

typedef enum {
	I_IF,\
	I_IF_ELSE,\
	I_FOR_LOOP,\
	I_WHILE_LOOP,\
	I_DEFINE,\
	I_ASSIGN,\
	I_STRUCTURE,\
	I_UNDEFINED
} low_level_instruction_type; // Low-level type of instruction/construction in the node used to transform graph in AST

typedef enum {
	OP_PLUS,\
	OP_MINUS,\
	OP_DIV,\
	OP_MUL,\
	OP_MOD,\
	OP_AND,\
	OP_OR,\
	OP_ASSIGN,\
	OP_BINARY_UNDEFINED
} bin_op_types; // Types of binary operations for AST

typedef enum {
	OP_LT,\
	OP_GT,\
	OP_LTE,\
	OP_GTE,\
	OP_EQ,\
	OP_LOGICAL_UNDEFINED
} cond_op_types; // Types of logical operations to implement conditions in loops and if-constructions

typedef enum {
	OP_NOT,\
	OP_UMINUS,\
	OP_UNARY_UNDEFINED
} unary_op_types; // Types of binary operations for AST

typedef enum {
    OP_SEARCH_STR,\
    OP_SEARCH_SML_STR,\
    OP_SEARCH_GRT_STR,\
    OP_INSERT_STR,\
    OP_DELETE_FROM_STR,\
    OP_NEXT_STR,\
    OP_DELETE_STR,\
    OP_MAX_STR,\
    OP_MIN_STR,\
    OP_POWER_STR,\
    OP_UNION_STR,\
    OP_INTERSECT_STR,\
    OP_NOT_STR,\
    OP_GT_STR,\
    OP_LT_STR,\
    OP_LTE_STR,\
    OP_GTE_STR,\
	OP_STRUCT_UNDEFINED
} structures_proc_op_types; // Types of structures processing operations

typedef enum {
	VAR_INT,\
	VAR_LONG,\
	VAR_FLOAT,\
	VAR_DOUBLE,\
	VAR_UNDEFINED
} variable_type; // Types of variables for AST

typedef enum {
	VIS_ALL,\
	VIS_INITIAL,\
	VIS_ARITH,\
	VIS_STRUCT,\
	VIS_INITIAL_ARITH,\
	VIS_INITIAL_STRUCT,\
	VIS_ARITH_STRUCT,\
	VIS_NONE
} visualisation_option; // Options to visualise the graph

typedef enum {
	AST_BASE,\
	AST_BINARYEXPRESSION,\
	AST_EXPRESSION,\
	AST_FORLOOP,\
	AST_IFEXPRESSION,\
	AST_LOGICALEXPRESSION,\
	AST_NUMBEREXPR,\
	AST_SEQUENCEAST,\
	AST_STRUCTUREEXPR,\
	AST_STRUCTURESEXPRESSION,\
	AST_UNARYEXPRESSION,\
	AST_VARIABLEEXPR,\
	AST_WHILELOOP,\
	AST_TRANSFER
} ast_label; // Labels to determine the exact type of AST tree

typedef enum {
	TR_SEND,\
	TR_RECEIVE,\
	TR_UNDEFINED
} transfer_direction; // Direction for transfer AST nodes

typedef enum {
	GR_SP,\
	GR_AL,\
	GR_INIT
} type_of_graph;

#endif
