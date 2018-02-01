/****************************************************************************
 *   $Id:: extint.c 5670 2010-11-19 01:33:16Z usb00423                      $
 *   Project: NXP LPC17xx EINT example
 *
 *   Description:
 *     This file contains EINT code example which include EINT 
 *     initialization, EINT interrupt handler, and APIs for EINT.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "extint.h"
#include "timer.h"
#include "uart.h"
#include <time.h>
volatile uint32_t eint0_counter;
extern uint32_t timer0_m0_counter, timer1_m0_counter;
extern uint32_t timer0_m1_counter, timer1_m1_counter;
int key_count1 = 0;
int key_count2 = 1;
int key_count = 0;
int spicy_memes = 0;
int start;

int x0 = 10;
int x1 = 118;
int x2 = 118;
int x3 = 10;

int y0 = 30;
int y1 = 30;
int y2 = 130;
int y3 = 130;

//======================

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Be careful with the port number and location number, because

some of the location may not exist in that port. */

#define PORT_NUM            0

uint8_t src_addr[SSP_BUFSIZE];
uint8_t dest_addr[SSP_BUFSIZE];

#define ST7735_TFTWIDTH 127
#define ST7735_TFTHEIGHT 159

#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_SLPOUT 0x11
#define ST7735_DISPON 0x29

#define swap(x, y) {x = x + y; y = x - y; x = x - y ;}

// defining color values

#define LIGHTBLUE 0x00FFE0
#define GREEN 0x00FF00
#define DARKBLUE 0x000033
#define BLACK 0x000000
#define BLUE 0x0007FF
#define RED 0xFF0000
#define MAGENTA 0x00F81F
#define WHITE 0xFFFFFF
#define PURPLE 0xCC33FF

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)

{

 int16_t slope = abs(y1 - y0) > abs(x1 - x0);

 if (slope) {

  swap(x0, y0);

  swap(x1, y1);

 }

 if (x0 > x1) {

  swap(x0, x1);

  swap(y0, y1);

 }

 int16_t dx, dy;

 dx = x1 - x0;

 dy = abs(y1 - y0);

 int16_t err = dx / 2;

 int16_t ystep;

 if (y0 < y1) {

  ystep = 1;

 }

 else {

  ystep = -1;

 }

 for (; x0 <= x1; x0++) {

  if (slope) {

   drawPixel(y0, x0, color);

  }

  else {

   drawPixel(x0, y0, color);

  }

  err -= dy;

  if (err < 0) {

   y0 += ystep;

   err += dx;

  }

 }

}

//======================

/*****************************************************************************
** Function name:		EINT0_Handler
**
** Descriptions:		external INT handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/


void EINT1_IRQHandler (void){

	LPC_SC->EXTINT = EINT1;

	//LPC_GPIO0->FIODIR |= (1<<2);
	if(LPC_GPIO2->FIOPIN &(1<<11))
	{
		puts("External interrupt detected!");
		key_count ++;  // key_count +1 when receive external interrupt
	    delayMs(0,500);  //delay used as debouncer
	    start = 1;
	}

	if(start == 1){
		if( key_count == (key_count1 + key_count2))
		{
			// Print Green Square
			if(spicy_memes == 1){
				for(int i=0; i<4; i++){
					 drawLine(x0,y0,x1,y1,0x83ff7f);
					 drawLine(x1,y1,x2,y2,0x83ff7f);
					 drawLine(x2,y2,x3,y3,0x83ff7f);
					 drawLine(x3,y3,x0,y0,0x83ff7f);

					lcddelay(50);

					 drawLine(x0,y0,x1,y1,0x00d303);
					 drawLine(x1,y1,x2,y2,0x00d303);
					 drawLine(x2,y2,x3,y3,0x00d303);
					 drawLine(x3,y3,x0,y0,0x00d303);

					lcddelay(50);
				}
				spicy_memes = 0;
			}
			// Print Red Square
			else if(spicy_memes == 0){
				for(int i=0; i<4; i++){
					 drawLine(x0,y0,x1,y1,0xff7c7c);
					 drawLine(x1,y1,x2,y2,0xff7c7c);
					 drawLine(x2,y2,x3,y3,0xff7c7c);
					 drawLine(x3,y3,x0,y0,0xff7c7c);


					 lcddelay(50);

					 drawLine(x0,y0,x1,y1,0xd20000);
					 drawLine(x1,y1,x2,y2,0xd20000);
					 drawLine(x2,y2,x3,y3,0xd20000);
					 drawLine(x3,y3,x0,y0,0xd20000);

					 lcddelay(50);
				}
				spicy_memes = 1;
			}

			key_count1 += key_count2;
			key_count2 ++;                 //increment the count and calculate the number of times needed to turn on and turn off led
										   //press button 1 time to turn on LED,
										   //             2 times to turn off LED,
										   //             3 times to turn on LED
										   //             4 times to turn off LED ...
		}
	}
    LPC_GPIOINT->IO2IntEnR = ((0x01 <<11));
	LPC_GPIOINT->IO2IntClr = 0xFFFFFFFF;
	LPC_GPIOINT->IO0IntClr = 0xFFFFFFFF;

}
/*****************************************************************************
** Function name:		EINTInit
**
** Descriptions:		Initialize external interrupt pin and
**						install interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the interrupt
**						handler can't be installed to the VIC table.
** 
*****************************************************************************/
uint32_t EINTInit( void )
{
	 LPC_PINCON->PINSEL4 &= ~(3 << 22 );  //set P2.11 as EINT1
	 LPC_PINCON->PINSEL4 |= (1 << 22 );
	 LPC_PINCON->PINMODE4 = 0;						// for making pull-up use 00
	 LPC_GPIOINT->IO2IntEnR |= ((0x01 <<11));				/* Port2.10 is rising edge. */
	 LPC_GPIOINT->IO2IntEnF &= ~((0x01 <<11));
	 LPC_SC->EXTMODE = EINT0_EDGE | EINT3_EDGE ;      /* INT1 edge trigger */
	 LPC_SC->EXTPOLAR |= 0;              /* INT0 is falling edge by default */
	 NVIC_EnableIRQ(EINT1_IRQn);
	 return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

