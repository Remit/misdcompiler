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
	void setSimpleType(int a_simple_type);

	data_type getDataType();
	int getSimpleType();

private:
	// Link to a corresponding identifier in data table.
	data_type dataType;
	int simple_type;
};

#endif /* IRDATANODE_H_ */
