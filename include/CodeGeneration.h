#ifndef CODEGENERATION_H_
#define CODEGENERATION_H_

#include "/usr/include/llvm/IR/DerivedTypes.h"
#include "/usr/include/llvm/IR/LLVMContext.h"
#include "/usr/include/llvm/IR/Module.h"
#include "/usr/include/llvm/IR/Verifier.h"
#include "/usr/include/llvm/IR/IRBuilder.h"

using namespace llvm;
extern LLVMContext GlobalContext;
extern IRBuilder<> Builder;
extern Module * GlobalModule;
extern std::map<std::string, AllocaInst *> NamedValues;

#endif