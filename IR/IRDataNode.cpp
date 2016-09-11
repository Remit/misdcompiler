/*
 * IRDataNode.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "../include/IRDataNode.h"

IR_DataNode::IR_DataNode() {
	// TODO Auto-generated constructor stub

}

IR_DataNode::~IR_DataNode() {
	// TODO Auto-generated destructor stub
}

void IR_DataNode::setDataType(data_type a_dataType) {
	dataType = a_dataType;
}

data_type IR_DataNode::getDataType() {
	return dataType;
}

void IR_DataNode::setSimpleType(int a_simple_type) {
	simple_type = a_simple_type;
}

int IR_DataNode::getSimpleType() {
	return simple_type;
}
