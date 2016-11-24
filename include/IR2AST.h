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

Base_AST * convertIRtoAST(IR_Graph * graph);
IfExpression * AST_st_if(int node_id, IR_Graph * graph);
WhileLoop * AST_st_whileloop(int node_id, IR_Graph * graph);
ForLoop * AST_st_forloop(int node_id, IR_Graph * graph);

#endif