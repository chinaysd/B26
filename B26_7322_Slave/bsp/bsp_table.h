#ifndef _BSP_TABLE_H_
#define _BSP_TABLE_H_


#include "sc92f732x_c.h"



#define TableKeyPort       P0
#define TableKeyPin         P00

#define TABLE_ENABLE     1
#define TABLE_DISABLE    0

#define TABLE_DOWN       0











void TableKeyInit(void);
unsigned char TableReturnValue(void);






#endif

