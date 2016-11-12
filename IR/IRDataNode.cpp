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

void IR_DataNode::print() {
	switch(dataType) {
		case IR_DATA_STRUCTURE:
			std::cout << "data structure type";
			break;
		case IR_DATA_SIMPLE:
			std::cout << "simple data type";
			break;
		case IR_DATA_SIMPLE_TMP:
			std::cout << "simple temporary data";
			break;
		case IR_DATA_TAG:
			std::cout << "tag type";
			break;
		case IR_UNDEFINED:
			std::cout << "UNDEFINED type";
			break;
	}
}

std::string IR_DataNode::getPicturePath() {
	std::string pic_path;
	pic_path = "Cytospace/images/";
	proc_type pr = getProcType();
	if((pr == IR_CPU) || (pr == IR_BOTH))
		pic_path += "cpu/";
	else if(pr == IR_SPU)
		pic_path += "spu/";

	switch(dataType) {
	case IR_DATA_STRUCTURE:
		pic_path += "Data_structure";
		break;
	case IR_DATA_SIMPLE:
		pic_path += "Data_simple";
		break;
	case IR_DATA_SIMPLE_TMP:
		pic_path += "Data_simple_tmp";
		break;
	case IR_DATA_TAG:
		pic_path += "Data_tag";
		break;
	case IR_UNDEFINED:
		pic_path += "Data_undefined";
		break;
	}

	pic_path += ".jpg";
	return pic_path;
}
