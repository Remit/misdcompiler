/*
 * IRDataNode.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IRDATANODE_H_
#define IRDATANODE_H_

#ifndef IRNODE_H_
#include "IRNode.h"
#endif

class IR_DataNode: public IR_Node {
public:
	IR_DataNode();
	virtual ~IR_DataNode();

	void setDataType(data_type a_dataType);
	void setSimpleType(variable_type a_simple_type);
	void setDataName(std::string a_name);
	void setIsTag();
	void unsetIsTag();

	data_type getDataType();
	variable_type getSimpleType();
	std::string getDataName();
	bool isTag();

	// Visualisation
	void print();
	std::string getPicturePath();



private:
//ATTENTION: When adding a field to a node, do not forget to add code to copy method!
	// Link to a corresponding identifier in data table.
	data_type dataType;
	variable_type simple_type;
	std::string name;
	bool istag;
};

#endif /* IRDATANODE_H_ */
