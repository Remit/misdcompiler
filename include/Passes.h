#ifndef PASSES_H
#define PASSES_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef IRGRAPH_H_
#include "IRGraph.h"
#endif

#ifndef ALGORITHM_
#include "Algorithm.h"
#endif

#ifndef IR2AST_
#include "IR2AST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

#ifndef MISD_IOCTL_H
#include "misd.h"
#endif

#include <fcntl.h>
#include "Timestamp.h"

int Compile(visualization_option option_vis, ast_IR_option option_ast_IR, std::string ast_filename, asm_IR_option option_asm_IR, std::string asm_filename, IR_Graph * src_result_graph, std::string out_filename, int iteration, std::string in_filename, TimeStamp * ts);
int IRDecompositionPass(IR_Graph* al_graph, IR_Graph* sp_graph, IR_Graph * src_result_graph, visualization_option option_vis);
int IR2ASTConversionPass(SequenceAST* al_AST, SequenceAST* sp_AST, IR_Graph* al_graph, IR_Graph* sp_graph, ast_IR_option option_ast_IR, std::string ast_filename);
int AST2ASMConversionPass(SequenceAST* al_AST, SequenceAST* sp_AST, asm_IR_option option_asm_IR, std::string asm_filename);

void create_index(std::string js_name);

#endif // PASSES_H