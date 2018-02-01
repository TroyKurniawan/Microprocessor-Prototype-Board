# Microprocessor-Prototype-Board
This repository holds files related to my Microprocessor Prototype Board. The board was built for my CMPE 127 (Microprocessor Design) Class at San jose State University.

______________________

**Summary**
The Microprocessor Prototype Board is a PCB board equipped with an NXP LPC1796 microcontroller. The board also contains several sub-circuits and components. These parts are the following:
- GPIO Input / Output Testing Circuit
- SPI Flash Memory
- LCD Screen
- Infrared Interrupt Testing Circuit

**GPIO Input / Output Testing Circuit**
The GPIO Input Testing Circuit is a sub-circuit capable of detecting an electrical signal at any GPIO specified pin on the microcontroller. When a signal is received at the pin, a message displays on the IDE console.

The GPIO Output Testing Circuit is a sub-circuit capable of producing a high-voltage output at any specified GPIO pin on the microcontroller. The user is able to use the IDE console to control a GPIO pin and light up and LED.

**SPI Flash Memory**
The SPI Flash Memory Circuit is a sub-circuit capable of storing a text message and preserving it for later use even after the microcontroller is powered off. The circuit uses an AT45 dataflash to store the text message entered in by the user in the IDE.

**LCD Screen**
A 128 x 160 LCD screen is included on the board for general use. The microcontroller is capable of using different functions to draw RGB shapes, lines, and more on the screen.
(Model: 1.8 SPI TFT 128\*160)

**Infrared Interrupt Testing Circuit**
The Infrared Interrupt Testing Circuit is a sub-circuit capable of detecting any infrared signal using an IR receiver and displaying different objects on the LCD screen. My configurations have been setup so that the screen is intially blank. When a signal is received, a flashing green square appears on the screen. When a signal is received again, a flashing red square appears on the screen. The flashing green and red squares then alternate with every subsequent IR signal detected. For this lab, I used a common TV remote control to send IR signals to the IR receiver.

______________________

**Extra Information**
- The program was written in C language.
- Much of the code was provided to me by the professor. Much of my work involved using the framework that my professor established to create the final product.
- The IDE used to control and program the board is called "MCUXpresso" from NXP Semiconductors.
