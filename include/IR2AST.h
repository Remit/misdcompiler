#ifndef IR2AST_
#define IR2AST_

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef IRGRAPH_H_
#include "IRGraph.h"
#endif

#ifndef IFEXPRESSION_H_
#include "IfExpression.h"
#endif

#ifndef WHILELOOP_H_
#include "WhileLoop.h"
#endif

#ifndef FORLOOP_H_
#include "ForLoop.h"
#endif

#ifndef SEQUENCEAST_H_
#include "SequenceAST.h"
#endif

#ifndef BINARYEXPRESSION_H_
#include "BinaryExpression.h"
#endif

Base_AST * convertIRtoAST(IR_Graph * graph);
IfExpression * AST_st_if(int node_id, IR_Graph * graph);
WhileLoop * AST_st_whileloop(int node_id, IR_Graph * graph);
ForLoop * AST_st_forloop(int node_id, IR_Graph * graph);

#endif