/*******************************************************************************/
/**

\file       GPIO.h
\brief      Macro definitions for registers access and I/O handling
\author     Abraham Tezmol
\version    0.2
\date       09/05/2013
*/
/*******************************************************************************/

#ifndef _GPIO_H        /*prevent duplicated includes*/
#define _GPIO_H

/*-- Includes ----------------------------------------------------------------*/

/** Core modules */
/** MCU derivative information */
#include "MCU_derivative.h"
/** Variable types and common definitions */
#include "typedefs.h"

/*-- Variables ---------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

#define LED1      					34
#define LED2       					35
#define LED3       					36
#define LED4        				37
#define LED5 						38
#define LED6 						39
#define LED7 						40
#define LED8 						41
#define LED9 						42
#define LED10 						44
#define LED_UP 						46
#define LED_DOWN 					47
#define PIN_BUTTON_UP 64
#define PIN_BUTTON_DOWN 65
#define PIN_BUTTON_ANTIPINCH 66


#define BUTTON_UP    		SIU.GPDI[PIN_BUTTON_UP].R
#define BUTTON_DOWN			SIU.GPDI[PIN_BUTTON_DOWN].R
#define BUTTON_ANTIPINCH	SIU.GPDI[PIN_BUTTON_ANTIPINCH].R
#define PRESSED 0
#define NOT_PRESSED 1



#define GPIO_INPUT					0
#define GPIO_OUTPUT					1

#define GPIO_OPEN_DRAIN_DISABLE		0
#define GPIO_OPEN_DRAIN_ENABLE		1

/*-- Macros ------------------------------------------------------------------*/
/* Indicator LEDs handling */

/** Set LED */ 
#define LED_ON(channel)                     (SIU.GPDO[channel].B.PDO =  1)
/** Clear LED */ 
#define LED_OFF(channel)                    (SIU.GPDO[channel].B.PDO =  0)
/** Toggle LED */ 
#define LED_TOGGLE(channel)                 (SIU.GPDO[channel].B.PDO ^= 1) 

/*-- Function Prototypes -----------------------------------------------------*/

void vfnGPIO_Init_channel(uint8_t channel, uint8_t input_output, uint8_t Open_drain);
void vfnGPIO_Output(uint8_t channel, uint8_t logical_value);
void vfnGPIO_FlashMainLED(void);
void vfnGPIO_LED_Init(void);


#endif /* _GPIO_H */

/*******************************************************************************/
