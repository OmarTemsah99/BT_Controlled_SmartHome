/*
 * main.c
 *
 *  Created on: Apr 8, 2023
 *      Author: Temsah
 */

#include <stdio.h>
#include "Functions.h"
#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "Dio.h"
#include "Led.h"
#include "Buzzer.h"
#include "Gie.h"
#include "Interrupts.h"
#include "Gpt.h"
#include "Pwm.h"
#include "Wdt.h"
#include "Uart.h"
#include "LPM.h"
#include "Delay.h"

/**
 * @brief interrupt funtion that uses timer0 to count each overflow the counter starts from 6 and resets at 256
 * 		  and keeps incrementing until the counter reaches 1800 then resets the avr and the cycle repeats unless
 *  	  the the user inputs something then the counters resets the total time that passes in real time is 60 sec.
 *
 * @param overflow_counter 	: counter that stores the number of overflows that happend in timer0
 *
 */

volatile u16 overflow_counter = 0;

/* Timer0 Interrupt function */
void Handler_Tim0_OVF(void)
{
	overflow_counter++;
	Wdt_SetTimeOut(WDT_TIMEOUT_2100_MS);
	Wdt_Enable();
	Wdt_Refresh();
	if (overflow_counter == 1800)
	{
		overflow_counter = 0;
		Reset_AVR();
	}
}

int main(void)
{
	/* Varibles */
	/**
	 * @brief varibles to be used to store or compare data recived.
	 *
	 * @param Users 	: registered usernames
	 * @param user 		: recieved username string from UART
	 * @param Password 	: registered Password for each user respectively
	 * @param pass 		: recieved password string from UART
	 * @param order 	: recieved order from UART
	 * @param angle 	: selects the angle at which the servo goes to
	 * @param flagA 	: flag used to not allow the send of an already working funtion
	 * @param flagB 	: flag used to not allow the send of an already working funtion
	 * @param flagDoor 	: flag used to not allow the send of an already working funtion
	 * @param flagLPM 	: flag used to not allow the send of an already working funtion
	 *
	 */

	u8 tries;
	u8 validation;
	u8 flagA = 0;
	u8 flagB = 0;
	u8 flagDoor = 0;
	u8 flagLPM = 0;
	u16 angle;
	u8 pass[10];
	u8 user[10];
	u8 order[10];
	u8 Users[10][10] = {"omar", "abdo", "medo", "tarek", "crocs", "temsah", "temo", "tms", "tamsoh", "lacost"};
	u8 Password[10][10] = {"2011", "0102", "0122", "0623", "1234", "4321", "5678", "8765", "0909", "9090"};

	/* Starting code */
	/**
	 * @brief init functions and preparations functions for main code.
	 *
	 * @param Uart_Init 				: initilize function for UART
	 * @param Led_Init 					: initilize function for LED
	 * @param Buzzer_Init 				: initilize function for BUZZER
	 * @param Pwm_Init 					: initilize function for PWM
	 * @param Pwm_SetICR 				: sets ICR value.
	 * @param Pwm_Start 				: selects PWM channel to be used as a pinout and
	 * 									  sets the prescaler value of the channel
	 * @param Pwm_SetTimeOn				: moves the servo motor into starting postion (locked Door)
	 *
	 * @param Gpt_Init 					: initilize function for the avr timers
	 * @param Gpt_Start 				: sets the timer prescaler and starts the clock cycle
	 * @param Gpt_SetCallback 			: sets the callback interrupt function and the interrupt cause
	 * @param Gpt_EnableNotification 	: enable the timer interrupt source
	 * @param Gpt_SetCounterValue 		: set the starting count value from 0 - 256
	 *
	 * @param Gie_Enable 				: enables global interrupt
	 *
	 */

	/* Uart communaction init */
	Uart_Init();

	/* LEDS init */
	Led_Init(LED_PIN);
	Led_Init(LED2_PIN);

	/* Buzzer init */
	Buzzer_Init(Buzzer_PIN);

	/* PWM init */
	Pwm_Init(PWM_CHANNEL_OC1A, PWM_MODE_FAST_ICR1);
	Pwm_SetICR(20000);
	Pwm_Start(PWM_CHANNEL_OC1A, PWM_PRESCALER_8);

	/* Timer0 init */
	Gpt_Init(GPT_CHANNEL_TIM0, &Gpt_Configuration[0]);
	Gpt_Start(GPT_CHANNEL_TIM0, GPT_PRESCALER_1024);
	Gpt_SetCallback(GPT_INT_SOURCE_TIM0_OVF, Handler_Tim0_OVF);
	Gpt_EnableNotification(GPT_INT_SOURCE_TIM0_OVF);
	Gpt_SetCounterValue(GPT_CHANNEL_TIM0, 6);

	/*Global Interrupts init */
	Gie_Enable();

	/* clears the lowpower mode SE bit and sits it to zero */
	LPM_Disable();

	angle = 2000;
	Pwm_SetTimeOn(PWM_CHANNEL_OC1A, angle);
	Delay(2000);
	Uart_SendString("\n Send Anything to Start");
	Uart_Receive();
	overflow_counter = 0;

	/* Main Code */
	/**
	 * @brief while loop that collects all subsytems of mobile controlled home.
	 *
	 */

	while (1)
	{
		overflow_counter = 0;
		/* login subsystem */
		/**
		 * @brief the login subsytem takes a username and password input through
		 * UART recive function and checks it using string compare function with the preregisterd
		 * usernames and pass words if checked out the user is welcomed and can start making orders,
		 * if failed the systems send a massege that the username or password is wrong, at the third
		 * time the systems lock for a minute and activites a buzzer for 10 sec.
		 *
		 */
		for (tries = 0; tries < 3; tries++)
		{
			overflow_counter = 0;
			/* funtions that send a request for data to be enterd and to recieve data sent */
			Uart_SendString("\n Please Enter your ID:");
			Uart_Receive_String(user);
			overflow_counter = 0;
			Uart_SendString("\n Please Enter your Password:");
			Uart_Receive_String(pass);
			overflow_counter = 0;
			/* for loop that checks if the user and his unique password checks togther
			 *  if not sends wrong password or username.
			 */
			for (validation = 0; validation <= 10; validation++)
			{
				overflow_counter = 0;
				if (CompareStrings(user, Users[validation]) && CompareStrings(pass, Password[validation]))
				{
					overflow_counter = 0;
					Uart_SendString("Hi ");
					Uart_SendArray(user);
					flagA = 0;
					flagB = 0;
					flagDoor = 0;

					/* while loop function that takes orders from user indefinitly until logged out or inactive for 60sec*/
					while (1)
					{
						overflow_counter = 0;
						Uart_SendString("\n Please Enter Your Order:");
						Uart_Receive_String(order);

						if (CompareStrings(order, "LedOnA"))
						{
							if (flagA == 0)
							{
								Uart_SendString("\n RoomA Led is ON");
								Led_TurnOn(LED_PIN);
								flagA = 1;
							}
							else
							{
								Uart_SendString("\n Please Enter Proper Order");
							}
						}
						else if (CompareStrings(order, "LedOffA"))
						{
							if (flagA == 1)
							{
								Uart_SendString("\n RoomA Led is Off");
								Led_TurnOff(LED_PIN);
								flagA = 0;
							}
							else
							{
								Uart_SendString("\n Please Enter Proper Order");
							}
						}
						else if (CompareStrings(order, "LedOnB"))
						{
							if (flagB == 0)
							{
								Uart_SendString("\n RoomB Led is ON");
								Led_TurnOn(LED2_PIN);
								flagB = 1;
							}
							else
							{
								Uart_SendString("\n Please Enter Proper Order");
							}
						}
						else if (CompareStrings(order, "LedOffB"))
						{
							if (flagB == 1)
							{
								Uart_SendString("\n RoomB Led is Off");
								Led_TurnOff(LED2_PIN);
								flagB = 0;
							}
							else
							{
								Uart_SendString("\n Please Enter Proper Order");
							}
						}
						else if (CompareStrings(order, "Open"))
						{
							if (flagDoor == 0)
							{
								Uart_SendString("\n Door is Open");
								angle = 550;
								Pwm_SetTimeOn(PWM_CHANNEL_OC1A, angle);
								Delay(2000);
								flagDoor = 1;
							}
							else
							{
								Uart_SendString("\n Please Enter Proper Order");
							}
						}
						else if (CompareStrings(order, "Lock"))
						{
							if (flagDoor == 1)
							{
								Uart_SendString("\n Door is closed");
								angle = 2000;
								Pwm_SetTimeOn(PWM_CHANNEL_OC1A, angle);
								Delay(2000);
								flagDoor = 0;
							}
							else
							{
								Uart_SendString("\n Please Enter Proper Order");
							}
						}
						else if (CompareStrings(order, "PowerSaveMode"))
						{
							if (flagLPM == 0)
							{
								Uart_SendString("\n Entering power save mode ");
								Uart_SendString("\n The system is in power save mode ");
								Gpt_Stop(GPT_CHANNEL_TIM0);
								Wdt_Disable();
								flagLPM = 1;
								LowPower_Mode(POWER_SAVE);
							}
							else
							{
								Uart_SendString("\n The system already in power save mode ");
								Uart_SendString("\n Please Enter Proper Order");
							}
						}
						else if (CompareStrings(order, "LogOut"))
						{
							Uart_SendString("\n GoodBye ");
							Uart_SendArray(user);
							Uart_SendString("\n (^^)");
							Reset_AVR();
						}
						else
						{
							Uart_SendString("\n Please Enter Proper Order");
						}
					}
				}
			}
			Uart_SendString("\n Wrong User or Pass Please Try Again");
		}
		Uart_SendString("\n no more tries");
		for (u8 i = 0; i < 10; i++)
		{
			Buzzer_On(Buzzer_PIN);
			Delay(250);
			Buzzer_Off(Buzzer_PIN);
			Delay(250);
		}
	}
}
