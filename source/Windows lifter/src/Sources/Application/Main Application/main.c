/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         main.c
* Instance:         RPL_1
* %version:         1.0 
* %created_by:      Hector Cuellar
* %date_created:    Fri Jun  26 2015 
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file contain the principal function that initialize*/
/* the GPIO and the PIT and make to callback with interruptions to            */
/* control_500microseconds() that controls the events in the buttons of       */
/* window lifter proyect                                                      */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 26/06/2015  |                               | Hector Cuellar   */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#include "MCU_derivative.h"


/** GPIO funtion prototypes  */
#include    "GPIO.h"
#include    "PIT.h"
#include    "dummy.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/


/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}

T_UBYTE Function1(T_UBYTE *rpub_U8Ptr)
{
	return (*rpub_U8Ptr);
}   

/*****************************************************************************************************
* Definition of global wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/
    
T_UBYTE (*rpfu_PtrToFctn)(T_UBYTE *); /* Our pointer to function */ 

/******************************************************************************************************
* Definition of module wide VARIABLEs 
******************************************************************************************************/

 T_UBYTE rub_Var1 = 0xFA; 
 T_UBYTE rub_Var2; 
 T_UBYTE * rpub_PtrToU8;
 
/******************************************************************************************************
* Code of module wide FUNCTIONS
******************************************************************************************************/

void BackgroundSubsystemTasks(void);


/*~~~~~~~ Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main(void) 
{
	initModesAndClock();
	/* Disable Watchdog */
	disableWatchdog();
	/*Initialize LEDs on TRK-MPC560xB board */
	vfnGPIO_LED_Init();	
	/*Initialize Interrupts */
	INTC_InitINTCInterrupts();
	/*Initialize Exception Handlers */
	EXCEP_InitExceptionHandlers();
	
	PIT_device_init();
    PIT_channel_configure(PIT_CHANNEL_0 , control_500microseconds);// Tenia Test	
    PIT_channel_start(PIT_CHANNEL_0);
    
    /* Enable External Interrupts*/
    enableIrq();
    
	/* Infinite loop */
	dummy_endless_loop();
	for (;;) 
	{

        BackgroundSubsystemTasks();
	}
	

}

/*~~~~~~~ End of Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Background tasks related to Subsystem control */
void BackgroundSubsystemTasks(void) 
{
	rpub_PtrToU8 = &rub_Var1; /* We need to initialize the pointer to be used by our function invocation */

    rpfu_PtrToFctn = &Function1; /* Let's perform our deferencing procedure (initialization) */

    /* Let's first call our function through direct invocation */
    rub_Var2 = Function1(rpub_PtrToU8);
    
    /* Clear var2 in preparation to next invocation */
    rub_Var2 = 0;

    /* Now, perform invocation through our pointer */
    rub_Var2 = rpfu_PtrToFctn(rpub_PtrToU8);

    /* See, I told you, pointers to functions are FUN !! */;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


