#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <stdio.h>

//Initialize the port and pin as outputs.
void GPIOinitOut(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIODIR |= (1 << pinNum);
	}
	else if (portNum == 1)
	{
		LPC_GPIO1->FIODIR |= (1 << pinNum);
	}
	else if (portNum == 2)
	{
		LPC_GPIO2->FIODIR |= (1 << pinNum);
	}
	else
	{
		puts("Not a valid port!\n");
	}
}

//Initialize the port and pin as inputs.
void GPIOinitIn(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIODIR &= ~(1 << pinNum);
	}
	else if (portNum == 1)
	{
		LPC_GPIO1->FIODIR &= ~(1 << pinNum);
	}
	else if (portNum == 2)
	{
		LPC_GPIO2->FIODIR &= ~(1 << pinNum);
	}
	else
	{
		puts("Not a valid port!\n");
	}
}

void setGPIO(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIOSET = (1 << pinNum);
		printf("Pin 0.%d has been set.\n",pinNum);
	}
	//Can be used to set pins on other ports for future modification
	else
	{
		puts("Only port 0 is used, try again!\n");
	}
}

//Deactivate the pin
void clearGPIO(uint8_t portNum, uint32_t pinNum)
{
	if (portNum == 0)
	{
		LPC_GPIO0->FIOCLR = (1 << pinNum);
		printf("Pin 0.%d has been cleared.\n", pinNum);
	}
	//Can be used to clear pins on other ports for future modification
	else
	{
		puts("Only port 0 is used, try again!\n");
	}
}

int main(void)
{
    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    //Set pin 0.2 as input
	GPIOinitIn(0,2);
	//Set pin 0.3 as output
	GPIOinitOut(0,3);
	//Sense input
	int input = 0;

    while(1)
    {
    	printf("Enter 1 to activate LED.\nEnter 0 to deactivate LED.\n");
        scanf("%d", &i);

        //Detect pin 0.2
        input = LPC_GPIO0->FIOPIN & (1 << 2);

        //=================================

    	if(input)
    	{
    		//Senses power from pin 0.2
    		printf("Input Received!\n");
    	}
    	else
    	{
    		//Loses power from pin 0.2
    		printf("No input found.\n");
    	}

    	//==================================

		if (i == 1)
		{
			//Activate pin 0.3
			setGPIO(0,3);
		}
		else if (i == 0){
			//Clear pin 0.3
			clearGPIO(0, 3);
		}
		else
		{
			puts("Not a valid option!\n");
		}
    }
    //0 should never be returned, due to infinite while loop
    return 0;
}
