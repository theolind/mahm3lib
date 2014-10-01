/*
 * unity_hw_setup.c
 *
 * This file still needs some "cleaning":
 * 	- 	eliminate the need for memory mapping in this file
 * 		(create new functions, etc)
 *
 * 	-	make this file totally dependent of the SAM3X8E library!
 *
 * Author:	Mathias Beckius
 *
 * Date:	29 September, 2014
 */

#include "unity_hw_setup.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/uart.h"
#include "sam3x8e/wdt.h"

// ---------------------------------------------------------------------------
// BAD CODE!
// THIS CODE MUST BE REMOVED WHEN THE FUNCTIONS BELOW ARE IN GOOD SHAPE
// ---------------------------------------------------------------------------
// EEFC Flash Mode Register 0
#define EEFC_FMR_0 (*p_EEFC_FMR_0)
// EEFC Flash Mode Register 1
#define EEFC_FMR_1 (*p_EEFC_FMR_1)
//keep this until PMC->PMC_SR is fully working!
#define PMC_SR_ (*((volatile uint32_t *)0x400E0668U))
/* -------- EEFC_FMR : (EFC Offset: 0x00) EEFC Flash Mode Register -------- */
#define EEFC_FMR_FRDY (0x1u << 0) /**< \brief (EEFC_FMR) Ready Interrupt Enable */
#define EEFC_FMR_FWS_Pos 8
#define EEFC_FMR_FWS_Msk (0xfu << EEFC_FMR_FWS_Pos) /**< \brief (EEFC_FMR) Flash Wait State */
#define EEFC_FMR_FWS(value) ((EEFC_FMR_FWS_Msk & ((value) << EEFC_FMR_FWS_Pos)))
// ---------------------------------------------------------------------------
// END OF BAD CODE...
// ---------------------------------------------------------------------------

static void configure_uart(void) {
	const uart_settings_t uart_settings = {
		.baud_rate = 115200,
		.parity = UART_PARITY_NO,
		.ch_mode = UART_CHMODE_NORMAL
	};

	// enable Peripheral Clock for UART.
	pmc_enable_peripheral_clock(ID_UART);

	// remove the pins from under the control of PIO
	pio_disable_pin(PIOA, 8);	//RX0
	pio_disable_pin(PIOA, 9);	//TX0

	// initialize UART
	uart_init(&uart_settings);
}

/*
 * Switch master clock source selection to PLLA clock.
 *
 * param: ul_pres Processor clock prescaler.
 *
 * ret 0 Success.
 * ret 1 Timeout error.
 *
 * Important!
 * When everything's working, clean up and move this function to PMC API.
 * PMC->PMC_SR might still be a little unreliable, won't work in
 * systemclock_init().
 */
static uint32_t pmc_switch_mclk_to_pllack(uint32_t ul_pres)
{
	uint32_t ul_timeout;
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (~(0x7u << 4))) | ul_pres;
	for (ul_timeout = 2048; !(PMC->PMC_SR & (1 << 3)); --ul_timeout) {
	//for (ul_timeout = 2048; (PMC_SR_ & (1 << 3)) == 0; --ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}
	PMC->PMC_MCKR = (PMC->PMC_MCKR & (~(0x3u))) | 2;
	for (ul_timeout = 2048; !(PMC->PMC_SR & (1 << 3)); --ul_timeout) {
	//for (ul_timeout = 2048; (PMC_SR_ & (1 << 3)) == 0; --ul_timeout) {
		if (ul_timeout == 0) {
			return 1;
		}
	}
	return 0;
}

/*
 * Important!
 * PMC->PMC_SR might still be a little unreliable, won't work!
 */
static void systemclock_init(void)
{
	// EEFC Flash Mode Register 0
	uint32_t *const p_EEFC_FMR_0 = (uint32_t *) 0x400E0A00U;
	// EEFC Flash Mode Register 1
	uint32_t *const p_EEFC_FMR_1 = (uint32_t *) 0x400E0C00U;

	/*
	 * Set flash wait state, based upon 84 MHz CPU frequency.
	 * This field defines the number of wait states for read and write operations:
	 * Number of cycles for Read/Write operations = FWS+1
	 */
	EEFC_FMR_0 = EEFC_FMR_FWS(4);
	EEFC_FMR_1 = EEFC_FMR_FWS(4);

	/* Config system clock setting - Already running from SYSCLK_SRC_MAINCK_4M_RC */
	//Internal 4MHz RC oscillator as master source clock
	/* Enable Main XTAL oscillator */
	PMC->CKGR_MOR = (PMC->CKGR_MOR & ~2u) | (0x37u << 16) | 1 | (62u << 8);

	// Wait to the Main XTAL oscillator is stabilized
	while ((PMC_SR_ & 1) == 0);
	//while (!(PMC->PMC_SR & 0x1u));

	// select the Main Crystal Oscillator
	PMC->CKGR_MOR |= (0x37 << 16) | (1 << 24);

	// oscillator ready? Main Oscillator Selection Status - Selection is in progress
	while ((PMC_SR_ & (1 << 16)) == 0);
	//while (!(PMC->PMC_SR & (1 << 16)));

	// Disable PLLA clock - Always stop PLL first!
	PMC->CKGR_PLLAR = (1 << 29);
	// set PMC clock generator
	PMC->CKGR_PLLAR = (1 << 29) | (13 << 16) | 1 | (0x3fU << 8);

	// wait for PLL to be locked
	while ((PMC_SR_ & 2) == 0);
	//while (!(PMC->PMC_SR & 2));

	// Switch master clock source selection to PLLA clock,
	// selected clock divided by 2
	pmc_switch_mclk_to_pllack(1 << 4);
}

void unity_hw_setup(void) {
	// originally this was a call to the ASF function 'sysclk_init()'
	systemclock_init();

	// disable the watchdog timer
	wdt_disable();

	// configure UART so Unity can use USB/RS-232 as output
	configure_uart();
}
