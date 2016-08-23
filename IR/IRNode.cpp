/*
 * IRNode.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "IRNode.h"

IR_Node::IR_Node() {
	id = -1;
	typeOfProcessor = IR_CPU;
}

IR_Node::~IR_Node() {

}

int IR_Node::getID() {
	return id;
}

proc_type IR_Node::getProcType() {
	return typeOfProcessor;
}

void IR_Node::setID(int a_id) {
	id = a_id;
}

void IR_Node::setProcType(proc_type a_ProcType) {
	typeOfProcessor = a_ProcType;
}

