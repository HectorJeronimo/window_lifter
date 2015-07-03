/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         dummy.c
* Instance:         RPL_1
* %version:         1.0 
* %created_by:      Hector Cuellar
* %date_created:    Fri Jun  26 2015 
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file contain the functions that control all module */
/* of window lifter                                                           */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 26/06/2015  |                               | Hector Cuellar   */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
#include "typedefs.h"
/** Own headers */
#include "dummy.h"
/* GPIO routines prototypes */ 
#include "GPIO.h"
/** Used modules */


/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/
typedef struct 
{
	T_UBYTE bi_AntiPinch:1; // 0 o 1
	T_UBYTE bi_ModeAutomaticUp :1; // 0 o 1
	T_UBYTE bi_SleepModule:1;// 0 o 1
	T_UBYTE bi_ModeAutomaticDown:1;// 0 o 1
	T_UBYTE bi4_LedLevel:4; //range from 0 al 10	
}S_FLAGS;

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

S_FLAGS rs_flags = {0,0,0,0,0};
T_UWORD ruw_timer_transition = 0;
T_UWORD ruw_timer_press_up = 0;
T_UWORD ruw_timer_press_down = 0;
T_UWORD ruw_timer_press_antpinch = 0;
T_UWORD ruw_timer_sleep = 0;

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/
#define ON 1
#define OFF 0
#define VALID_PRESS 20
#define TIME_MANUAL_MODE 1000
#define TIME_SLEEP 10000
#define TIME_TRANSITION 800
#define LAST_LED_ON 10
#define FIRST_LED_ON 1
#define ALL_LEDS_OFF 0
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Functions prototypes
*****************************************************************************************************/
void check_button_antipinch(void);
void check_button_down(void);
void check_button_up(void);
void turnOffLeds(void);
void turnOnLeds(void);
void turnLeds( T_UBYTE lub_led, T_UBYTE lub_mode);


/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/**************************************************************
 *  Name                 : turnLeds
 *  Description          : Turn on/off a specific Led
 *  Parameters           : T_UBYTE lub_led is a number of the led that you want to turn off/on
 						   T_UBYTE lub_mode specifies if is turn off or turn on
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void turnLeds( T_UBYTE lub_led, T_UBYTE lub_mode)
{	
	switch(lub_led)
	{
		case 1:
			if(lub_mode == 1)
				LED_ON(LED1);
			else
			    LED_OFF(LED1);
		break;
		case 2:
			if(lub_mode == 1)
				LED_ON(LED2);
			else
				LED_OFF(LED2);
		break;
		case 3:
			if(lub_mode == 1)
				LED_ON(LED3);
			else
				LED_OFF(LED3);
		break;
		case 4:
			if(lub_mode == 1)
				LED_ON(LED4);
			else
				LED_OFF(LED4);
		break;
		case 5:
			if(lub_mode == 1)
				LED_ON(LED5);
			else
				LED_OFF(LED5);
		break;
		case 6:
			if(lub_mode == 1)
				LED_ON(LED6);
			else
				LED_OFF(LED6);
		break;
		case 7:
			if(lub_mode == 1)
				LED_ON(LED7);
			else
				LED_OFF(LED7);
		break;
		case 8:
			if(lub_mode == 1)
				LED_ON(LED8);
			else
				LED_OFF(LED8);
		break;
		case 9:
			if(lub_mode == 1)
				LED_ON(LED9);
			else
				LED_OFF(LED9);
		break;
		case 10:
			if(lub_mode == 1)
				LED_ON(LED10);
			else
				LED_OFF(LED10);
		break;
		default :
		break;
		
	}	
}

/**************************************************************
 *  Name                 : turnOnLeds
 *  Description          : It controls the turn on between each 
                           led respecting the time of each 
                           transition of 400 milliseconds
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void turnOnLeds(void)
{
	LED_ON(LED_UP);
	if(rs_flags.bi4_LedLevel == ALL_LEDS_OFF)
	{
		rs_flags.bi4_LedLevel++;
		turnLeds(rs_flags.bi4_LedLevel,ON);
		ruw_timer_transition = 0;	
	}
	else
	{
		if( ( ruw_timer_transition == TIME_TRANSITION) && ( rs_flags.bi4_LedLevel < LAST_LED_ON ) )
		{
			rs_flags.bi4_LedLevel++;
			turnLeds(rs_flags.bi4_LedLevel,ON);
			ruw_timer_transition = 0;
		}
	}
	ruw_timer_transition++;
}

/**************************************************************
 *  Name                 :  turnOffLeds
 *  Description          :	It controls the turn off between each
 							led respecting the time of each 
 							transition of 400 milliseconds
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void turnOffLeds(void)
{
	LED_ON(LED_DOWN);
	if(rs_flags.bi4_LedLevel == LAST_LED_ON)
	{
		turnLeds(rs_flags.bi4_LedLevel,OFF);
		rs_flags.bi4_LedLevel--;
		ruw_timer_transition = 0;
	}
	else
	{
		if( ( ruw_timer_transition == TIME_TRANSITION) && (rs_flags.bi4_LedLevel >= FIRST_LED_ON ) )
		{
			turnLeds(rs_flags.bi4_LedLevel,OFF);
			rs_flags.bi4_LedLevel--;
			ruw_timer_transition = 0;
		}
	}
	ruw_timer_transition++;
}

/**************************************************************
 *  Name                 :  check_button_up	
 *  Description          :	It controls the events in button up 
 							and the states caused by this button
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void check_button_up(void)
{
	if( BUTTON_UP == PRESSED && rs_flags.bi_ModeAutomaticDown == OFF && BUTTON_DOWN == NOT_PRESSED && rs_flags.bi_SleepModule == OFF && rs_flags.bi_AntiPinch == OFF)
	{
		ruw_timer_press_up++;
		if(ruw_timer_press_up >= VALID_PRESS)
		{
			if ( ruw_timer_press_up < TIME_MANUAL_MODE ) 
			{
				rs_flags.bi_ModeAutomaticUp = ON;
				turnOnLeds();
			}
			else
			if(ruw_timer_press_up >= TIME_MANUAL_MODE)
			{
				rs_flags.bi_ModeAutomaticUp = OFF;
				turnOnLeds();
			}
		}			
	}
	else
		if(rs_flags.bi_ModeAutomaticUp == ON)
		{
			turnOnLeds();
			if(rs_flags.bi4_LedLevel == LAST_LED_ON)
			{
				rs_flags.bi_ModeAutomaticUp = OFF;	
			}	
		}
		else
		{
			LED_OFF(LED_UP);
			ruw_timer_press_up = 0;
		}
	
}

/**************************************************************
 *  Name                 :  check_button_down
 *  Description          :	It controls the events in button down 
 							and the states caused by this button.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void check_button_down(void)
{
	if( BUTTON_DOWN == PRESSED && rs_flags.bi_ModeAutomaticUp == OFF && BUTTON_UP == NOT_PRESSED && rs_flags.bi_SleepModule == OFF)
	{
		ruw_timer_press_down++;
		if(ruw_timer_press_down >= VALID_PRESS)
		{
			if ( ruw_timer_press_down < TIME_MANUAL_MODE ) 
			{
				rs_flags.bi_ModeAutomaticDown = ON;
				turnOffLeds();
			}
			else
			if(ruw_timer_press_down >= TIME_MANUAL_MODE)
			{
				rs_flags.bi_ModeAutomaticDown = OFF;
				turnOffLeds();
			}
		}	
	}
	else
		if(rs_flags.bi_ModeAutomaticDown == ON)
		{
			turnOffLeds();
			if(rs_flags.bi4_LedLevel == ALL_LEDS_OFF)
			{
				rs_flags.bi_ModeAutomaticDown = OFF;	
			}		
		}
		else
		{
			LED_OFF(LED_DOWN);
			ruw_timer_press_down = 0;
		}
}

/**************************************************************
 *  Name                 :  check_button_antipinch
 *  Description          :	It controls the events in button 
 							anti-pinch and the states caused by 
 							this button. 
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void check_button_antipinch(void)
{
	if( BUTTON_ANTIPINCH == PRESSED && rs_flags.bi4_LedLevel < LAST_LED_ON && ruw_timer_press_up > 0) 
	{
		ruw_timer_press_antpinch++;
		if(ruw_timer_press_antpinch >= VALID_PRESS)
		{
			rs_flags.bi_AntiPinch = ON;
			rs_flags.bi_ModeAutomaticUp = OFF;
			turnOffLeds();
		}
	}
	else
		if(rs_flags.bi_AntiPinch == ON)
		{	
			turnOffLeds();
			if(rs_flags.bi4_LedLevel == ALL_LEDS_OFF )
			{
				rs_flags.bi_AntiPinch = OFF;
				rs_flags.bi_SleepModule = ON;	
			}
		}
		else
			if(rs_flags.bi_SleepModule == ON)
			{
				ruw_timer_sleep++;
				if( ruw_timer_sleep == TIME_SLEEP )
				{
					ruw_timer_sleep = 0;
					rs_flags.bi_SleepModule = OFF;
				}	
			}
			else
			{
				ruw_timer_press_antpinch = 0;
			}
}

/**************************************************************
 *  Name                 : control_500microseconds
 *  Description          : This function controls the calls to 
 					       functions that control an event in a 
 					       specific button.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void control_500microseconds(void)
{
	check_button_up();
	
	check_button_down();
	
	check_button_antipinch();
}

/**************************************************************
 *  Name                 : dummy_endless_loop	
 *  Description          :	This function creates a infinite 
 							loop
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :   No
 **************************************************************/
void dummy_endless_loop(void)
{

	for(;;){}

}