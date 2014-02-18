PingPong
========

Byggern

#Files
##Node 1
- main.c
- setup.h			Config file for ATmega168
- adc.c 			ADC-driver for the ATmega168
- adc.h
- joystick.c 		ADC-joystick using potentiometer driver for ATmega168
- joystick.h
- music_notes.h		Note header file for buzzer
- buzzer.c			Buzzer driver for ATmega168
- buzzer.h
- eeprom.c 			EEPROM-driver for ATmega168
- eeprom.h
- can.c				CAN protocol for MCP2515
- can.h	
- mcp2515.c 		MCP2515 tranciver driver for ATmega168
- mcp2515.h	
- pwm.c				PWM driver for ATmega168
- pwm.h	
- spi.c				SPI-driver for ATmega168
- spi.h
- sram.c			SRAM-driver for ATmega168
- sram.h	
- uart.c			UART/USART driver for ATmega168
- uart.h
- oled.c			OLED-driver for ATmega168
- oled.h	
- menu.c			Menu system for the game
- menu.h
#Fonts
- font_4x6.h		Font header containing structs for fonts and drawings to display on the OLED
- font_5x7.h		 
- font_8x8.h		 
- font_drawings.h	 

##Node 2
- main.c
- ring_buffer.h 	Ring buffer for AVR  
- setup.h 			Config file for 
- DAC_driver.c		DAC-driver for ATmega128	  
- DAC_driver.h		  
- TWI_Master.c 		I2C-driver for ATmega128	  
- TWI_Master.h		  
- adc.c		  		ADC-driver for ATmega128
- adc.h		  
- can.c		  		CAN protocol for MCP2515
- can.h	
- mcp2515.c		 	MCP2515 tranciver driver for ATmega168
- mcp2515.h		  
- control_driver.c 	P and PI regu for the game board
- control_driver.h		  		    
- pwm.c		  		PWM driver for ATmega128
- pwm.h		  		  
- shooter.c		  	Solenoid driver for ATmega128
- shooter.h		  
- spi.c		  		SPI-driver for ATmega128
- spi.h		  
- uart.c		  	UART/USART driver for ATmega128
- uart.h		  