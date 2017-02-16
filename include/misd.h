#ifndef MISD_IOCTL_H
#define MISD_IOCTL_H

#include <linux/ioctl.h>

typedef struct //Data structure for the burts IO
misd_burst {
	unsigned int count;		//Words count
	unsigned long *adr;		//Address (IO and MEM space depending of request type)
	unsigned long *data;	//Data (data to be written or read from the device)
} misd_burst;

#define MISD_WRITE_IO _IOWR('q', 1, misd_burst*) 	//universal write operation to device IO port
#define MISD_READ_IO _IOR('q', 2, misd_burst*)		//universal read operation from IO port
#define MISD_WRITE_MEM _IOWR('q', 3, misd_burst*)	//universal write operation to device MEM port
#define MISD_READ_MEM _IOR('q', 4, misd_burst*)		//universal read operation from MEM port
#define MISD_WRITE_LCM _IOWR('q', 5, misd_burst*)	//write operation to the Local Command Memory
#define MISD_READ_LCM _IOR('q', 6, misd_burst*)		//read operation from the Local Command Memory
#define MISD_WRITE_LSM _IOWR('q', 7, misd_burst*)	//write operation to the Local Structure Memory
#define MISD_READ_LSM _IOR('q', 8, misd_burst*)		//readoperation from the Local Structure Memory

//MISD revision
#define MISDTEST
//#define MISD32
//#define MISD64

#endif

