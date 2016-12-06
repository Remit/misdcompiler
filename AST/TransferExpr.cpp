#include "../include/TransferExpr.h"

TransferExpr::TransferExpr() {
	name_of_var = "";
	direction = TR_UNDEFINED;
}

TransferExpr::~TransferExpr() {
}
	
void TransferExpr::setNameOfVar(std::string a_name_of_var) {
	name_of_var = a_name_of_var;
}

void TransferExpr::setDirection(transfer_direction a_direction) {
	direction = a_direction;
}
	
std::string TransferExpr::getNameOfVar() {
	return name_of_var;
}

transfer_direction TransferExpr::getDirection() {
	return direction;
}

Base_AST * TransferExpr::copyAST() {
	TransferExpr * cpy = new TransferExpr(name_of_var, direction);
	
	return cpy;
}

void TransferExpr::print() {
	std::cout << "\n - Transfer expression: ";
	if(direction == TR_SEND) {
		std::cout << " SEND ";
	} else if(direction == TR_RECEIVE) {
		std::cout << " RECEIVE ";
	} else if(direction == TR_UNDEFINED) {
		std::cout << " UNDEFINED ";
	}
	
	std::cout << " variable " << name_of_var;
}