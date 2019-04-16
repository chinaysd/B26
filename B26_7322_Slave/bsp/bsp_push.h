#ifndef _BSP_PUSH_H_
#define _BSP_PUSH_H_


#include "sc92f732x_c.h"
#include "TimeOut.h"
#include "bsp_uart.h"


#define PushReset_True      1
#define PushReset_False     0

typedef enum
{
	PUSH_STOP,
	PUSH_OPEN,
	PUSH_CLOSE
}
PUSH_STATUS;

typedef enum
{
	PUSHA_ADDR,
       PUSHB_ADDR,
       PUSHC_ADDR,
       PUSHD_ADDR
}
PUSH_ADDR;

/*座部推杆PUSHA*/
#define PUSHA_OPEN_PORT        P2               
#define PUSHA_OPEN_PIN           P24
#define PUSHA_OPEN_SET(X)      ((X)?(PUSHA_OPEN_PIN=1):(PUSHA_OPEN_PIN=0))

#define PUSHA_CLOSE_PORT       P2
#define PUSHA_CLOSE_PIN          P25
#define PUSHA_CLOSE_SET(X)      ((X)?(PUSHA_CLOSE_PIN=1):(PUSHA_CLOSE_PIN=0))

/*头部推杆PUSHB*/
#define PUSHB_OPEN_PORT         P2
#define PUSHB_OPEN_PIN            P21
#define PUSHB_OPEN_SET(X)       ((X)?(PUSHB_OPEN_PIN=1):(PUSHB_OPEN_PIN=0))

#define PUSHB_CLOSE_PORT        P2
#define PUSHB_CLOSE_PIN           P20
#define PUSHB_CLOSE_SET(X)      ((X)?(PUSHB_CLOSE_PIN=1):(PUSHB_CLOSE_PIN=0))

/*腰部推杆  PUSHC*/
#define PUSHC_OPEN_PORT          P0
#define PUSHC_OPEN_PIN             P05
#define PUSHC_OPEN_SET(X)        ((X)?(PUSHC_OPEN_PIN=1):(PUSHC_OPEN_PIN=0))

#define PUSHC_CLOSE_PORT         P0
#define PUSHC_CLOSE_PIN            P04
#define PUSHC_CLOSE_SET(X)        ((X)?(PUSHC_CLOSE_PIN=1):(PUSHC_CLOSE_PIN=0))


/**桌板推杆PUSHD*/
#define PUSHD_OPEN_PORT          P0           
#define PUSHD_OPEN_PIN            P02
#define PUSHD_OPEN_SET(X)        ((X)?(PUSHD_OPEN_PIN=1):(PUSHD_OPEN_PIN=0))

#define PUSHD_CLOSE_PORT         P0
#define PUSHD_CLOSE_PIN            P03
#define PUSHD_CLOSE_SET(X)       ((X)?(PUSHD_CLOSE_PIN=1):(PUSHD_CLOSE_PIN=0))


void Push_Init(void);
void Push_Handle(PUSH_ADDR addr,PUSH_STATUS Push_Status);

void PushResetHandle(void);
void PushResetBackHandle(void);

#endif

