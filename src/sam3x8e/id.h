/*
 * @file pid.h
 * @brief Peripheral Identifiers
 * @details A peripheral identifier is required for the control of the
 * peripheral interrupt with the Nested Vectored Interrupt Controller
 * and for the control of the peripheral clock with the
 * Power Management Controller.
 * @details This file is automatically included in pmc.h.
 *
 * @author Saeed Ghasemi
 * @author Mathias Beckius
 * @date 27 September, 2014
 */

#ifndef ID_H_
#define ID_H_

#define ID_SUPC  		(0)		///<Supply Controller
#define ID_RSTC  		(1) 	///<Reset Controller
#define ID_RTC   		(2) 	///<Real Time Clock
#define ID_RTT   		(3) 	///<Real Time Timer
#define ID_WDG   		(4) 	///<Watchdog Timer
#define ID_PMC   		(5) 	///<Power Management Controller
#define ID_EEFC0 		(6) 	///<Enhanced Flash Controller 0
#define ID_EEFC1 		(7) 	///<Enhanced Flash Controller 1
#define ID_UART			(8) 	///<Universal Asynchronous Receiver Transceiver
#define ID_SMC_SDRAMC 	(9) 	///<Static Memory Controller / Synchronous Dynamic RAM Controller
#define ID_SDRAMC 		(10) 	///<Synchronous Dynamic RAM Controller
#define ID_PIOA 		(11) 	///<Parallel I/O Controller A
#define ID_PIOB 		(12) 	///<Parallel I/O Controller B
#define ID_PIOC 		(13) 	///<Parallel I/O Controller C
#define ID_PIOD 		(14) 	///<Parallel I/O Controller D
#define ID_PIOE 		(15) 	///<Parallel I/O Controller E
#define ID_PIOF 		(16) 	///<Parallel I/O Controller F
#define ID_USART0 		(17) 	///<USART 0
#define ID_USART1 		(18) 	///<USART 1
#define ID_USART2 		(19) 	///<USART 2
#define ID_USART3 		(20) 	///<USART 3
#define ID_HSMCI 		(21) 	///<High Speed Multimedia Card Interface
#define ID_TWI0 		(22) 	///<Two-Wire Interface 0
#define ID_TWI1 		(23) 	///<Two-Wire Interface 1
#define ID_SPI0 		(24) 	///<Serial Peripheral Interface 0
#define ID_SPI1 		(25) 	///<Serial Peripheral Interface 1
#define ID_SSC 			(26) 	///<Synchronous Serial Controller
#define ID_TC0 			(27) 	///<Timer Counter 0
#define ID_TC1 			(28) 	///<Timer Counter 1
#define ID_TC2 			(29) 	///<Timer Counter 2
#define ID_TC3 			(30) 	///<Timer Counter 3
#define ID_TC4 			(31) 	///<Timer Counter 4
#define ID_TC5 			(32) 	///<Timer Counter 5
#define ID_TC6 			(33) 	///<Timer Counter 6
#define ID_TC7 			(34) 	///<Timer Counter 7
#define ID_TC8 			(35) 	///<Timer Counter 8
#define ID_PWM 			(36) 	///<Pulse Width Modulation Controller
#define ID_ADC 			(37) 	///<ADC Controller
#define ID_DACC 		(38) 	///<DAC Controller
#define ID_DMAC 		(39) 	///<DMA Controller
#define ID_UOTGHS	 	(40) 	///<USB OTG High Speed
#define ID_TRNG 		(41) 	///<True Random Number Generator
#define ID_EMAC 		(42) 	///<Ethernet MAC
#define ID_CAN0 		(43) 	///<CAN Controller 0
#define ID_CAN1 		(44) 	///<CAN Controller 1

#define ID_MIN			(0)
#define ID_MAX			(44)


#endif
