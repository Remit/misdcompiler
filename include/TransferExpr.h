#ifndef TRANSFEREXPR_H
#define TRANSFEREXPR_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef BASEAST_H_
#include "BaseAST.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class TransferExpr : public Base_AST
{
public:
	TransferExpr();
	TransferExpr(std::string a_name_of_var, transfer_direction a_direction) : name_of_var(a_name_of_var), direction(a_direction) { lbl = AST_TRANSFER; }
	~TransferExpr();
	
	void setNameOfVar(std::string a_name_of_var);
	void setDirection(transfer_direction a_direction);
	
	std::string getNameOfVar();
	transfer_direction getDirection();
	
	Base_AST * copyAST();
	
	void print();
	
	virtual Value *generateCode();
	virtual std::string generateStructCode();
	
private:
	std::string name_of_var;
	transfer_direction direction;
	
};

#endif // TRANSFEREXPR_H
