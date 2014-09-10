/*
 * unity_hw_setup.c
 *
 * Created: 2014-09-07 15:43:47
 *  Author: m11p0910
 */ 

//#include <asf.h>
#include "unity_hw_setup.h"
#include "io_uart.h"
// #include "unity.h" //remove this when done!!
// 
// uint16_t test = 1; //remove this when done!!

// EEFC Flash Mode Register 0
uint32_t *const p_EEFC_FMR_0 = (uint32_t *) 0x400E0A00U;
// EEFC Flash Mode Register 1
uint32_t *const p_EEFC_FMR_1 = (uint32_t *) 0x400E0C00U;

static void configure_uart(void) {
	const uart_options_t uart_options = {
		.baudrate = 115200,
		.paritytype = UART_MR_PAR_NO
	};
	uart_config(&uart_options);
}

/**
 * \brief Switch master clock source selection to PLLA clock.
 *
 * \param ul_pres Processor clock prescaler.
 *
 * \retval 0 Success.
 * \retval 1 Timeout error.
 */
static uint32_t pmc_switch_mclk_to_pllack(uint32_t ul_pres)
{
	// PMC Master Clock Register
	uint32_t *const p_PMC_MCKR	= (uint32_t *) 0x400E0630U;
	// PMC Status Register
	//uint32_t *const p_PMC_SR	= (uint32_t *) 0x400E0668U;
	
	uint32_t ul_timeout;
	*p_PMC_MCKR = (*p_PMC_MCKR & (~(0x7u << 4))) | ul_pres;
	//for (ul_timeout = 2048; !(PMC->PMC_SR & (1 << 3)); --ul_timeout) {
	for (ul_timeout = 2048; (PMC_SR & (1 << 3)) == 0; --ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}
	*p_PMC_MCKR = (*p_PMC_MCKR & (~(0x3u))) | 2;
	//for (ul_timeout = 2048; !(PMC->PMC_SR & (1 << 3)); --ul_timeout) {
	for (ul_timeout = 2048; (PMC_SR & (1 << 3)) == 0; --ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}
	return 0;
}

static void systemclock_init(void)
{
	// PMC Clock Generator Main Oscillator Register
	uint32_t *const p_PMC_CKGR_MOR	= (uint32_t *) 0x400E0620U;
	// PMC Status Register
	//uint32_t *const p_PMC_SR		= (uint32_t *) 0x400E0668U;
	// PMC Clock Generator PLLA Register
	uint32_t *const p_CKGR_PLLAR	= (uint32_t *) 0x400E0628U;
	
	/*
	 * Set flash wait state, based upon 84 MHz CPU frequency.
	 * This field defines the number of wait states for read and write operations:
	 *		Number of cycles for Read/Write operations = FWS+1
	 */
	EEFC_FMR_0 = EEFC_FMR_FWS(4);
	EEFC_FMR_1 = EEFC_FMR_FWS(4);

	/* Config system clock setting - Already running from SYSCLK_SRC_MAINCK_4M_RC */
	//Internal 4MHz RC oscillator as master source clock
	/* Enable Main Xtal oscillator */
	*p_PMC_CKGR_MOR = (*p_PMC_CKGR_MOR & ~2) | (0x37 << 16) | 1 | (62 << 8);
	// Wait to the Main XTAL oscillator is stabilized
	while ((PMC_SR & 1) == 0);
	//while (!(PMC->PMC_SR & 1));
	// select the Main Crystal Oscillator
	*p_PMC_CKGR_MOR |= (0x37 << 16) | (1 << 24);
		 
	// oscillator ready? Main Oscillator Selection Status - Selection is in progress
	while ((PMC_SR & (1 << 16)) == 0);
	//while (!(PMC->PMC_SR & (1 << 16)));
			
	// Disable PLLA clock - Always stop PLL first!
	*p_CKGR_PLLAR = (1 << 29);
	// set PMC clock generator
	*p_CKGR_PLLAR = (1 << 29) | (13 << 16) | 1 | (0x3fU << 8);
				
	// wait for PLL to be locked
	while ((PMC_SR & 2) == 0);
	//while (!(PMC->PMC_SR & 2));
		
	// Switch master clock source selection to PLLA clock,
	// selected clock divided by 2
	pmc_switch_mclk_to_pllack(1 << 4);
}

void unity_hw_setup(void) {
	// Watchdog Timer Mode Register
	uint32_t *const p_WDT_MR = (uint32_t *) 0x400E1A54U;
	// Peripheral Clock Enable Register 0
	uint32_t *const p_PMC_PCER0 = (uint32_t *) 0x400E0610U;
	
	//sysclk_init();
	systemclock_init();
	
	// Disable the watchdog timer
	*p_WDT_MR = (1 << 15);

	/*
	 * Enables peripheral clocks for Parallel I/O Controller A-F.
	 * This a standard initialization before using peripherals.
	 */
	*p_PMC_PCER0 =	(1 << 11) | (1 << 12) | (1 << 13) |
					(1 << 14) | (1 << 15) | (1 << 16);
	
	// configure UART so Unity can use USB/RS-232 as output
	configure_uart();
}
