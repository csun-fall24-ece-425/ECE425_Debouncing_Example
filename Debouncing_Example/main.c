/*
 * @file main.c
 *
 * @brief Main source code for the Debouncing_Example program.
 *
 * @author Aaron Nanas
 */

#include "TM4C123GH6PM.h"
#include "GPIO.h"
#include "PMOD_BTN_Interrupt.h"
#include "EduBase_Button_Interrupt.h"
#include "Seven_Segment_Display.h"

// Declare the user-defined function prototype for PMOD_BTN_Interrupt
void PMOD_BTN_Handler(uint8_t pmod_btn_status);

// Declare the user-defined function prototype for EduBase_Button_Interrupt
void EduBase_Button_Handler(uint8_t edubase_button_status);

// Initialize a global variable for an 8-bit counter
static uint8_t counter = 0;

int main(void)
{	
	// Initialize the SysTick timer used to provide blocking delay functions
	SysTick_Delay_Init();
	
	// Initialize the Seven Segment Display (Port B and C)
	Seven_Segment_Display_Init();
	
	// Initialize the push buttons on the PMOD BTN module (Port A)
	PMOD_BTN_Interrupt_Init(&PMOD_BTN_Handler);
	
	// Initialize the SW2 and SW3 on the EduBase board with interrupts enabled (Port D)
	EduBase_Button_Interrupt_Init(&EduBase_Button_Handler);
	
	// Initialize the LEDs on the EduBase board (Port B)
	EduBase_LEDs_Init();
	
	while(1)
	{
		Seven_Segment_Display(counter);
		EduBase_LEDs_Output(counter);
	}
}

/**
 * @brief
 *
 * @param
 *
 * @return
 */
void EduBase_Button_Handler(uint8_t edubase_button_status)
{
	switch(edubase_button_status)
	{
		// SW2 (PD3) is pressed
		case 0x04:
		{
			if (counter >= 15)
			{
				counter = 0;
			}
			else
			{
				counter = counter + 1;
			}
			break;
		}
		
		// SW3 (PD2) is pressed
		case 0x08:
		{
			if (counter <= 0)
			{
				counter = 15;
			}
			else
			{
				counter = counter - 1;
			}
			break;
		}
		
		default:
		{
			break;
		}
	}
}

/**
 * @brief
 *
 * @param
 *
 * @return
 */
void PMOD_BTN_Handler(uint8_t pmod_btn_status)
{
	switch(pmod_btn_status)
	{
		// BTN0 (PA2) is pressed
		case 0x04:
		{
			if (counter >= 15)
			{
				counter = 0;
			}
			else
			{
				counter = counter + 1;
			}
			break;
		}
		
		// BTN1 (PA3) is pressed
		case 0x08:
		{
			if (counter <= 0)
			{
				counter = 15;
			}
			else
			{
				counter = counter - 1;
			}
			break;
		}
		
		// BTN2 (PA4) is pressed
		case 0x10:
		{
			break;
		}
		
		// BTN3 (PA5) is pressed
		case 0x20:
		{
			break;
		}
		
		default:
		{
			break;
		}
	}
}
