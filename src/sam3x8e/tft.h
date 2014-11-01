/**
 * @brief TFT display code
 * @details Provides rendering on a TFT display and touch input (both polling
 * and interrupt based)
 *
 * @pre This API needs to have all pins in tft_screen struct to be enabled by
 * pio and configured as outputs. An example using a itead 2.4" shield follows:
 *
 *	tft_screen tft;
 *	tft.PORT_CS = PIOA; tft.PIN_CS = 22;
 *	tft.PORT_WR = PIOA; tft.PIN_WR = 6;
 *	tft.PORT_RS = PIOA; tft.PIN_RS = 4;
 *	tft.PORT_D0 = PIOA; tft.PIN_D0 = 8;
 *	tft.PORT_D1 = PIOA; tft.PIN_D1 = 9;
 *	tft.PORT_D2 = PIOB; tft.PIN_D2 = 25;
 *	tft.PORT_D3 = PIOC; tft.PIN_D3 = 28;
 *	tft.PORT_D4 = PIOC; tft.PIN_D4 = 26;
 *	tft.PORT_D5 = PIOC; tft.PIN_D5 = 25;
 *	tft.PORT_D6 = PIOC; tft.PIN_D6 = 24;
 *	tft.PORT_D7 = PIOC; tft.PIN_D7 = 23;
 *	tft.width = 239;
 *	tft.height = 319;
 *
 * 	//configure pins
 *	pio_enable_pin(tft.PORT_CS, tft.PIN_CS); pio_conf_pin(tft.PORT_CS, tft.PIN_CS, 0, 1);
 *	pio_enable_pin(tft.PORT_WR, tft.PIN_WR); pio_conf_pin(tft.PORT_WR, tft.PIN_WR, 0, 1);
 *	pio_enable_pin(tft.PORT_RS, tft.PIN_RS); pio_conf_pin(tft.PORT_RS, tft.PIN_RS, 0, 1);
 *	pio_enable_pin(tft.PORT_D0, tft.PIN_D0); pio_conf_pin(tft.PORT_D0, tft.PIN_D0, 0, 1);
 *	pio_enable_pin(tft.PORT_D1, tft.PIN_D1); pio_conf_pin(tft.PORT_D1, tft.PIN_D1, 0, 1);
 *	pio_enable_pin(tft.PORT_D2, tft.PIN_D2); pio_conf_pin(tft.PORT_D2, tft.PIN_D2, 0, 1);
 *	pio_enable_pin(tft.PORT_D3, tft.PIN_D3); pio_conf_pin(tft.PORT_D3, tft.PIN_D3, 0, 1);
 *	pio_enable_pin(tft.PORT_D4, tft.PIN_D4); pio_conf_pin(tft.PORT_D4, tft.PIN_D4, 0, 1);
 *	pio_enable_pin(tft.PORT_D5, tft.PIN_D5); pio_conf_pin(tft.PORT_D5, tft.PIN_D5, 0, 1);
 *	pio_enable_pin(tft.PORT_D6, tft.PIN_D6); pio_conf_pin(tft.PORT_D6, tft.PIN_D6, 0, 1);
 *	pio_enable_pin(tft.PORT_D7, tft.PIN_D7); pio_conf_pin(tft.PORT_D7, tft.PIN_D7, 0, 1);
 *
 *	tft_init(&tft);
 *
 * @author Theodor Lindquist
 * @date 30 October 2014
 *
 */

#ifndef TFT_H_
#define TFT_H_

#include <inttypes.h>
#include "sam3x8e/pio.h"

// Struct containing an instace of a tft screen
typedef struct tft_screen {
	uint32_t PORT_CS;
	uint32_t PIN_CS;

	uint32_t PORT_WR;
	uint32_t PIN_WR;

	uint32_t PORT_RS;
	uint32_t PIN_RS;

	uint32_t PORT_D0;
	uint32_t PIN_D0;

	uint32_t PORT_D1;
	uint32_t PIN_D1;

	uint32_t PORT_D2;
	uint32_t PIN_D2;

	uint32_t PORT_D3;
	uint32_t PIN_D3;

	uint32_t PORT_D4;
	uint32_t PIN_D4;

	uint32_t PORT_D5;
	uint32_t PIN_D5;

	uint32_t PORT_D6;
	uint32_t PIN_D6;

	uint32_t PORT_D7;
	uint32_t PIN_D7;

	uint32_t width;
	uint32_t height;
} tft_screen;

/**
 * Initialize the tft screen
 * @param screen the screen instance
 */
void tft_init(tft_screen *screen);

/**
 * Clears the tft screen (fills it with black)
 * @param screen the screen instance
 */
void tft_clear(tft_screen *screen);

/**
 * Writes a pixel to the screen memory. Alternative name tft_write_pixel / tft_put_pixel / tft_render_pixel
 * @param screen screen instance
 * @param x xpos
 * @param y ypos
 * @param color color of pixel, format: 0bRRRRRGGGGGBBBBB
 */
void tft_write(tft_screen *screen, uint16_t x, uint16_t y, uint16_t color);

/**
 * Poll for input (not implemented)
 * @param screen screen instance
 * @param x will contain the x-coordinate of the touch
 * @param y will contain the y-coordinate of the touch
 * @return true if touch is occuring
 */
uint32_t tft_read_input(tft_screen *screen, uint32_t *x, uint32_t *y);

// The funcitons below should not be used by the API user
// They are only intended as "helper" functions for the tft-api
void tft_write_com(tft_screen *screen, uint8_t com);

void tft_write_data(tft_screen *screen, uint16_t data);

void tft_set_xy(tft_screen *screen, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);

// bus functions
void tft_clear_bus(tft_screen *screen);

void tft_set_bus(tft_screen *screen, uint8_t value);

void tft_commit_bus(tft_screen *screen);

void tft_write_bus(tft_screen *screen, uint16_t data);

void tft_fast_fill(tft_screen *screen);

#endif //TFT_H_
